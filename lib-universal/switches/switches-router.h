#ifndef SWITCHES_ROUTER_H
#define SWITCHES_ROUTER_H

#include <switches.h>
#include <vector>

class SwitchesRouter
{
private:
    /* data */
public:
    SwitchesRouter(std::vector<SwitchRoute> routes, SignalReader reader, SignalWriter writer);

    void setup();
    void processRoutes();
};

#endif