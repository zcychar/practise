#include <iostream>
#include<algorithm>
using namespace std;
int length,m,n,a[100015];
void search(int l,int r) {
  if(l==r) {
    cout<<l;
    exit(0);
  }
  int mid=(l+r+1)>>1;
  int cnt=0,current =0;
  for(int i=1;i<=n;++i) {
    if(length-a[i]<mid){
      cnt++;
    }else if(a[i]-a[current]<mid) {
      cnt++;
    }else current = i;
  }
  if(cnt<=m)search(mid,r);
  else search(l,mid-1);
}
int main() {
  cin>>length>>n>>m;
  for(int i=1;i<=n;++i)cin>>a[i];
  sort(a+1,a+n+1);
  search(1,length);
  return 0;
}
