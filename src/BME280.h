#ifndef BME680_H
#define BME680_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

const int VBAT_PIN = 29;

// Function declarations
void setupBMP280();
void getBME680Data();

#endif // GPS_TEMP_BAR_H
