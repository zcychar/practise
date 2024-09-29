//
// Created by zcy on 24-9-24.
//
#include<iostream>
using namespace std;

int main() {
  int n;

  cin >> n;
  for(int i=0;i<n;++i){
    char sym;
    long long a,b;
    cin >> sym >> a >> b;
    if(sym == '+'){
      cout << a+b << endl;
  }else if (sym == '*'){
    cout << a*b <<endl;
  }
}
return 0;
}