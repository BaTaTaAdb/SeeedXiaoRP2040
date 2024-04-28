#include "MotorControl.h"
#include <Wire.h>
#include "sharedData.h"

ReceivedData receivedData;    // Declaration of the received data object
MiniMotor motor1(Wire, 0x60); // A1 = 1, A0 = clear
MiniMotor motor2(Wire, 0x65); // A1 = 1, A0 = 1 (default)

void motorControlSetup()
{
    pinMode(ANALOG_MOTOR_PIN_1, INPUT);
    pinMode(ANALOG_MOTOR_PIN_2, INPUT);

    motor1.init();
    motor2.init();
}
void motorControlLoop()
{
    if (receivedData.dataReady == false || receivedData.state != 1)
    {
        return;
    }

    int instruction = receivedData.instruction; // int between 0-255
    int analogValue1 = analogRead(ANALOG_MOTOR_PIN_1);
    int analogValue2 = analogRead(ANALOG_MOTOR_PIN_2);
    int motorValue1 = map(analogValue1, 0, 1023, 0, 255);
    int motorValue2 = map(analogValue2, 0, 1023, 0, 255);

    while (motorValue1 < instruction)
    // If the motor value is less than the instruction, then drive the motor forward
    {
        motor1.drive(63);
        motor2.drive(-63);
        delayUntil(50);

        if (motorValue1 > instruction)
        {
            break;
        }
    }

    while (motorValue1 > instruction)
    // If the motor value is greater than the instruction, then drive the motor backward
    {
        motor1.drive(-63);
        motor2.drive(63);
    }
}

void delayUntil(unsigned long elapsedTime)
{
    unsigned long startTime = millis();
    while (startTime + elapsedTime > millis())
    {
        checkAndReportFault(motor1, 0); // Check and report faults for motor1
        checkAndReportFault(motor2, 1); // Check and report faults for motor2
    }
}

void checkAndReportFault(MiniMotor &motor, int motorNumber)
{
    byte faultStatus = motor.getFault();

    if (faultStatus & FAULT)
    {
        Serial.print("Motor ");
        Serial.print(motorNumber);
        Serial.print(" fault: ");

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