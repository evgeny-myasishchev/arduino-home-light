#include <Arduino.h>
#include "switches.h"

switches::PCF8574IO io(0x20, 1, 0x21, 1);

void setup() {
    io.init();
}

void loop() {
    for (size_t i = 0; i < 8; i++)
    {
        auto state = io.read(i);
        io.write(i, state);
    }
}
