#include "FakeTimers.h"

void FakeTimers::setMillis(unsigned long value) {
    this->currentMillis = value;
}

void FakeTimers::advance(unsigned long step) {
    this->currentMillis += step;
}

unsigned long FakeTimers::millis() {
    return this->currentMillis;
}