// Copyright (c) 2010
// All rights reserved.


#include <typeinfo>
#include <memory>
#include "gtest/gtest.h"

#ifdef __GNUG__  // gnu C++ compiler

#include <cxxabi.h>

std::string demangle(const char* mangled_name) {
  std::size_t len = 0;
  int status = 0;
  std::unique_ptr< char, decltype(&std::free) > ptr(
      __cxxabiv1::__cxa_demangle(mangled_name, nullptr, &len, &status),
      &std::free);
  return ptr.get();
}

#else

std::string demangle( const char* name ) { return name; }

#endif  // _GNUG_


TEST(AutoTest, simpleTest) {
  auto i = 1;
  ASSERT_EQ(demangle(typeid(i).name()), "int");

  auto d = 1.0;
  ASSERT_EQ(demangle(typeid(d).name()), "double");

  auto ch = 'a';
  ASSERT_EQ(demangle(typeid(ch).name()), "char");

  auto str = "Hello World";
  ASSERT_EQ(demangle(typeid(str).name()), "char const*");
}

TEST(AutoTest, refTest) {
  int x = 5;
  int& y = x;

  {
    auto z = y;
    ASSERT_EQ(demangle(typeid(z).name()), "int");
    ASSERT_EQ(++z, 6);
    ASSERT_EQ(y, 5);
    ASSERT_EQ(x, 5);
  }

  {
    auto& z = y;
    ASSERT_EQ(demangle(typeid(z).name()), "int");
    ASSERT_EQ(++z, 6);
    ASSERT_EQ(y, 6);
    ASSERT_EQ(x, 6);
  }
}

TEST(AutoTest, pointTest) {
  int x = 5;
  int *px = &x;

  auto py = px;
  ASSERT_EQ(demangle(typeid(py).name()), "int*");

  const int* cx = &x;
  auto pz = cx;
  ASSERT_EQ(demangle(typeid(pz).name()), "int const*");

  const auto pd = cx;
  ASSERT_EQ(demangle(typeid(pd).name()), "int const*");

  const auto pc = px;
  ASSERT_EQ(demangle(typeid(pc).name()), "int*");
}
