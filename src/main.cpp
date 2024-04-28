#include <Arduino.h>
#include "config.h"
#include "BME680.h"
#include <LoRa.h>
#include <Wire.h>

void setup()
{
  Serial.begin(115200); // Serial to computer
  setupBME680();
}

void loop()
{
  getBME680Data();
}

void setup1()
{
}

void loop1()
{
}