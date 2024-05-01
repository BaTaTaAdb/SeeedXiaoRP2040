// SharedData.cpp
#include "SharedData.h"
#include <Arduino.h>

void parseString(const String &input, int &num1, int &num2, int &num3, int &num4);
SharedData sharedData;     // Define the shared data object
ReceivedData receivedData; // Define the received data object
