#ifndef SERIAL_COMS_H
#define SERIAL_COMS_H

#include "Arduino.h"

const int UART_TX_PIN = 0;
const int UART_RX_PIN = 1;
const int UART_BAUD_RATE = 9600;

void setupSerialComs();
void loopSerialComs();
// void parseString(const String &input, int &num1, int &num2);

#endif