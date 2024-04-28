#ifndef SHARED_DATA_H
#define SHARED_DATA_H

struct SharedData
{
    double pressure, temperature, height, humidity, gasResistance;
    double groundPressure;
    volatile bool dataReady; // Flag to indicate new data is ready
};
struct ReceivedData
{
    int state;               // 1 controll, 0 default
    int instruction;         // value 0-255 (stearing)
    volatile bool dataReady; // Flag to indicate new data is ready
};

extern SharedData sharedData;     // Declaration of the shared data object
extern ReceivedData receivedData; // Declaration of the received data object

#endif