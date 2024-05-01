// XIAO RP2040
#include "SerialComs.h"
#include "SharedData.h"

// ReceivedData receivedData; // Declaration of the received data object
// SharedData sharedData;     // Declaration of the shared data object

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
        // receivedData.gliderInstruction = gliderInstruction;
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
        Serial1.print(sharedData.vbat);
        Serial1.println();
        sharedData.dataReady = false;
    }
}

void parseString(const String &input, int &num1, int &num2, int &num3, int &num4)
{
    int firstCommaIndex = input.indexOf(',');
    if (firstCommaIndex == -1)
    {
        Serial.println("Error: First comma missing in string.");
        return;
    }

    int secondCommaIndex = input.indexOf(',', firstCommaIndex + 1);
    if (secondCommaIndex == -1)
    {
        Serial.println("Error: Second comma missing in string.");
        return;
    }

    int thirdCommaIndex = input.indexOf(',', secondCommaIndex + 1);
    if (thirdCommaIndex == -1)
    {
        Serial.println("Error: Third comma missing in string.");
        return;
    }

    num1 = input.substring(0, firstCommaIndex).toInt();
    num2 = input.substring(firstCommaIndex + 1, secondCommaIndex).toInt();
    num3 = input.substring(secondCommaIndex + 1, thirdCommaIndex).toInt();
    num4 = input.substring(thirdCommaIndex + 1).toInt();
}
