#include <arduino-compat.h>
#include <logger.h>
#include <pin-bus.h>

using namespace v2;


#define RELAY_BOARDS 2
#define INPUT_BOARDS 3
#define BUS_SIZE RELAY_BOARDS + INPUT_BOARDS

PCF8574Bus bus(RELAY_BOARDS, INPUT_BOARDS);

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

void loop()
{
    bus.readState();
    for (size_t relayIndex = 0; relayIndex < RELAY_BOARDS; relayIndex++)
    {
        for (size_t bit = 0; bit < 8; bit++)
        {
            const auto relayState = bus.getPin(RELAY_BOARDS + relayIndex, bit);
            bus.setPin(relayIndex, bit, relayState);
        }
    }

    bus.writeState();
}
