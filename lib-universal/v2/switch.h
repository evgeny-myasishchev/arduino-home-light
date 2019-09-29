#ifndef V2_SWITCH
#define V2_SWITCH

namespace v2
{
#include <arduino-compat.h>
#include <array-ptr.h>

struct Switch
{
public:
    byte state = 0;
    byte pendingState = 0;
    bool stateChanged = false;
    unsigned int seenSignalTimes = 0;
    unsigned int seenSignalSince = 0;
    
    // ArrayPtr targetAddresses;

    Switch() {}

    Switch(
        byte state,
        bool stateChanged,
        unsigned int seenSignalTimes,
        unsigned int seenSignalSince)
    {
        this->state = state;
        this->stateChanged = stateChanged;
        this->state = state;
        this->seenSignalTimes = seenSignalTimes;
        this->seenSignalSince = seenSignalSince;
    }
};

} // namespace v2

#endif