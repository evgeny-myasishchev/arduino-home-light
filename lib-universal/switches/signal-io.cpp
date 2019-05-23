#include <switches.h>

#ifdef ARDUINO

namespace switches
{

CD74HC4067SignalReader::CD74HC4067SignalReader(CD74HC4067Config cfg)
{
    this->cfg = cfg;
    this->mux = new CD74HC4067(cfg.s0, cfg.s1, cfg.s2, cfg.s3);
}

void CD74HC4067SignalReader::init()
{
    pinMode(cfg.s0, OUTPUT);
    pinMode(cfg.s1, OUTPUT);
    pinMode(cfg.s2, OUTPUT);
    pinMode(cfg.s3, OUTPUT);
    digitalWrite(cfg.s0, LOW);
    digitalWrite(cfg.s1, LOW);
    digitalWrite(cfg.s2, LOW);
    digitalWrite(cfg.s3, LOW);

    pinMode(cfg.en, OUTPUT);
    pinMode(cfg.sig, INPUT_PULLUP);
    digitalWrite(cfg.en, LOW);
}

int CD74HC4067SignalReader::read(int channel)
{
    mux->channel(channel);
    return digitalRead(cfg.sig);
}

} // namespace switches

#endif