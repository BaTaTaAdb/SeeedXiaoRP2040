#include "Global.h"
#include "pico/sync.h"

LoRaData loraData;

void initSharedDataStructures() {
    mutex_init(&loraData.lock);
}

String message = "";
String state = "0";
float magneticDirection;
int steer = 0;

/*
States 

-1 - doesn't change
0 - not ready
1 - ready
2 - armed
3 - flight
4 - Help
5 - Manual control

*/
