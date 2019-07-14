#ifndef SwitchService_h
#define SwitchService_h

#include <switches.h>

namespace switches
{

#ifdef SWITCH_SERVICE_VERBOSE
#define service_log logger_log
#else
#define service_log
#endif

struct SwitchServiceConfig
{
    // Min number of ms a signal should be seen
    // to consider button pressed or switched
    unsigned int minSignalDurationMs = 50;

    // Min number of times we've seen the signal
    // to take it in action
    int minSignalIterations = 3;

    Timers *timers = new Timers();

    SwitchServiceConfig() {}

    SwitchServiceConfig(
        int minSignalDurationMs,
        int minSignalIterations,
        Timers *timers)
    {
        this->minSignalDurationMs = minSignalDurationMs;
        this->minSignalIterations = minSignalIterations;
        this->timers = timers;
    }
};

class SwitchService
{
protected:
    SwitchServiceConfig cfg;

public:
    SwitchService(SwitchServiceConfig cfg);
    virtual void processSignal(int signal, SwitchStatus *switchStatus) = 0;
    virtual void applyStateChange(SwitchStatus *switchStatus) = 0;
};

/*
Push button alg:

1) If see signal for more than Xms and more than Ytimes, toggle signal state
2) Keep the state unchanged if continuing seeing the signal
3) Keep the state unchanged if stopped seeing the signal
4) Go to 1 if started seeing the signal
 */
class PushButtonSwitchService : public SwitchService
{
public:
    PushButtonSwitchService(SwitchServiceConfig cfg);
    void processSignal(int signal, SwitchStatus *switchStatus);
    void applyStateChange(SwitchStatus *switchStatus);
};

} // namespace switch_service

#endif