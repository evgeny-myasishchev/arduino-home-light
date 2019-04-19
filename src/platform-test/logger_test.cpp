#include <ArduinoUnit.h>
#include <logger.h>

class MockOutput : public logger::Output
{
    private:
        String result;
    public:
        String currentOutput();

        void print(const char*);
        void print(char);
        // void print(int, int);

        void clean();
};

String MockOutput::currentOutput() {
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

test(logger_printf)
{
  MockOutput out;
  logger::printf(&out, "String with params: %s, %s", "str1", "str2");
  assertEqual("String with params: str1, str2", out.currentOutput());
  out.clean();
}