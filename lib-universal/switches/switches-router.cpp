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
    logger_log("Procssing routes");
    for (int i = 0; i < routes.size(); i++)
    {
        auto route = routes[i];
        auto status = route.status;
        const int signal = services.reader->read(i);
        services.switchSvc->processSignal(signal, status);
        if (status->stateChanged)
        {
            logger_log("Route %d status changed to %d", i, status->currentState);
            for (int addrNum = 0; addrNum < route.targetAddresses.size(); addrNum++)
            {
                auto address = route.targetAddresses[addrNum];
                logger_log("Writting %d state to %d address", status->currentState, address);
                services.writer->write(address, status->currentState);
            }
            services.switchSvc->applyStateChange(status);
        }
    }
}

} // namespace switches