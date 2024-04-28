#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "Arduino.h"
#include "MiniMotor.h"

const int ANALOG_MOTOR_PIN_1 = 27;
const int ANALOG_MOTOR_PIN_2 = 26;

void motorControlSetup();
void motorControlLoop();
void checkAndReportFault(MiniMotor &motor);
void delayUntil(unsigned long elapsedTime);
void adjustMotor(MiniMotor &motor, int currentValue, int targetValue);

#endif