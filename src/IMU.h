#ifndef IMU_H
#define IMU_H

#include <Arduino.h>


void setupIMU();
void getIMUData(String &message);
void IMUDataUpdate(uint32_t regIndex, uint32_t count);

#endif // IMU_H