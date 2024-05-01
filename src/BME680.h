#ifndef BME680_H
#define BME680_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

const int VBAT_PIN = 29;

// Function declarations
void setupBME680();
void getBME680Data();

#endif // GPS_TEMP_BAR_H
