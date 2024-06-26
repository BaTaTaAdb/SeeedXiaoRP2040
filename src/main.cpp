#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "BME680.h"
#include "SerialComs.h"
#include "MotorControl.h"

void setup()
{
  Serial.begin(115200); // Serial to computer

  setupBME680();
  setupSerialComs();
}

void loop()
{
  getBME680Data();
  loopSerialComs();
  Serial.println("Bootup!");
}

void setup1()
{
  // motor controll on core1
  motorControlSetup();
}

void loop1()
{
  // motor controll on core1
  motorControlLoop();
}