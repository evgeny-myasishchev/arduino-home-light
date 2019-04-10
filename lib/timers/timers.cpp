#include <timers.h>
#include <Arduino.h>

unsigned long Timers::millis() {
    return ::millis();
}