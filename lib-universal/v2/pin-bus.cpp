#include <pin-bus.h>

#include <string>
#include <iostream>

namespace v2
{

PinBus::PinBus(const byte busSize)
{
    this->busSize = busSize;
    this->busState = new byte[busSize]();
}

PinBus::~PinBus()
{
    delete this->busState;
}

const byte PinBus::getBusSize()
{
    return busSize;
}

void PinBus::setStateByte(const byte byteIndex, const byte state)
{
    if (byteIndex >= this->busSize)
    {
        return;
    }
    this->busState[byteIndex] = state;
}

const byte PinBus::getStateByte(const byte byteIndex)
{
    return this->busState[byteIndex];
}

const byte PinBus::getPin(const byte byteIndex, const byte bit) const
{
    if (byteIndex >= this->busSize)
    {
        return LOW;
    }
    const auto byte = this->busState[byteIndex];
    return bitRead(byte, bit);
}

const void PinBus::setPin(const byte byteIndex, const byte bit, byte state)
{
    if (byteIndex >= this->busSize)
    {
        return;
    }
    bitWrite(this->busState[byteIndex], bit, state);
}

} // namespace v2