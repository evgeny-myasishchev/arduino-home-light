#include <Arduino.h>
#include "switches.h"
#include "switches-router.h"
#include "switch-service.h"

using namespace switches;

PCF8574IO io(0x24, 4, 0x20, 4);
SwitchesRouter *router;

SwitchRoute createRoute(int targetAddress)
{
    int route1Targets[] = {targetAddress};
    SwitchRoute route(new SwitchStatus(), new pstd::vector<int>(route1Targets));
    return route;
}

pstd::vector<SwitchRoute>* setupTestRoutes()
{
    int allAddresses[] = {
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23,
    };
    SwitchRoute allRoute(new SwitchStatus(), new pstd::vector<int>(allAddresses));

    SwitchRoute routesArray[] = {
        // relay0
        createRoute(0),
        createRoute(1),
        createRoute(2),
        createRoute(3),
        createRoute(4),
        createRoute(5),
        createRoute(6),
        createRoute(7),

        // relay1
        createRoute(8),
        createRoute(9),
        createRoute(10),
        createRoute(11),
        allRoute,
        createRoute(13),
        createRoute(14),
        createRoute(15),

        // relay2
        createRoute(16),
        createRoute(17),
        createRoute(18),
        createRoute(19),
        createRoute(20),
        createRoute(21),
        createRoute(22),
        createRoute(23),

        // relay3
        // allRoute,
        createRoute(24),
        createRoute(25),
        createRoute(26),
        createRoute(27),
        createRoute(28),
        createRoute(29),
        createRoute(30),
        createRoute(31),
    };
    return new pstd::vector<SwitchRoute>(routesArray);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    logger_setup(&Serial);

    auto routes = setupTestRoutes();

    auto switchService = SwitchRouterServices(
            &io,
            &io,
            new PushButtonSwitchService(SwitchServiceConfig()));

    router = new SwitchesRouter(routes, switchService);

    io.init();

    logger_log("Controller initialized. Total routes: %d", routes->size());
}

void loop()
{
    router->processRoutes();
}
