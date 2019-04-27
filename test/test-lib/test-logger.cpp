#include "test-logger.h"
#include <iostream>

namespace test
{

void StdOutput::print(const char *msg)
{
    std::cout << msg;
}
void StdOutput::print(char c)
{
    std::cout << c;
}
void StdOutput::print(int v, int b)
{
    std::cout << v;
}

} // namespace test