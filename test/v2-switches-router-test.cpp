#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <arduino-compat.h>
#include <stdio.h>
#include <random>
#include <switches-router-v2.h>
#include "test-lib/test-pin-bus.h"

namespace
{

using namespace v2;

class MockSwitchService : public SwitchService
{
public:
    MockSwitchService() : SwitchService(SwitchServiceConfig{}) {}
    MOCK_METHOD(void, processSignal, (uint8_t signal, Switch *sw));
    MOCK_METHOD(void, applyStateChange, (Switch *sw));
};

class V2SwitchesRouterTest : public ::testing::Test
{
public:
    PinBus *bus;
    SwitchesRouter *router;
    testing::NiceMock<MockSwitchService> *pushBtnSwitchSvc;
    testing::NiceMock<MockSwitchService> *toggleBtnSwitchSvc;
protected:
    void SetUp() override
    {
        bus = new TestPinBus(1);
        pushBtnSwitchSvc = new testing::NiceMock<MockSwitchService>();
        toggleBtnSwitchSvc = new testing::NiceMock<MockSwitchService>();
        SwitchRouterServices services{
            .bus = bus,
            .pushBtnSwitchSvc = pushBtnSwitchSvc,
            .toggleBtnSwitchSvc = toggleBtnSwitchSvc,
        };
        router = new SwitchesRouter(services);
    }
    void TearDown() override
    {
        delete bus;
        delete router;
        delete toggleBtnSwitchSvc;
        delete pushBtnSwitchSvc;
    }
};

TEST_F(V2SwitchesRouterTest, processRoutesNoChanges)
{
    Switch route1;
    Switch route2;
    Switch route3;
    Switch* routesArray[] = {&route1, &route2, &route3};
    ArrayPtr<Switch*> routes(3, (Switch**)&routesArray);

    EXPECT_CALL((*pushBtnSwitchSvc), processSignal(0, &route1));
    EXPECT_CALL((*pushBtnSwitchSvc), processSignal(0, &route2));
    EXPECT_CALL((*pushBtnSwitchSvc), processSignal(0, &route3));

    router->processRoutes(routes);
}

} // namespace
