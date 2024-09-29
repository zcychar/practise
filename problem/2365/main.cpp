#include <iostream>
using namespace std;
int n;
void mygo(int n);
void its(int n) {
  if(n==0)return;
  if(n==1) {
    cout << 1 << " ";
    return;
  }
  its(n-1);
  mygo(n-2);
  cout << n << " ";
  its(n-2);
}
void mygo(int n){
  if(n<=0)return;
  if(n==1) {
    cout<<1<< " ";
    return;
  }
  mygo(n-2);
  cout << n << " ";
  its(n-2);
  mygo(n-1);
}
int main() {
  cin >> n;
  mygo(n);
  return 0;
}
