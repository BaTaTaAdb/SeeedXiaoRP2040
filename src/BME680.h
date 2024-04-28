#ifndef BME680_H
#define BME680_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

extern Adafruit_BME680 bme; // Externally define BME680 sensor instance

// Function declarations
void setupBME680();
void getBME680Data(String &message);

#endif // GPS_TEMP_BAR_H
