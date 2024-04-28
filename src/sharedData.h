#ifndef SHARED_DATA_H
#define SHARED_DATA_H

struct SharedData
{
    double pressure, temperature, height, humidity, gasResistance;
    double groundPressure;
    volatile bool dataReady; // Flag to indicate new data is ready
};

extern SharedData sharedData; // Declaration of the shared data object

#endif