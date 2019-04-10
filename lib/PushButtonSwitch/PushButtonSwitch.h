#ifndef PushButton_h
#define PushButton_h

#include <Timers.h>

struct pushButtonSwitchConfig
{
    // Min number of ms a signal should be seen
    // to consider button pressed or switched
    unsigned int minSignalDurationMs;

    // Min number of times we've seen the signal
    // to take it in action
    int minSignalIterations;

    Timers * timers;

    pushButtonSwitchConfig(): 
        minSignalDurationMs(200), 
        minSignalIterations(10),
        timers(new Timers())
    {
    }
};

class PushButtonSwitch
{
private:
    int currentState;
    bool stateChanged;
    int seenSignalTimes;
    int seenSignalSince;
    pushButtonSwitchConfig cfg;

public:
    PushButtonSwitch(pushButtonSwitchConfig cfg);

    // Return state of a button (either LOW or HIGH)
    int getState();

    // Indicates wether state change recognised
    bool hasStateChanged();

    // 
    void processCurrentLevel(int level);

    // Make current state active
    void applyCurrentState();
};

#endif