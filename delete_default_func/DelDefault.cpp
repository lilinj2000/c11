#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

struct A
{
  A()=default; //C++11
  virtual ~A()=default; //C++11
};

struct NoCopy
{
  NoCopy() {}
  NoCopy & operator =( const NoCopy & ) = delete;
  NoCopy ( const NoCopy & ) = delete;
};

int main()
{
  NoCopy a;
  // NoCopy b(a);  // compilation error, copy ctor is deleted
}
