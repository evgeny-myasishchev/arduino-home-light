#ifndef LOGGER_H

#include <Print.h>
#include <stdarg.h>

namespace logger
{
    #define DEC 10
    #define HEX 16
    #define OCT 8
    #define BIN 2

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

    void printf(Output * out, const char *format, ...);

} // namespace logger

#endif