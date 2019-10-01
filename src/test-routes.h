#include <switch.h>

using namespace v2;

#define RELAY_BOARDS 2
#define INPUT_BOARDS 2

ArrayPtr<Switch *> createTestRoutes(const byte relayBoards, const byte inputBoards)
{
    const byte switchesOffset = relayBoards * 8;
    const byte switchesCount = inputBoards * 8;

    Switch * *routesArray = new Switch*[switchesCount];
    for (byte switchNr = 0; switchNr < switchesCount; switchNr++)
    {
        Switch* route = (new Switch())
            ->withSwitchAddress(switchesOffset + switchNr)
            ->withTargetAddresses(1, new byte[1]{switchNr});
        routesArray[switchNr] = route;
    }
    return ArrayPtr<Switch *>(switchesCount, routesArray);
}