#ifndef SERIAL_COMS_H
#define SERIAL_COMS_H

#include "Arduino.h"

const int UART_TX_PIN = 6;
const int UART_RX_PIN = 7;
const int UART_BAUD_RATE = 9600;

void setupSerialComs();
void loopSerialComs();

#endif