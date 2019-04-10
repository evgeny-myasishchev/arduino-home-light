#include "FakeTimers.h"

void FakeTimers::setMillis(unsigned long value) {
    this->currentMillis = value;
}

unsigned long FakeTimers::millis() {
    return this->currentMillis;
}