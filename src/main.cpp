#include <Arduino.h>
#include <logger.h>

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
