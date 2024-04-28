#include "SerialComs.h"
#include "SharedData.h"

//ReceivedData receivedData; // Declaration of the received data object
//SharedData sharedData;     // Declaration of the shared data object

int gliderInstruction;
int operation;

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
        // "control,operation\n" (if -1, then no instruction)
        String message = Serial1.readStringUntil('\n');
        parseString(message, gliderInstruction, operation);
        receivedData.gliderInstruction = gliderInstruction;
        receivedData.operation = operation;
        receivedData.dataReady = true;
    }

    if (sharedData.dataReady)
    {
        Serial1.print(sharedData.pressure);
        Serial1.print(",");
        Serial1.print(sharedData.temperature);
        Serial1.print(",");
        Serial1.print(sharedData.height);
        Serial1.print(",");
        Serial1.print(sharedData.humidity);
        Serial1.print(",");
        Serial1.print(sharedData.gasResistance);
        Serial1.print(",");
        Serial1.print(sharedData.vbat);
        Serial1.println();
    }
}

void parseString(const String &input, int &num1, int &num2)
{
    int commaIndex = input.indexOf(',');
    if (commaIndex == -1)
    {
        Serial.println("Error: No comma in string.");
        return;
    }

    num1 = input.substring(0, commaIndex).toInt();
    num2 = input.substring(commaIndex + 1).toInt();
}