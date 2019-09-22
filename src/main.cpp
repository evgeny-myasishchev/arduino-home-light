#include <arduino-compat.h>
#include <logger.h>
#include <pin-bus.h>

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    logger_setup(&Serial);

    logger_log("Controller initialized.");
}

void loop()
{
}
