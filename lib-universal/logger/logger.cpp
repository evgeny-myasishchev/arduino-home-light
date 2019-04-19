#include "logger.h"

namespace logger
{

PrintOutput::PrintOutput(Print* target) {
    this->target = target;
};

void PrintOutput::print(const char* msg) {
    this->target->print(msg);
}

void PrintOutput::print(char ch) {
    this->target->print(ch);
}

void PrintOutput::print(int value, int format) {
    this->target->print(value, format);
}

void printf(Output *out, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    //
    // loop through format string
    for (; *format != 0; ++format)
    {
        if (*format == '%')
        {
            ++format;
            if (*format == '\0')
                break;
            if (*format == '%')
            {
                continue;
            }
            if (*format == 's')
            {
                out->print(va_arg(args, char *));
                continue;
            }
            if (*format == 'd' || *format == 'i')
            {
                out->print((int)va_arg(args, int), DEC);
                continue;
            }
        }
        out->print((char)*format);
    }
}
} // namespace logger