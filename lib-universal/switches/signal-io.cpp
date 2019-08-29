#include <switches.h>

#ifdef ARDUINO

namespace switches
{

PCF8574 **setupBoards(const int boardsNum, uint8_t initialAddress, uint8_t initialState)
{
    auto readerBoards = new PCF8574 *[boardsNum];
    for (size_t i = 0; i < boardsNum; i++)
    {
        const auto boardAddr = initialAddress++;
        const auto board = new PCF8574(boardAddr);
        // logger_log("Setup board %d", boardAddr);
        board->begin(initialState);
        readerBoards[i] = board;
    }
    return readerBoards;
}

PCF8574IO::PCF8574IO(
    const uint8_t readerStartAddr,
    const uint8_t readerBoardsNum,
    const uint8_t writerStartAddr,
    const uint8_t writerBoardsNum)
{
    this->readerStartAddr = readerStartAddr;
    this->readerBoardsNum = readerBoardsNum;
    this->writerStartAddr = writerStartAddr;
    this->writerBoardsNum = writerBoardsNum;
}

void PCF8574IO::init()
{
    this->readerBoards = setupBoards(this->readerBoardsNum, this->readerStartAddr, 0xFF);
    this->writerBoards = setupBoards(this->writerBoardsNum, this->writerStartAddr, 0xFF);
}

int PCF8574IO::read(int channel)
{
    const uint8_t boardNum = channel / 8;
    const uint8_t pinNumber = channel % 8;


    // TODO: Check and investigate overflow behavior
    const auto board = this->readerBoards[boardNum];

    // Reversing since default is HIGH and relays are HIGH closed
    // But other logic depends on LOW
    const auto signal = board->read(pinNumber);

    // logger_log("Reading board %d, pin %d, pinVal %d", boardNum, pinNumber, signal);

    return signal == HIGH ? LOW : HIGH;
}

void PCF8574IO::write(int address, int state)
{
    const uint8_t boardNum = address / 8;
    const uint8_t pinNumber = address % 8;
    // TODO: Check and investigate overflow behavior
    auto board = this->writerBoards[boardNum];

    // Reversing since default is HIGH and relays are HIGH closed
    // But other logic depends on LOW
    const auto reversedState = state == HIGH ? LOW : HIGH;

    board->write(pinNumber, reversedState);
}

} // namespace switches

#endif