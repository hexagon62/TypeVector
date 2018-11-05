#include "../TypeVector/TypeVector.hpp"

#include <iostream>

int main()
{
  [[maybe_unused]]
  TypeVector<int, float, int>::at<3>::type x;

  std::cout << typeid(x).name() << '\n';
}