#include <arduino-compat.h>
#include <logger.h>
#include <pin-bus.h>

using namespace v2;

#define BUS_SIZE 5

#define RELAY_BOARDS 2
#define INPUT_BOARDS 3

PCF8574Bus bus(BUS_SIZE);

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    logger_setup(&Serial);

    bus.setup(0xFF);

    logger_log("Controller initialized.");
}

byte state = LOW;

void loop()
{
    state = state == LOW ? HIGH : LOW;
    bus.readState();
    for (size_t relayIndex = 0; relayIndex < RELAY_BOARDS; relayIndex++)
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            bus.setPin(relayIndex, bit, state);
            // if (bitState == LOW)
            // {
            //     logger_log("Bus byte: %d pin: %d state: %d", i, bit, bitState);
            // }
        }
    }

    bus.writeState();

    delay(1000);
}
