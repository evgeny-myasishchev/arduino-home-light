#ifndef SIGNAL_READER_H
#define SIGNAL_READER_H

class SignalReader
{
public:
    virtual void read(int channel) = 0;
};


#endif