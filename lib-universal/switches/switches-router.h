#ifndef SWITCHES_ROUTER_H
#define SWITCHES_ROUTER_H

#include <switches.h>
#include <switch-service.h>
#include <pstd.h>

namespace switches
{

struct SwitchRouterServices
{
    SignalReader * reader;
    SignalWriter * writer;
    SwitchService * switchSvc;
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