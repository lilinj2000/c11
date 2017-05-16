// Copyright (c) 2010
// All rights reserved.


#include <fstream>
#include "gtest/gtest.h"

TEST(IOTest, FileTest) {
  std::fstream* f = new std::fstream("test.data", std::fstream::out);

  *f <<"test one." <<std::endl;

  GTEST_SUCCEED();
}
