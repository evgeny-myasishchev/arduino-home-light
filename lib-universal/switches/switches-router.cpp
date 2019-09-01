#include <switches-router.h>

namespace switches
{

SwitchesRouter::SwitchesRouter(pstd::vector<SwitchRoute> * routes, SwitchRouterServices services)
{
    this->routes = routes;
    this->services = services;
}

void SwitchesRouter::processRoutes()
{
    for (int i = 0; i < routes->size(); i++)
    {
        auto route = (*routes)[i];
        auto status = route.status;
        const int signal = services.reader->read(i);
        if (signal == HIGH)
        {
            logger_log("Seeing signal for %d route", i);
        }
        services.switchSvc->processSignal(signal, status);
        if (status->stateChanged)
        {
            logger_log("Route %d status changed to %d", i, status->currentState);
            for (unsigned int addrNum = 0; addrNum < route.targetAddresses->size(); addrNum++)
            {
                const auto address = (*route.targetAddresses)[addrNum];
                logger_log("Writting %d state to %d[%d] address", status->currentState, address, addrNum);
                services.writer->write(address, status->currentState);
            }
            services.switchSvc->applyStateChange(status);
        }
    }
}

} // namespace switches