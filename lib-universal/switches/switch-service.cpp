#include <switch-service.h>

namespace switches
{

SwitchService::SwitchService(SwitchServiceConfig cfg)
{
    this->cfg = cfg;
    logger_log("Init switch service: minSignalDurationMs=%d, minSignalIterations=%d",
               cfg.minSignalDurationMs,
               cfg.minSignalIterations);
}

PushButtonSwitchService::PushButtonSwitchService(SwitchServiceConfig cfg) : SwitchService(cfg)
{
}

void PushButtonSwitchService::processSignal(int signal, SwitchStatus *switchStatus)
{
    service_log("Processing signal %d, seen times: %d, since: %d", signal, switchStatus->seenSignalTimes, switchStatus->seenSignalSince);
    if (signal == HIGH)
    {
        switchStatus->seenSignalTimes += 1;
        unsigned long now = cfg.timers->millis();
        if (switchStatus->seenSignalSince == 0)
        {
            service_log("Seen signal for a first time, now is: %d", now);
            switchStatus->seenSignalSince = now;
        };

        const unsigned int signalDuration = now - switchStatus->seenSignalSince;

        if (switchStatus->stateChanged)
        {
            service_log("The state got already changed to %d", switchStatus->currentState);
            return;
        }

        if (switchStatus->seenSignalTimes >= cfg.minSignalIterations &&
            signalDuration >= cfg.minSignalDurationMs)
        {

            switchStatus->stateChanged = true;
            switchStatus->currentState = switchStatus->currentState == LOW ? HIGH : LOW;
            service_log("State change detected. Signal duration: %d, new state: %d", signalDuration, switchStatus->currentState);
        }
    }
    else
    {
        switchStatus->stateChanged = false;
        switchStatus->seenSignalTimes = 0;
        switchStatus->seenSignalSince = 0;
    }
}

void PushButtonSwitchService::applyStateChange(SwitchStatus *switchStatus)
{
}

} // namespace switches