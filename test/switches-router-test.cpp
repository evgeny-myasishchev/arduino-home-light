#include <switches.h>
#include <switch-service.h>
#include <switches-router.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <arduino-compat.h>
#include <stdio.h>
#include <random>

namespace
{

using namespace switches;
using namespace testing;

class MockSignalReader : public SignalReader
{
public:
    MOCK_METHOD1(read, int(int channel));
};

class MockSignalWriter : public SignalWriter
{
public:
    MOCK_METHOD2(write, void(int address, int state));
};

class MockSwitchService : public SwitchService
{
public:
    MockSwitchService() : SwitchService(SwitchServiceConfig{}) {
    }
    MOCK_METHOD2(processSignal, void(int signal, SwitchStatus *switchStatus));
    MOCK_METHOD1(applyStateChange, void(SwitchStatus *switchStatus));
};

class SwitchesRouterTest : public ::testing::Test
{
protected:
    StrictMock<MockSignalReader> signalReader;
    StrictMock<MockSignalWriter> signalWriter;
    StrictMock<MockSwitchService> switchService;

    SwitchRouterServices services = SwitchRouterServices(&signalReader, &signalWriter, &switchService);

    void SetUp() override
    {
        // services = SwitchRouterServices(&signalReader, &signalWriter, &switchService);
    }
};

TEST_F(SwitchesRouterTest, processRoutesNoSignal)
{
    SwitchStatus status1;
    SwitchStatus status2;
    SwitchStatus status3;

    const int routesNum = 3;
    SwitchRoute routeValues[routesNum] = {
        SwitchRoute(&status1),
        SwitchRoute(&status2),
        SwitchRoute(&status3)
    };

    pstd::vector<SwitchRoute> routes(routeValues);
    SwitchesRouter router(routes, services);

    EXPECT_CALL(signalReader, read(0)).WillOnce(Return(0));
    EXPECT_CALL(switchService, processSignal(0, &status1));
    EXPECT_CALL(signalReader, read(1));
    EXPECT_CALL(switchService, processSignal(0, &status2));
    EXPECT_CALL(signalReader, read(2)).WillOnce(Return(0));;
    EXPECT_CALL(switchService, processSignal(0, &status3));

    router.processRoutes();
}

TEST_F(SwitchesRouterTest, processRoutesSeenSignalNoChanges)
{
    SwitchStatus status1;
    SwitchStatus status2;
    SwitchStatus status3;

    const int routesNum = 3;
    SwitchRoute routeValues[routesNum] = {
        SwitchRoute(&status1),
        SwitchRoute(&status2),
        SwitchRoute(&status3)
    };

    pstd::vector<SwitchRoute> routes(routeValues);
    SwitchesRouter router(routes, services);

    EXPECT_CALL(signalReader, read(0)).WillOnce(Return(1));
    EXPECT_CALL(switchService, processSignal(1, &status1));
    EXPECT_CALL(signalReader, read(1));
    EXPECT_CALL(switchService, processSignal(0, &status2));
    EXPECT_CALL(signalReader, read(2)).WillOnce(Return(1));;
    EXPECT_CALL(switchService, processSignal(1, &status3));

    router.processRoutes();
}

} // namespace
