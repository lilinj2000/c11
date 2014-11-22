#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#define MAX 10
class M //C++11 delegating constructors
{
  int x, y;
  char *p;
 public:
  M(int v) : x(v), y(0), p(new char [MAX]) {} //#1 target
  M(): M(0) {std::cout<<"delegating ctor"<<std::endl;} //#2 delegating
};

int main()
{
  M m1(10);
  M m2();
}
