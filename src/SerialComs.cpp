#include "SerialComs.h"

void setupSerialComs()
{
    // Start Serial comms with raspberry pi pico
    Serial1.setRX(UART_RX_PIN);
    Serial1.setTX(UART_TX_PIN);
    Serial1.begin(UART_BAUD_RATE);

    while (!Serial1)
    {
        delay(50); // wait for raspberry pi pico to connect
    }
    while (Serial1.available() == 0)
    {
        delay(100);
    }
}

void loopSerialComs()
{
    // available message:
    while (Serial1.available() > 0)
    {
        // state,controll
        String message = Serial.readStringUntil('\n');
    }
}