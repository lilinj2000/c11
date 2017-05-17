#include <algorithm>
#include <functional>
#include <list>
#include <vector>
#include "gtest/gtest.h"

TEST(LambdaTest, CountUpperCaseTest) {
  char s[]="Hello World!";
  int Uppercase = 0; //modified by the lambda
  std::for_each(s, s+sizeof(s), [&Uppercase] (char c) {
      if (isupper(c))
        Uppercase++;
    });

  EXPECT_EQ(Uppercase, 2);
}

TEST(LambdaTest, CaptureCaseTest) {
  int i = 0;
  [&]{}; //ok: by-reference capture default
  [=]{}; //ok: by-copy capture default
  [&, i]{}; // ok: by-reference capture, except i is captured by copy
  [=, &i]{}; // ok: by-copy capture, except i is captured by reference
  // [&, &i] {}; // error: by-reference capture when by-reference is the default
  // [=, this] {}; // error: this when = is the default
  // [=, *this]{}; // ok: captures the enclosing S2 by copy (C++17)
  // [i, i] {}; // error: i repeated
  // [this, *this] {}; // error: "this" repeated (C++17)

  SUCCEED();
}

TEST(LambdaTest, Expressions1Test) {
  auto f1 = [](int x, int y) { return x + y; };  
  EXPECT_EQ(f1(2, 3), 5);

  std::function<int(int, int)> f2 = [](int x, int y) { return x + y; };
  EXPECT_EQ(f1(3, 4), 7);
}

TEST(LambdaTest, Expressions2Test) {
  int i = 3;  
  int j = 5;
  std::function<int (void)> f = [i, &j] { return i + j; };
  EXPECT_EQ(f(), 8);

  i = 22;  
  j = 44;
  EXPECT_EQ(f(), 47);
}

TEST(LambdaTest, Expressions3Test) {
  int n = [] (int x, int y) { return x + y; }(5, 4);  

  EXPECT_EQ(n, 9);
}

TEST(LambdaTest, Expressions4Test) {
  // Create a list of integers with a few initial elements.  
  std::list<int> numbers;  
  numbers.push_back(13);  
  numbers.push_back(17);  
  numbers.push_back(42);  
  numbers.push_back(46);  
  numbers.push_back(99);  
  
  // Use the find_if function and a lambda expression to find the   
  // first even number in the list.  
  const std::list<int>::const_iterator result =   
      std::find_if(numbers.begin(), numbers.end(),[](int n) { return (n % 2) == 0; });  
  
    // Print the result.  
    if (result != numbers.end()) {
      EXPECT_EQ(*result, 42); 
    } else {  
      FAIL();
    }
}

TEST(LambdaTest, NestingExpressionsTest) {
  int timestwoplusthree = [](int x) { return [](int y) { return y * 2; }(x) + 3; }(5);
  EXPECT_EQ(timestwoplusthree, 13);
} 

TEST(LambdaTest, HigherOrderExpressionsTest) {
  // The following code declares a lambda expression that returns   
  // another lambda expression that adds two numbers.   
  // The returned lambda expression captures parameter x by value.  
  auto addtwointegers = [](int x) -> std::function<int(int)> {   
      return [=](int y) { return x + y; };   
  };  
  
  // The following code declares a lambda expression that takes another  
  // lambda expression as its argument.  
  // The lambda expression applies the argument z to the function f  
  // and multiplies by 2.  
  auto higherorder = [](const std::function<int(int)>& f, int z) {   
      return f(z) * 2;   
  };  
  
  // Call the lambda expression that is bound to higherorder.   
  auto answer = higherorder(addtwointegers(7), 8);  
  EXPECT_EQ(answer, 30);
}

class Scale  
{  
public:  
  // The constructor.  
  explicit Scale(int scale) : _scale(scale) {}  

  // Prints the product of each element in a vector object   
  // and the scale value to the console.  
  void ApplyScale(const std::vector<int>& v) const {  
      std::for_each(v.begin(), v.end(), [=](int n) { std::cout << n * _scale << std::endl; });
      // the below is also ok
      // std::for_each(v.begin(), v.end(), [this](int n) { std::cout << n * _scale << std::endl; });    
  }  
  
private:  
  int _scale;  
};

TEST(LambdaTest, ScaleTest) {
  std::vector<int> values;  
  values.push_back(1);  
  values.push_back(2);  
  values.push_back(3);  
  values.push_back(4);  
  
  // Create a Scale object that scales elements by 3 and apply  
  // it to the vector object. Does not modify the vector.  
  Scale s(3);  
  s.ApplyScale(values);

  SUCCEED();
}

// Negates each element in the vector object. Assumes signed data type.  
template <typename T>  
void negate_all(std::vector<T>& v) {  
    std::for_each(v.begin(), v.end(), [](T& n) { n = -n; });  
}  
  
// Prints to the console each element in the vector object.  
template <typename T>  
void print_all(const std::vector<T>& v) {  
    std::for_each(v.begin(), v.end(), [](const T& n) { std::cout << n << std::endl; });  
}

TEST(LambdaTest, TemplateExpressionTest) {
  std::vector<int> v;  
  v.push_back(34);  
  v.push_back(-43);  
  v.push_back(56);  

  print_all(v);  
  negate_all(v);  
  std::cout << "After negate_all():" << std::endl;  
  print_all(v);

  SUCCEED();
}

TEST(LambdaTest, ExceptionExpressionTest) {
  // Create a vector that contains 3 elements.  
  std::vector<int> elements(3);  

  // Create another vector that contains index values.  
  std::vector<int> indices(3);  
  indices[0] = 0;  
  indices[1] = -1; // This is not a valid subscript. It will trigger an exception.  
  indices[2] = 2;  

  // Use the values from the vector of index values to   
  // fill the elements vector. This example uses a   
  // try/catch block to handle invalid access to the   
  // elements vector.  
  try {  
      for_each(indices.begin(), indices.end(), [&](int index) {   
          elements.at(index) = index;   
      });  
  } catch (const std::out_of_range& e)  {  
    std::cerr << "Caught '" << e.what() << "'." << std::endl;
  };

  SUCCEED();
}