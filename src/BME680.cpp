#include <Arduino.h>
#include "BME680.h"
#include <Arduino.h>
#include "Global.h"

Adafruit_BME680 bme; // Initialize the BME680 sensor instance

void setupBME680()
{
    if (!bme.begin())
    {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
    }
    else
    {
        // Set up oversampling and filter initialization
        bme.setTemperatureOversampling(BME680_OS_2X);
        bme.setHumidityOversampling(BME680_OS_2X);
        bme.setPressureOversampling(BME680_OS_2X);
        bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
        // bme.setGasHeater(320, 150); // 320*C for 150 ms
    }
}

void getBME680Data(String &message)
{
    if (!bme.performReading())
    {
        message += " Failed to perform reading from BME680.";
        return;
    }
    sharedData.temperatureAmbient = double(bme.temperature);
    message += ", Pressure: " + String(bme.pressure / 100.0) + " hPa";
    message += ", Humidity: " + String(bme.humidity) + "%";
}
