#ifndef V2_SWITCHES_ROUTER_H
#define V2_SWITCHES_ROUTER_H

#include <array-ptr.h>
#include <pin-bus.h>
#include <switch-service-v2.h>

namespace v2
{

struct SwitchRouterServices
{
    PinBus *bus;
    SwitchService *pushBtnSwitchSvc;
    SwitchService *toggleBtnSwitchSvc;
};

class SwitchesRouter
{
public:
    SwitchesRouter(SwitchRouterServices);
    void processRoutes(ArrayPtr<Switch *> routes);
};

} // namespace v2
#endif