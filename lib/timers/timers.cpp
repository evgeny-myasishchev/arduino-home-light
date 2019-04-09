#include <timers.h>
#include <Arduino.h>

nowMillisProc defaultNowMillisProc() {
    return &millis;
}