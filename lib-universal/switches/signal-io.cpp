#include <switches.h>

#ifdef ARDUINO

namespace switches
{

PCF8574IO::PCF8574IO(
    const uint8_t readerStartAddr,
    const uint8_t readerBoardsNum,
    const uint8_t writerStartAddr,
    const uint8_t writerBoardsNum
    )
{
    this->readerStartAddr = readerStartAddr;
    this->writerStartAddr = writerStartAddr;
}

void PCF8574IO::init()
{
}

int PCF8574IO::read(int channel)
{
    const uint8_t boardNum = channel / 8;
    const uint8_t pinNumber = channel % 8;
}

void PCF8574IO::write(int address, int state)
{
}

} // namespace switches

#endif