#include <Arduino.h>
#include "config.h"
#include "Comms.h"
#include "GpsTempBar.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <LoRa.h>
#include "Global.h"
#include <Wire.h>
#include "IMU.h"

void setupLoRa();

void setup()
{
  Serial.begin(115200); // Serial to computer
  setupBME680();
}

void loop()
{
  getBME680Data(message);
  initSharedDataStructures();
}

void setup1()
{
}

void loop1()
{
}