#include <Arduino.h>
#include "switches.h"
#include "switches-router.h"
#include "switch-service.h"

using namespace switches;

PCF8574IO io(0x20, 1, 0x21, 1);
SwitchesRouter *router;

SwitchRoute createRoute(int targetAddress)
{
    int route1Targets[] = {targetAddress};
    SwitchRoute route(new SwitchStatus(), pstd::vector<int>(route1Targets));
    return route;
}

pstd::vector<SwitchRoute> setupTestRoutes()
{
    SwitchRoute routesArray[] = {
        createRoute(0),
        createRoute(1),
        createRoute(2),
        createRoute(3),
        createRoute(4),
        createRoute(5),
        createRoute(6),
        createRoute(7)};
    return pstd::vector<SwitchRoute>(routesArray);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    logger_setup(&Serial);

    pstd::vector<SwitchRoute> routes = setupTestRoutes();

    router = new SwitchesRouter(
        pstd::vector<SwitchRoute>(routes),
        SwitchRouterServices(
            &io,
            &io,
            new PushButtonSwitchService(SwitchServiceConfig())));
    io.init();

    logger_log("Controller init. Total routes: %d", routes.size());
}

void loop()
{
    router->processRoutes();
}
