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

void PinBus::setStateByte(const uint8_t byteIndex, const uint8_t state)
{
}

const uint8_t PinBus::getStateByte(const uint8_t byteIndex)
{
}

const uint8_t PinBus::getPin(const uint8_t byteIndex, const uint8_t bit) const
{
    const auto byte = this->busState[byteIndex];
    return bitRead(byte, bit);
}

const void PinBus::setPin(const uint8_t byteIndex, const uint8_t bit, uint8_t state)
{
}

} // namespace v2