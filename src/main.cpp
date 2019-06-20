#include <Arduino.h>
#include "switches.h"

switches::PCF8574IO io(0x20, 2, 0x23, 2);

void setup() {
    io.init();
}

void loop() {
}
