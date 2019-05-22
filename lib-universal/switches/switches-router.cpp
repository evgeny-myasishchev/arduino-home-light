#include <switches-router.h>

namespace switches
{

SwitchesRouter::SwitchesRouter(pstd::vector<SwitchRoute> routes, SwitchRouterServices services)
{
    this->routes = routes;
    this->services = services;
}

void SwitchesRouter::processRoutes()
{
    for(int i = 0; i < routes.size(); i++)
    {
        auto route = routes[i];
        const int signal = services.reader->read(i);
        services.switchSvc->processSignal(signal, route.status);
    }
}

}