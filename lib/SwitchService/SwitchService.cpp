#include <SwitchService.h>
#include <Arduino.h>
#include <ArduinoLog.h>

SwitchService::SwitchService(SwitchServiceConfig cfg) {
    this->cfg = cfg;
}

PushButtonSwitchService::PushButtonSwitchService(SwitchServiceConfig cfg) : SwitchService(cfg) {
    
}

void PushButtonSwitchService::processSignal(int signal, SwitchStatus *switchStatus) {
    Log.notice("Processing signal %d, cfg.minSignalIterations: %d" CR, signal, cfg.minSignalIterations);
    if(signal == HIGH) {
        switchStatus->seenSignalTimes += 1;
        unsigned long now = cfg.timers->millis();
        if(switchStatus->seenSignalSince == 0) {
            Log.trace("Seen signal for a first time, now is: %d" CR, now);
            switchStatus->seenSignalSince = now;
        };

        if(switchStatus->seenSignalTimes >= cfg.minSignalIterations && 
            (now - switchStatus->seenSignalSince) >= cfg.minSignalDurationMs) {
            switchStatus->stateChanged = true;
            switchStatus->currentState = switchStatus->currentState == LOW ? HIGH : LOW;
        }
    }
}

void PushButtonSwitchService::applyStateChange(SwitchStatus *switchStatus) {
}
