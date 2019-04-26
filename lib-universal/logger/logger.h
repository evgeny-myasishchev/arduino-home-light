#ifndef LOGGER_H

#ifdef ARDUINO
#include <Print.h>
#endif

#include <stdarg.h>
#include <Timers.h>

namespace logger
{
    #define DEC 10

    class Output
    {
    public:
        virtual void print(const char*) = 0;
        virtual void print(char) = 0;
        virtual void print(int, int) = 0;
    };

    void printf(Output * out, const char *format, ...);

#ifdef ARDUINO
    class PrintOutput : public Output
    {
    private:
        Print * target;
    public:
        PrintOutput(Print*);

        void print(const char*);
        void print(char);
        void print(int, int);
    };
#endif

    class Logger
    {
    private:
        Output * output;
        Timers * timers;
    public:
        Logger(Timers * timers, Output * output);
        template<typename... Args> void log(const char * msg, Args... args) {
            logger::printf(this->output, "[INFO %d] ", this->timers->millis());
            logger::printf(this->output, msg, args...);
            printf(this->output, "\n");
        }
    };

    struct LoggingSystem {
        Output *output;
    };

    void setupLoggingSystem(Output *output);
} // namespace logger

#endif