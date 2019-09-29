#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <arduino-compat.h>
#include <stdio.h>
#include <random>
#include <switches-router-v2.h>

namespace
{

using namespace v2;

class V2SwitchesRouterTest : public ::testing::Test
{
public:
    SwitchesRouter *router;
protected:
    void SetUp() override
    {
        SwitchRouterServices services;
        router = new SwitchesRouter(services);
    }
    void TearDown() override
    {
        delete router;
    }
};

TEST_F(V2SwitchesRouterTest, processRoutesNoSignal)
{
    Switch route1;
    Switch route2;
    Switch route3;
    Switch* routesArray[] = {&route1, &route2, &route3};
    ArrayPtr<Switch*> routes(3, (Switch**)&routesArray);
    router->processRoutes(routes);
}

} // namespace
