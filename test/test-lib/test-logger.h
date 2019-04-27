#ifndef test_logger
#define test_logger

#include "logger.h"

namespace test
{

class StdOutput : public logger::Output
{
public:
    void print(const char *);
    void print(char);
    void print(int, int);
};

#define setup_test_logger() logger::setupLoggingSystem(new test::StdOutput())

} // namespace test

#endif