#include <gtest/gtest.h>
#include <arduino-compat.h>
#include "test-lib/random.h"
#include <pin-bus.h>

namespace
{

class TestPinBus : public v2::PinBus
{

public:
    TestPinBus(const uint8_t busSize) : PinBus(busSize)
    {
    }

    void readState()
    {
    }

    void writeState()
    {
    }
};

TEST(V2PinBus, initialState)
{
    const uint8_t maxBytes = test::randomNumber(5, 10);
    const TestPinBus bus(maxBytes);
    for (size_t byteIndex = 0; byteIndex < maxBytes; byteIndex++)
    {
        const auto pin = bus.getPin(byteIndex, 0);
        EXPECT_EQ(LOW, pin);
    }
}

} // namespace
