#include "IMU.h"
#include <Arduino.h>
#include <REG.h>
#include <wit_c_sdk.h>
#include <Wire.h>
#include "Global.h"

void IMUDataUpdate(uint32_t regIndex, uint32_t count) {
    // This function is called when new data is available
    // We assume AX, AY, AZ are at indices 0, 1, 2, and HX, HY, HZ are at indices 3, 4, 5
    if (regIndex <= 2) { // Accelerometer data
        float ax = sReg[AX] / 32768.0 * 16; // Convert to actual value
        float ay = sReg[AY] / 32768.0 * 16; // Convert to actual value
        float az = sReg[AZ] / 32768.0 * 16; // Convert to actual value
    }
    if (regIndex <= 5 && regIndex >= 3) { // Magnetometer data
        float hx = sReg[HX]; // Raw magnetometer readings
        float hy = sReg[HY];
        float hz = sReg[HZ];
        magneticDirection = atan2(hy, hx) * (180 / PI); // Calculate heading
    }
}

void setupIMU() {
    WitInit(WIT_PROTOCOL_I2C, 0x50); // Initialize the IMU on I2C protocol at address 0x50
    WitRegisterCallBack(IMUDataUpdate); // Register the callback function
}

void getIMUData(String &message) {
    WitReadReg(AX, 6); // Read accelerometer and magnetometer data
    delay(100); // Small delay to ensure data is ready

    // Append IMU data to message
    message += " AccX: " + String(sReg[AX] / 32768.0 * 16);
    message += " AccY: " + String(sReg[AY] / 32768.0 * 16);
    message += " AccZ: " + String(sReg[AZ] / 32768.0 * 16);
    message += " MagDir: " + String(magneticDirection) + "°";
}