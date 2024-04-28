#include "MotorControl.h"
#include <Wire.h>
#include "sharedData.h"

ReceivedData receivedData;    // Declaration of the received data object
MiniMotor motor1(Wire, 0x60); // A1 = 1, A0 = clear
MiniMotor motor2(Wire, 0x65); // A1 = 1, A0 = 1 (default)

const int range = 20;
const int motorDriveStrength = 100;
const int updateInterval = 50; // Interval for updating motor position

void motorControlSetup()
{
    pinMode(ANALOG_MOTOR_PIN_1, INPUT);
    pinMode(ANALOG_MOTOR_PIN_2, INPUT);

    motor1.init();
    motor2.init();
}
void motorControlLoop()
{
    if (!receivedData.dataReady || receivedData.instruction == -1)
    {
        return;
    }

    int instruction = receivedData.instruction; // Instruction range 0-255
    int targetValue2 = 255 - instruction;       // Complementary target for motor2

    int analogValue1 = analogRead(ANALOG_MOTOR_PIN_1);
    int analogValue2 = analogRead(ANALOG_MOTOR_PIN_2);

    int motorValue1 = map(analogValue1, 0, 1023, 0, 255);
    int motorValue2 = map(analogValue2, 0, 1023, 0, 255);

    adjustMotor(motor1, motorValue1, instruction);
    adjustMotor(motor2, motorValue2, targetValue2);
}

void adjustMotor(MiniMotor &motor, int currentValue, int targetValue)
{
    if (abs(currentValue - targetValue) > range)
    {
        int direction = (currentValue < targetValue) ? motorDriveStrength : -motorDriveStrength;
        motor.drive(direction);
        delay(updateInterval);
        checkAndReportFault(motor);
    }
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