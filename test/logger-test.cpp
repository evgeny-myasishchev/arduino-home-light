#include <gtest/gtest.h>
#include <logger.h>

namespace {

    class MockOutput : public logger::Output 
    {
        private:
            std::string result;
        public:
            std::string currentOutput();

            void print(const char*);
            void print(char);
            void print(int, int);

            void clean();
    };

    std::string MockOutput::currentOutput() {
        return result;
    }

    void MockOutput::print(const char *val) {
        result += val;
    }

    void MockOutput::print(const char val) {
        result += val;
    }

    void MockOutput::print(int val, int base) {
        result += val;
    }

    void MockOutput::clean() {
        result = "";
    }

    TEST(logger, printf) {
        MockOutput out;
        logger::printf(&out, "Regular message");
        EXPECT_EQ("Regular message", out.currentOutput());
        out.clean();

        logger::printf(&out, "Encoded %%");
        EXPECT_EQ("Encoded %", out.currentOutput());
        out.clean();

        // logger::printf(&out, "String params %s, %s", "str1", "str2");
        // EXPECT_EQ("String params str1, str2", out.currentOutput());
        // out.clean();

        // logger::printf(&out, "String params %s, %s", "str1", "str2");
        // EXPECT_EQ("String params str1, str2", out.currentOutput());
        // out.clean();

        // logger::printf(&out, "String params %");
        // EXPECT_EQ("String params str2, str2", out.currentOutput());
        // out.clean();
    }
} // namespace
