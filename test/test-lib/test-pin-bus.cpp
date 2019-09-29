#include "test-pin-bus.h"

TestPinBus::TestPinBus(const byte busSize) : PinBus(busSize)
{
}

void TestPinBus::readState()
{
    for (size_t i = 0; i < this->getBusSize(); i++)
    {
        this->setStateByte(i, pendingTestState[i]);
    }
}

void TestPinBus::writeState()
{
    for (size_t i = 0; i < this->getBusSize(); i++)
    {
        pendingTestState[i] = this->getStateByte(i);
    }
}