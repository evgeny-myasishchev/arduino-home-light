#include <switch-service.h>
#include <arduino-compat.h>
#include <logger.h>

// #define SWITCH_SERVICE_VERBOSE

namespace switch_service {

#ifdef SWITCH_SERVICE_VERBOSE
#define service_log logger_log
#else
#define service_log
#endif

SwitchService::SwitchService(SwitchServiceConfig cfg) {
    this->cfg = cfg;
}

PushButtonSwitchService::PushButtonSwitchService(SwitchServiceConfig cfg) : SwitchService(cfg) {
    
}

void PushButtonSwitchService::processSignal(int signal, SwitchStatus *switchStatus) {
    service_log("Processing signal %d", signal);
    if(signal == HIGH) {
        switchStatus->seenSignalTimes += 1;
        unsigned long now = cfg.timers->millis();
        if(switchStatus->seenSignalSince == 0) {
            service_log("Seen signal for a first time, now is: %d", now);
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

}