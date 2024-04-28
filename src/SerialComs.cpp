#include "SerialComs.h"

void setupSerialComs()
{
    Serial1.setRX(UART_RX_PIN);
    Serial1.setTX(UART_TX_PIN);
    Serial1.begin(UART_BAUD_RATE);
}

void loopSerialComs()
{
}