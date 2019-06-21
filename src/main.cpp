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

void setup()
{
    Serial.begin(9600);
    while(!Serial) {}
    logger_setup(&Serial);

    SwitchRoute routesArray[] = {
        createRoute(0),
        createRoute(1),
        createRoute(2),
        createRoute(3),
        createRoute(4),
        createRoute(5),
        createRoute(6),
        createRoute(7)};
    pstd::vector<SwitchRoute> routes(routesArray);

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
