#include "logger.h"

namespace logger
{
    void printf(Output *out, const char *format, ...)
    {
        va_list args;

        // loop through format string
        for (; *format != 0; ++format)
        {
            if (*format == '%')
            {
                ++format;
                if (*format == '\0') break;
                if (*format == '%')
                {
                    out->print(*format);
                    continue;
                }
                // if (*format == 's')
                // {
                //     char *s = (char *)va_arg(args, int);
                //     out->print(s);
                //     continue;
                // }
                // if (*format == 'd' || *format == 'i')
                // {
                //     out->print(va_arg(args, int), DEC);
                //     continue;
                // }
                // if (*format == 'x')
                // {
                //     out->print(va_arg(args, int), HEX);
                //     continue;
                // }
                // if (*format == 'X')
                // {
                //     out->print("0x");
                //     out->print(va_arg(args, int), HEX);
                //     continue;
                // }
                // if (*format == 'b')
                // {
                //     out->print(va_arg(args, int), BIN);
                //     continue;
                // }
                // if (*format == 'B')
                // {
                //     out->print("0b");
                //     out->print(va_arg(args, int), BIN);
                //     continue;
                // }
                // if (*format == 'l')
                // {
                //     out->print(va_arg(args, long), DEC);
                //     continue;
                // }

                // if (*format == 'c')
                // {
                //     out->print(va_arg(args, int));
                //     continue;
                // }
                // if (*format == 't')
                // {
                //     if (va_arg(args, int) == 1)
                //     {
                //         out->print("T");
                //     }
                //     else
                //     {
                //         out->print("F");
                //     }
                //     continue;
                // }
                // if (*format == 'T')
                // {
                //     if (va_arg(args, int) == 1)
                //     {
                //         out->print("true");
                //     }
                //     else
                //     {
                //         out->print("false");
                //     }
                //     continue;
                // }
            }
            out->print(*format);
        }
    }
}