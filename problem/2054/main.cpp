#include <iostream>
#include<algorithm>
using namespace std;
int a[3000005],k,n;
int main() {
  cin>>n>>k;
  for(int i=1;i<=n;++i)cin>>a[i];
  sort(a+1,a+n+1);
  cout<<a[n-k+1];
  return 0;
}
