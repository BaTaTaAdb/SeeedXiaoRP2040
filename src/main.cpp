#include <Arduino.h>
#include "config.h"
#include "BME680.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <LoRa.h>
#include "Global.h"
#include <Wire.h>

void setup()
{
  initSharedDataStructures();
  Serial.begin(115200); // Serial to computer
  setupBME680();
}

void loop()
{
  getBME680Data(message);
}

void setup1()
{
  
}

void loop1()
{
}