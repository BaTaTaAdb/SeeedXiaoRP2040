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
  setupGPS();
  setupBME680();
  setupIMU();
}

void loop()
{

  getGPSData(message);
  getBME680Data(message);
  getIMUData(message);
  initSharedDataStructures();
}

void setup1()
{
  setupLoRa();
}

void loop1()
{
  if (state == "0")
  {
    onReceive(LoRa.parsePacket());
  }
  if (state == "1")
  {
    onReceive(LoRa.parsePacket());
  }

  sendMessage();
}