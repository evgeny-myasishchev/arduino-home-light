#include "gtest/gtest.h"
#include <iostream>
#include <fstream> 
#include "logger.h"

class FileOutput : public logger::Output
{
private:
  std::ofstream * output;

public:
  FileOutput(std::ofstream * output) {
    this->output = output;
  }

  void print(const char *msg)
  {
    *output << msg;
  }
  void print(char c)
  {
    *output << c;
  }
  void print(int v, int b)
  {
    *output << v;
  }
};

int main(int argc, char **argv)
{
  std::srand(std::time(nullptr));
  ::testing::InitGoogleTest(&argc, argv);
  std::ofstream testLogOutput ("test.log", std::ofstream::out | std::ofstream::trunc);
  logger::setupLoggingSystem(new FileOutput(&testLogOutput));
  return RUN_ALL_TESTS();
}