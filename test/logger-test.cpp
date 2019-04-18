#include <gtest/gtest.h>
#include <logger.h>
#include <stdio.h>

namespace
{

class MockOutput : public logger::Output
{
    private:
        std::string result;
    public:
        std::string currentOutput();

        void print(const char*);
        void print(char);
        // void print(int, int);

        void clean();
};

std::string MockOutput::currentOutput() {
    return this->result;
}

void MockOutput::print(const char* val) {
    result += val;
}

void MockOutput::print(const char val) {
    result += val;
}

void MockOutput::clean() {
    result = "";
}

void formatString(logger::Output * out, const char *format, ...)
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
                out->print(va_arg(args, char*));
                continue;
            }
        }
        out->print((char)*format);
    }
}

    TEST(logger, printf)
    {
        MockOutput out;
        // std::string result = formatString(&out, "Size of char: %s", "hello");
        // std::cout << "result: " << out.currentOutput() << "\n";
        // out.clean();

        logger::printf(&out, "Regular message");
        EXPECT_EQ("Regular message", out.currentOutput());
        out.clean();

        // formatString(&out, "Encoded %%");
        // EXPECT_EQ("Encoded %", out.currentOutput());
        // out.clean();

        logger::printf(&out, "Single string param: %s", "str1");
        EXPECT_EQ("Single string param: str1", out.currentOutput());
        out.clean();

        // logger::printf(&out, "String params %s, %s", "str1", "str2");
        // EXPECT_EQ("String params str1, str2", out.currentOutput());
        // out.clean();

        // logger::printf(&out, "String params %");
        // EXPECT_EQ("String params str2, str2", out.currentOutput());
        // out.clean();
    }
} // namespace
