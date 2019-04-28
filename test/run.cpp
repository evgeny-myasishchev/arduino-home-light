#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include "logger.h"

class FileOutput : public logger::Output
{
private:
  std::ofstream *output;

public:
  FileOutput(std::ofstream *output)
  {
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

class Environment : public ::testing::Environment
{
  // Override this to define how to set up the environment.
  void SetUp()
  {
    logger_log("test start");
  }

  // Override this to define how to tear down the environment.
  void TearDown()
  {
    logger_log("test end");
  }
};

int main(int argc, char **argv)
{
  std::srand(std::time(nullptr));
  ::testing::InitGoogleTest(&argc, argv);
  std::ofstream testLogOutput("test.log", std::ofstream::out | std::ofstream::trunc);
  logger::setupLoggingSystem(new FileOutput(&testLogOutput));
  ::testing::AddGlobalTestEnvironment(new Environment());
  return RUN_ALL_TESTS();
}