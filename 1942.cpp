//
// Created by zcy on 24-9-20.
//
#include<iostream>
#include<string>

int main(){
  std::string s;
  std::cin >> s;
  int len = s.length();
  for (int i = len - 1 ; i >= 0 ; --i )
    std::cout << s[i];
  return 0;
}
