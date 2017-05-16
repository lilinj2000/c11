// Copyright (c) 2010
// All rights reserved.


#include <typeinfo>
#include "gtest/gtest.h"

class TypeInfoTest : public ::testing::Test {
 public:
  TypeInfoTest() {
  }
};


TEST_F(TypeInfoTest, integerTest) {
  ASSERT_STREQ(typeid(short).name(), "s");  // NOLINT(runtime/int)
  ASSERT_STREQ(typeid(int).name(), "i");  // NOLINT(runtime/int)
  ASSERT_STREQ(typeid(long).name(), "l");  // NOLINT(runtime/int)
  ASSERT_STREQ(typeid(long long).name(), "x");  // NOLINT(runtime/int)
  ASSERT_STREQ(typeid(unsigned short).name(), "t");  // NOLINT(runtime/int)
  ASSERT_STREQ(typeid(unsigned int).name(), "j");  // NOLINT(runtime/int)
  ASSERT_STREQ(typeid(unsigned long).name(), "m");  // NOLINT(runtime/int)
  ASSERT_STREQ(typeid(unsigned long long).name(), "y");  // NOLINT(runtime/int)
}

TEST_F(TypeInfoTest, decimalTest) {
  ASSERT_STREQ(typeid(float).name(), "f");
  ASSERT_STREQ(typeid(double).name(), "d");
}

TEST_F(TypeInfoTest, stringTest) {
  ASSERT_STREQ(typeid(std::string).name(), "Ss");
}

TEST_F(TypeInfoTest, refTest) {
  ASSERT_STREQ(typeid(int&).name(), "i");
  ASSERT_STREQ(typeid(const int&).name(), "i");
}

TEST_F(TypeInfoTest, pointTest) {
  ASSERT_STREQ(typeid(int*).name(), "Pi");
  ASSERT_STREQ(typeid(int**).name(), "PPi");
  ASSERT_STREQ(typeid(const int*).name(), "PKi");
  ASSERT_STREQ(typeid(const int* const).name(), "PKi");

  ASSERT_STREQ(typeid(int* &).name(), "Pi");
  ASSERT_STREQ(typeid(const int* &).name(), "PKi");
}
