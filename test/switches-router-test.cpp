#include <switches.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <arduino-compat.h>
#include <stdio.h>
#include <random>

namespace
{

class MockSignalReader : public switches::SignalReader
{
public:
    MOCK_METHOD1(read, void(int channel));
};

class SwitchesRouterTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }
};

TEST_F(SwitchesRouterTest, processRoutes)
{
}

} // namespace
