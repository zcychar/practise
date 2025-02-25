#include <iostream>
#include "MemoryRiver.hpp"
int main() {
  MemoryRiver<int> a("123.txt");
  a.initialise("123.txt");
  int tmp=3;
  a.write_info(tmp,2);
  a.get_info(tmp,1);
  std::cout << tmp<< std::endl;
  a.get_info(tmp,2);
  std::cout << tmp<< std::endl;
  return 0;
}
