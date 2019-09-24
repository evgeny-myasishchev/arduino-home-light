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
            const byte relayAddress = relayIndex * 8 + bit;
            const byte relaySwitchAddress = RELAY_BOARDS * 8 + relayAddress;
            const auto relaySwitchState = bus.getPin(relaySwitchAddress);
            bus.setPin(relayIndex * 8 + bit, relaySwitchState);
        }
    }

    const byte switchAllState = bus.getPin((RELAY_BOARDS + INPUT_BOARDS - 1) * 8);
    if(switchAllState == LOW) 
    {
        logger_log("Got signal from all switch");
        for (size_t i = 0; i < RELAY_BOARDS * 8; i++)
        {
            bus.setPin(i, LOW);
        }
    }

    bus.writeState();
}
