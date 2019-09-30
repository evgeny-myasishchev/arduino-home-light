#ifndef V2_SWITCH
#define V2_SWITCH

namespace v2
{
#include <arduino-compat.h>
#include <array-ptr.h>

enum SwitchType
{
    Push = 0, // Will change state when switch pushed
    // TODO
    // PushOff = 1, // Same as Push but always do off
    Toggle = 2, // Will keep exact state as switch state
};

struct Switch
{
    SwitchType type;
    byte state;
    byte pendingState;
    bool stateChanged;
    unsigned int seenSignalTimes;
    unsigned int seenSignalSince;

    byte switchAddress;
    // ArrayPtr targetAddresses;
};

} // namespace v2

#endif