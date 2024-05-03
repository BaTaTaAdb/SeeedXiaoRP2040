#include "MotorControl.h"
#include <Wire.h>
#include "SharedData.h"

// ReceivedData receivedData;    // Declaration of the received data object
MiniMotor motor1(Wire, 0x60); // A1 = 1, A0 = clear
MiniMotor motor2(Wire, 0x65); // A1 = 1, A0 = 1 (default)

const int range = 20;
const int motorDriveStrength = 100;
const int updateInterval = 50; // Interval for updating motor position

void motorControlSetup()
{
    pinMode(ANALOG_MOTOR_PIN_1, OUTPUT);
    pinMode(ANALOG_MOTOR_PIN_2, OUTPUT);
    pinMode(MOSFET_1_PIN, OUTPUT);
    digitalWrite(MOSFET_1_PIN, LOW); // Set MOSFET_1_PIN HIGH to enable MOSFET()
    pinMode(MOSFET_2_PIN, OUTPUT);
    digitalWrite(MOSFET_2_PIN, LOW); // Set MOSFET_2_PIN HIGH to enable MOSFET()

    delay(1000);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
    digitalWrite(BUZZER_PIN, HIGH);

    motor1.init();
    motor2.init();

    Serial.println("MOTORS: READY!");
}
void motorControlLoop()
{
    if (!receivedData.dataReady)
        return;

    // int gliderInstruction = receivedData.gliderInstruction; // Instruction range 0-255
    int gliderInstruction = -1; // Instruction range 0-255
    int operation = receivedData.operation;
    int targetValue2 = 255 - gliderInstruction; // Complementary target for motor2

    switch (operation)
    {
    case 1:
        digitalWrite(MOSFET_1_PIN, HIGH);
        break;

    case 2:
        digitalWrite(MOSFET_2_PIN, HIGH);
        break;

    case 3:
        digitalWrite(BUZZER_PIN, HIGH);
        break;

    case 4:
        digitalWrite(BUZZER_PIN, LOW);
        break;
    }

    if (gliderInstruction == -1)
        return;

    while (1)
    {
        runMotor(motor1);
        runMotor(motor2);
    }

    /* int analogValue1 = analogRead(ANALOG_MOTOR_PIN_1);
    int analogValue2 = analogRead(ANALOG_MOTOR_PIN_2);

    int motorValue1 = map(analogValue1, 0, 1023, 0, 255);
    int motorValue2 = map(analogValue2, 0, 1023, 0, 255);

    adjustMotor(motor1, motorValue1, gliderInstruction);
    adjustMotor(motor2, motorValue2, targetValue2); */
}

void runMotor(MiniMotor &motor)
{
    motor.drive(100);
    delay(1000);
}

void delayUntil(unsigned long elapsedTime)
{
    unsigned long startTime = millis();
    while (startTime + elapsedTime > millis())
    {
        checkAndReportFault(motor1); // Check and report faults for motor1
        checkAndReportFault(motor2); // Check and report faults for motor2
    }
}

void checkAndReportFault(MiniMotor &motor)
{
    byte faultStatus = motor.getFault();
    if (faultStatus & FAULT)
    {
        Serial.print("Motor fault: ");
        if (faultStatus & OCP)
            Serial.println("Chip overcurrent!");
        if (faultStatus & ILIMIT)
            Serial.println("Load current limit!");
        if (faultStatus & UVLO)
            Serial.println("Undervoltage!");
        if (faultStatus & OTS)
            Serial.println("Over temp!");
    }
}

void cutParachute(bool cut)
{
    if (cut)
    {

        analogWrite(MOSFET_1_PIN, 1023);
        analogWrite(MOSFET_2_PIN, 1023);
        digitalWrite(ANALOG_MOTOR_PIN_1, HIGH);
        digitalWrite(ANALOG_MOTOR_PIN_2, HIGH);
    }
    else
    {

        digitalWrite(MOSFET_1_PIN, LOW);
        digitalWrite(MOSFET_2_PIN, LOW);
        digitalWrite(ANALOG_MOTOR_PIN_1, LOW);
        digitalWrite(ANALOG_MOTOR_PIN_2, LOW);
    }
    Serial.println(cut);
}

void buzzerControl(bool state) {
    if (state) {
        digitalWrite(BUZZER_PIN, LOW);
    }
    else {
        digitalWrite(BUZZER_PIN, HIGH);
    }
}