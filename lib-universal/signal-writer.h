#ifndef SIGNAL_WRITER_H
#define SIGNAL_WRITER_H

class SignalWriter
{
public:
    virtual void write(int channel, int state) = 0;
};


#endif