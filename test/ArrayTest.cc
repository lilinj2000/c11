// Copyright (c) 2010
// All rights reserved.


#include <array>
#include "gtest/gtest.h"

TEST(ArrayTest, simpleTest) {
  std::array<int, 10> sz;
  ASSERT_EQ(sz.size(), 10);
  ASSERT_FALSE(sz.empty());
}
