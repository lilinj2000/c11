#include <iostream>
#include <algorithm>

int main()
{
  char s[]="Hello World!";
  int Uppercase = 0; //modified by the lambda
  std::for_each(s, s+sizeof(s), [&Uppercase] (char c) {
      if (isupper(c))
        Uppercase++;
    });
  std::cout<< Uppercase<<" uppercase letters in: "<< s<<std::endl;
}
