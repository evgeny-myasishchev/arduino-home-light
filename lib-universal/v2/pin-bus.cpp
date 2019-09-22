#include <pin-bus.h>

#include <string>
#include <iostream>

namespace v2
{

PinBus::PinBus(const uint8_t busSize)
{
    this->busSize = busSize;
    this->busState = new uint8_t[busSize]();
}

PinBus::~PinBus()
{
    delete this->busState;
}

const uint8_t PinBus::getBusSize()
{
    return busSize;
}

void PinBus::setStateByte(const uint8_t byteIndex, const uint8_t state)
{
    if (byteIndex >= this->busSize)
    {
        return;
    }
    this->busState[byteIndex] = state;
}

const uint8_t PinBus::getStateByte(const uint8_t byteIndex)
{
    return this->busState[byteIndex];
}

const uint8_t PinBus::getPin(const uint8_t byteIndex, const uint8_t bit) const
{
    if (byteIndex >= this->busSize)
    {
        return LOW;
    }
    const auto byte = this->busState[byteIndex];
    return bitRead(byte, bit);
}

const void PinBus::setPin(const uint8_t byteIndex, const uint8_t bit, uint8_t state)
{
    if (byteIndex >= this->busSize)
    {
        return;
    }
    bitWrite(this->busState[byteIndex], bit, state);
}

} // namespace v2