#include "vector.h"
#include <iostream>

template<typename T> void print_vec(const og::Vector<T> &vec);

int main()
{
  og::Vector<int> vec(2, 5);
  std::cout << vec.size() << std::endl;
  print_vec(vec);
  vec.clear();
  std::cout << vec.size() << std::endl;
  print_vec(vec);

  return 0;
}
template<typename T> void print_vec(const og::Vector<T> &vec)
{
  for (int i = 0; i < vec.size(); i++) { std::cout << vec.at(i) << std::endl; }
}
