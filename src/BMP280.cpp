#include <Arduino.h>
#include "BMP280.h"
#include "SharedData.h"
#include <Wire.h>

// SharedData sharedData;                        // Declaration of the shared data object
/* Adafruit_BME680 bme = Adafruit_BME680(&Wire); // Initialize the BME680 sensor instance */
Adafruit_BMP280 bmp;

void setupBMP280()
{
    // set vbat analog pin
    pinMode(VBAT_PIN, INPUT);

    Wire.setSDA(6);
    Wire.setSCL(7);
    Wire.begin();
    if (!bmp.begin())
    {
        while (1)
        {
            Serial.println("Could not find a valid BMP280 sensor, check wiring!");
            delay(200);
        }
    }
    else
    {
        // Set up oversampling and filter initialization
        /* bme.setTemperatureOversampling(BME680_OS_2X);
        bme.setHumidityOversampling(BME680_OS_2X);
        bme.setPressureOversampling(BME680_OS_2X);
        bme.setIIRFilterSize(BME680_FILTER_SIZE_3); */
        // bme.setGasHeater(320, 150); // 320*C for 150 ms
        sharedData.groundPressure = bmp.readPressure() / 100;
    }
}

void getBMP280Data()
{
    sensors_event_t temp_event, pressure_event;
    bmp_temp->getEvent(&temp_event);
    bmp_pressure->getEvent(&pressure_event);

    sharedData.pressure = pressure_event.pressure / 100;
    sharedData.temperature = temp_event.temperature;
    sharedData.height = bmp.readAltitude(sharedData.groundPressure);
    sharedData.vbat = analogRead(VBAT_PIN) * 0.01302083; // (5.0 / 1024.0) * 3 * (8 / 9); // Reads analog pin and converts it to volts
    sharedData.dataReady = true;

    // DEBUG DATA
    Serial.print(sharedData.pressure);
    Serial.print(",");
    Serial.print(sharedData.temperature);
    Serial.print(",");
    Serial.print(sharedData.height);
    Serial.print(",");
    Serial.print(sharedData.vbat);
    Serial.println();
}
