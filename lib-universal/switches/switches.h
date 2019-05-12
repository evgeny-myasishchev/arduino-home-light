#ifndef SWITCHES_H
#define SWITCHES_H

struct SwitchStatus
{
public:
    int currentState = 0;
    bool stateChanged = false;
    int seenSignalTimes = 0;
    unsigned int seenSignalSince = 0;

    SwitchStatus() {}

    SwitchStatus(
        int currentState,
        bool stateChanged,
        int seenSignalTimes,
        unsigned int seenSignalSince)
    {
        this->currentState = currentState;
        this->stateChanged = stateChanged;
        this->currentState = currentState;
        this->seenSignalTimes = seenSignalTimes;
        this->seenSignalSince = seenSignalSince;
    }
};

struct SwitchRoute 
{
public:
    // int outputAddresses[];
    SwitchStatus status;
};

#endif