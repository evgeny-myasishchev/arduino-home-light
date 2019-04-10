#include <Arduino.h>
#include <PushButtonSwitch.h>

PushButtonSwitch::PushButtonSwitch(pushButtonSwitchConfig cfg) {
    currentState = LOW;
    stateChanged = false;
    seenSignalTimes = 0;
    seenSignalSince = 0;
    this->cfg = cfg;
}

int PushButtonSwitch::getState() {
    return LOW;
}

bool PushButtonSwitch::hasStateChanged() {
    return stateChanged;
}

void PushButtonSwitch::processCurrentLevel(int level) {
    if(level == HIGH) {
        seenSignalTimes += 1;
        unsigned long now = cfg.timers->millis();
        if(seenSignalSince == 0) seenSignalSince = now;

        if(seenSignalTimes >= cfg.minSignalIterations && (now - seenSignalSince) >= cfg.minSignalDurationMs) {
            stateChanged = true;
            currentState = currentState == LOW ? HIGH : LOW;
        }
    }
}

void PushButtonSwitch::applyCurrentState() {
    stateChanged = false;
}