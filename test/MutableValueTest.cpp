#include <gtest/gtest.h>
#include <MutableValue.h>

// class MutableValueTest : public ::testing::Test {

// };

TEST(MutableValue, setValue) {
  MutableValue mv = MutableValue(10);
  mv.setValue(101);
  EXPECT_TRUE(mv.hasChanged());
}