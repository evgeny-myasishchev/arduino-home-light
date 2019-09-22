#include <arduino-compat.h>
#include <logger.h>
#include <pin-bus.h>

using namespace v2;

PCF8574Bus bus(6);

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    logger_setup(&Serial);

    bus.setup();

    logger_log("Controller initialized.");
}

void loop()
{
    bus.readState();

    bus.writeState();
}
