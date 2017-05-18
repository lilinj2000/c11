// Copyright (c) 2010
// All rights reserved.

#include "gtest/gtest.h"

struct Foo {
    int   i;
    float f;
    char  c;
};
 
struct Empty {};
 
struct alignas(64) Empty64 {};

TEST(AlignofTest, basicTest) {
 
 EXPECT_EQ(alignof(char), 1);
 EXPECT_EQ(alignof(int*), 8);
 EXPECT_EQ(alignof(Foo), 4);
 EXPECT_EQ(alignof(Empty), 1);
 EXPECT_EQ(alignof(Empty64), 64);
}
