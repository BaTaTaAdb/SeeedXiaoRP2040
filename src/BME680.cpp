#include <Arduino.h>
#include "BME680.h"
#include <Arduino.h>
#include "sharedData.h"
#include <Wire.h>

SharedData sharedData;                        // Declaration of the shared data object
Adafruit_BME680 bme = Adafruit_BME680(&Wire); // Initialize the BME680 sensor instance

void setupBME680()
{
    // set vbat analog pin
    pinMode(VBAT_PIN, INPUT);

    Wire.setSDA(6);
    Wire.setSCL(7);
    Wire.begin();
    if (!bme.begin())
    {
        while (1)
        {
            Serial.println("Could not find a valid BME680 sensor, check wiring!");
            delay(200);
        }
    }
    else
    {
        // Set up oversampling and filter initialization
        bme.setTemperatureOversampling(BME680_OS_2X);
        bme.setHumidityOversampling(BME680_OS_2X);
        bme.setPressureOversampling(BME680_OS_2X);
        bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
        // bme.setGasHeater(320, 150); // 320*C for 150 ms
        sharedData.groundPressure = bme.readPressure() / 100;
    }
}

void getBME680Data()
{
    if (!bme.performReading())
    {
        Serial.println("Failed to perform reading from BME680.");
        return;
    }
    else
    {
        // also possible code:
        /*
        sharedData.pressure = bme.readPressure() / 100;
        sharedData.temperature = bme.readTemperature();
        sharedData.height = bme.readAltitude(sharedData.groundPressure);
        sharedData.humidity = bme.readHumidity();
        sharedData.gasResistance = bme.gas_resistance / 1000;
        sharedData.vbat = analogRead(VBAT_PIN) * (5.0 / 1024.0) * 3; // Converte o valor lido em volts
        sharedData.dataReady = true;
        */
        sharedData.pressure = bme.pressure / 100;
        sharedData.temperature = bme.temperature;
        sharedData.height = bme.readAltitude(sharedData.groundPressure);
        sharedData.humidity = bme.readHumidity();
        sharedData.gasResistance = bme.gas_resistance / 1000;
        sharedData.vbat = analogRead(VBAT_PIN) * (5.0 / 1024.0) * 3; // Reads analog pin and converts it to volts
        sharedData.dataReady = true;
    }
}
