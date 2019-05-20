#ifndef SWITCHES_ROUTER_H
#define SWITCHES_ROUTER_H

#include <switches.h>
#include <switch-service.h>
#include <pstd.h>

namespace switches
{

struct SwitchRouterServices
{
public:
    SignalReader * reader;
    SignalWriter * writer;
    SwitchService * switchSvc;

    SwitchRouterServices() {}

    SwitchRouterServices(SignalReader * reader, SignalWriter * writer, SwitchService * svc) {
        this->reader = reader;
        this->writer = writer;
        this->switchSvc = svc;
    }
};

class SwitchesRouter
{
private:
    /* data */
public:
    SwitchesRouter(pstd::vector<SwitchRoute> route, SwitchRouterServices services);

    void setup();
    void processRoutes();
};

}
#endif