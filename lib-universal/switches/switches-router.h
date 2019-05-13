#ifndef SWITCHES_ROUTER_H
#define SWITCHES_ROUTER_H

#include <switches.h>

class SwitchesRouter
{
private:
    /* data */
public:
    SwitchesRouter(SignalReader reader, SignalWriter writer);

    void setup();
    void processRoutes();
};

#endif