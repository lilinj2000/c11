#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

int main()
{
  // Parenthesized initialization looks like this
  std::string s1("hello");
  int m = int();
  std::cout <<"s1 is " <<s1 <<" m is " <<std::endl;
  
  // use the = notation for the same purpose in certain cases
  std::string s2 = "hello";
  int x = 5;
  std::cout <<"s2 is " <<s2 <<" x is " <<x <<std::endl;
  
  // For POD aggregates, you use braces
  int arr[4] = {0, 1, 2, 3};
  std::cout <<"arr is " ;
  std::for_each(arr, arr+4, [](int i){
      std::cout <<i <<" ";
    });
  std::cout <<std::endl;
  
  struct tm today = {0};


  // Finally, constructors use member initializers
  struct S
  {
    int x;
    
    S(): x(0) {}
  };

  // c++11
  class C
  {
    int a;
    int b;
   public:
    C(int i, int j): a(i), b(j)
    {
    }
  };

  C c{100, 100};

  int* a= new int[3] { 1, 2, 0};

  class X {
    int a[4];
   public:
    X(): a{1, 2, 3, 4}
    {
    }
  };

  std::vector<std::string> vs = { "first", "second" };

  std::map<std::string, std::string> singers =
      { {"Lady Gaga", "+1 (212) 555-7890"},
        {"Beyonce Knowles", "+1 (212) 555-0987"}};

  class D
  {
    int a = 7;
   public:
    D();
  };
}
