#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

// void f(int a)
// {
//   std::cout <<"in f(int)" <<std::endl;
// }

void f(char *)
{
  std::cout <<"in f(char *)" <<std::endl;
}

void f(int a)
{
  std::cout <<"in f(int)" <<std::endl;
}

class A
{
};

int main()
{
  //C++03
  // call f(int)
  f(0); //which f is called?;

  //C++11
  f(nullptr); //unambiguous, calls #2

  std::string str{"hello world"};
  
  const char *pc=str.c_str(); //data pointers
  if (pc!=nullptr)
    std::cout<<pc<<std::endl;
  
  int (A::*pmf)()=nullptr; //pointer to member function
  void (*pmg)()=nullptr; //pointer to function
}
