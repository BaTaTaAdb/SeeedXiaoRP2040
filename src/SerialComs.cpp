// XIAO RP2040
#include "SerialComs.h"
#include "SharedData.h"
#include "motorControl.h"

bool cut;

// ReceivedData receivedData; // Declaration of the received data object
// SharedData sharedData;     // Declaration of the shared data object

/* int gliderInstruction;
int operation; */

void setupSerialComs()
{
    // Start Serial comms with raspberry pi pico

    // Checked init
    Serial1.setRX(UART_RX_PIN);
    Serial1.setTX(UART_TX_PIN);
    Serial1.begin(UART_BAUD_RATE);
}

void loopSerialComs()
{
    // available message:
    if (Serial1.available() > 0)
    {
        // "control,operation\n" (if -1, then no instruction)
        String message = Serial1.readStringUntil('\n');
        message.trim();
        if (message == "open")
        {
            cutParachute(1);
            Serial.println("Start motor!");
        }
        // parseString(message, gliderInstruction, operation);
        // receivedData.gliderInstruction = gliderInstruction;
        // receivedData.operation = operation;
        // receivedData.dataReady = true;
        Serial.print("Received data: ");
        Serial.println(message);
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
        Serial.println("Sent through Serial1!");
    }
}

void parseString(const String &input, double &num1, double &num2)
{
    int firstCommaIndex = input.indexOf(',');
    if (firstCommaIndex == -1)
    {
        Serial.println("Error: First comma missing in string.");
        return;
    }

    num1 = input.substring(0, firstCommaIndex).toInt();
    num2 = input.substring(firstCommaIndex + 1).toInt();
}