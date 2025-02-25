#include <iostream>
using namespace std;
int n,k,a[100015],cnt,num;
void count(int l,int r) {
  cnt++;
  if(l==r-1)return;
  int mid=(l+r)>>1;
  count(l,mid);
  count(mid,r);
}
void print(int l,int r) {
  if(l==r-1) {
    return;
  }
  if(k==1) {
    return;
  }
  k-=2;
  int mid=(l+r)>>1;
  swap(a[mid-1],a[mid]);
  print(mid,r);
  print(l,mid);
}
int main() {
  cin>>n>>k;
  if(k%2==0) {
    cout<<-1;
    return 0;
  }
  count(1,n+1);
  if(cnt<k) {
    cout<<-1;
    return 0;
  }
  for(int i=1;i<=n;++i)a[i]=i;
  print(1,n+1);
  for(int i=1;i<=n;++i) {
    cout<<a[i]<<" ";
  }
  return 0;
}