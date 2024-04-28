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
    int gliderInstruction;   // value 0-255 (stearing) if -1, then no steering
    int operation;           // value that cuts the wires
    volatile bool dataReady; // Flag to indicate new data is ready
};

extern SharedData sharedData;     // Declaration of the shared data object
extern ReceivedData receivedData; // Declaration of the received data object

#endif