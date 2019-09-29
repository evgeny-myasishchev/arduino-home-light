#include <switch-service-v2.h>

namespace v2
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

void PushButtonSwitchService::processSignal(uint8_t signal, Switch *sw)
{
    service_log("Processing signal %d, seen times: %d, since: %d", signal, sw->seenSignalTimes, sw->seenSignalSince);
    if (signal == HIGH)
    {
        sw->seenSignalTimes += 1;
        unsigned long now = cfg.timers->millis();
        if (sw->seenSignalSince == 0)
        {
            service_log("Seen signal for a first time, now is: %d", now);
            sw->seenSignalSince = now;
        };

        const unsigned int signalDuration = now - sw->seenSignalSince;

        if (sw->stateChanged)
        {
            service_log("The state got already changed to %d", sw->state);
            return;
        }

        if (sw->seenSignalTimes >= cfg.minSignalIterations &&
            signalDuration >= cfg.minSignalDurationMs)
        {
            sw->stateChanged = true;
            sw->state = sw->state == LOW ? HIGH : LOW;
            service_log("State change detected. Signal duration: %d, new state: %d", signalDuration, sw->state);
        }
    }
    else
    {
        sw->stateChanged = false;
        sw->seenSignalTimes = 0;
        sw->seenSignalSince = 0;
    }
}

void PushButtonSwitchService::applyStateChange(Switch *aSwitch)
{
}

ToggleButtonSwitchService::ToggleButtonSwitchService(SwitchServiceConfig cfg) : SwitchService(cfg)
{
}

void ToggleButtonSwitchService::processSignal(uint8_t signal, Switch *sw)
{
    service_log("Processing signal %d, seen times: %d, since: %d", signal, sw->seenSignalTimes, sw->seenSignalSince);
    if (signal == HIGH)
    {
        sw->seenSignalTimes += 1;
        unsigned long now = cfg.timers->millis();
        if (sw->seenSignalSince == 0)
        {
            service_log("Seen signal for a first time, now is: %d", now);
            sw->seenSignalSince = now;
        };

        const unsigned int signalDuration = now - sw->seenSignalSince;

        if (sw->stateChanged)
        {
            service_log("The state got already changed to %d", sw->state);
            return;
        }

        if (sw->seenSignalTimes >= cfg.minSignalIterations &&
            signalDuration >= cfg.minSignalDurationMs)
        {

            sw->stateChanged = true;
            sw->state = HIGH;
            service_log("State change detected. Signal duration: %d, new state: %d", signalDuration, sw->state);
        }
    }
    else
    {
        sw->stateChanged = false;
        sw->seenSignalTimes = 0;
        sw->seenSignalSince = 0;
    }
}

void ToggleButtonSwitchService::applyStateChange(Switch *sw)
{
    sw->stateChanged = false;
    sw->seenSignalTimes = 0;
    sw->seenSignalSince = 0;
}

} // namespace v2