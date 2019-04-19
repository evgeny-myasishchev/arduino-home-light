#ifndef LOGGER_H

#include <Print.h>
#include <stdarg.h>

namespace logger
{
    class Output
    {
    public:
        virtual void print(const char*) = 0;
        virtual void print(char) = 0;
        virtual void print(int, int) = 0;
    };

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

    struct LoggingSystem {
        Output *output;
    };

    void setupLoggingSystem(Output *output);

    void printf(Output * out, const char *format, ...);

} // namespace logger

#endif