#ifndef V2_SWITCH
#define V2_SWITCH

namespace v2
{

#include <stdint.h>

struct Switch
{
public:
    uint8_t currentState = 0;
    bool stateChanged = false;
    unsigned int seenSignalTimes = 0;
    unsigned int seenSignalSince = 0;

    Switch() {}

    Switch(
        uint8_t currentState,
        bool stateChanged,
        unsigned int seenSignalTimes,
        unsigned int seenSignalSince)
    {
        this->currentState = currentState;
        this->stateChanged = stateChanged;
        this->currentState = currentState;
        this->seenSignalTimes = seenSignalTimes;
        this->seenSignalSince = seenSignalSince;
    }
};

} // namespace v2

#endif