#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

void naiveswap(string &a, string & b)
{
  string temp = a;
  a=b;
  b=temp;
}

void moveswapstr(string& empty, string & filled)
{
  // //pseudo code, but you get the idea
  // size_t sz=empty.size();
  // const char *p= empty.data();
  // //move filled's resources to empty
  // empty.setsize(filled.size());
  // empty.setdata(filled.data());
  // //filled becomes empty
  // filled.setsize(sz);
  // filled.setdata(p);
}

class Movable
{
  Movable (Movable&&); //move constructor
  Movable&& operator=(Movable&&); //move assignment operator
};

int main()
{
}
