#include <switches-router-v2.h>

namespace v2
{
SwitchesRouter::SwitchesRouter(SwitchRouterServices services)
{
    this->services = services;
}

void SwitchesRouter::processRoutes(ArrayPtr<Switch *> routes)
{
    for (size_t i = 0; i < routes.size(); i++)
    {
        Switch *sw = routes[i];
        SwitchService *swSvc = NULL;
        switch (sw->type)
        {
        case SwitchType::Push:
            swSvc = this->services.pushBtnSwitchSvc;
            break;
        case SwitchType::Toggle:
            swSvc = this->services.toggleBtnSwitchSvc;
            break;
        default:
            break;
        }
        if (swSvc != NULL)
        {
            const auto switchState = this->services.bus->getPin(sw->switchAddress);
            router_log("Processing switch: %d, address: %d, state: %d", i, sw->switchAddress, switchState);
            swSvc->processSignal(switchState, sw);
        }
        else
        {
            logger_log("Unexpected switch type: %d at index: %d", sw->type, i);
        }
    }
}

} // namespace v2