#include <iostream>
#include <vector>

void func(const std::vector<int> &vi)
{
  auto ci = vi.begin();
  typedef decltype (vi.begin()) CIT;
  CIT ite_end = vi.end();
  
  for( ; ci!=ite_end; ci++ )
  {
    std::cout <<*ci <<" ";
  }
  std::cout <<std::endl;
}

int main()
{
  auto x = 0;  // int
  auto c = 'a';  // char
  auto d = 0.5;  // double
  auto debt = 14400000000000LL;  // long long

  std::cout <<"x is " <<x << " c is " <<c
            <<" d is " <<d <<" debt is " <<debt
            <<std::endl;

  std::vector<int> vec;
  int A[] = {1, 2, 3, 4, 5, 6, 7};
  vec.resize(7);
  std::copy(A, A+7, vec.begin());
  func(vec);
}
