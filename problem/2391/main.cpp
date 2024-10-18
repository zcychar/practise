#include <iostream>
#include<string>
using namespace std;
int n,num[35];
string a, b, c;
bool vis[35],nvis[35];
bool Vcheck() {

  for(int i=n-1;i>=0;--i) {
    int x1=a[i]-'A',x2=b[i]-'A',x3=c[i]-'A';
    if(vis[x1]&&vis[x2]&&vis[x3]) {
      if(((num[x1]+num[x2])%n!=num[x3])&&((num[x1]+num[x2]+1)%n!=num[x3])) {
        return 0;
      }
      if(i==0) {
        if(num[x1]+num[x2]>=n)return 0;
      }
    }
  }
  return 1;
}
bool finalcheck() {
  int tmp=0;

  for(int i=n-1;i>=0;--i) {
    int x=num[a[i]-'A'],y=num[b[i]-'A'],z=num[c[i]-'A'];
    int ans=(x+y+tmp)%n;
    tmp=(x+y+tmp)/n;
    if(ans!=z) {
      return false;
    }
  }
  return true;
}
void search(int p) {
  if(p==0) {
    for(int i=0;i<n;++i) {
      if(!nvis[i]) {
        num[a[0]-'A']=i;
        break;
      }
    }
    if(!finalcheck())return;
    for(int i=0;i<n;++i) {
      cout<<num[i]<<" ";
    }
    exit(0);
  }
  int x=a[p]-'A';
  for(int i=0;i<n;++i) {
    if(!nvis[i]) {
      num[x]=i;
      if(!Vcheck())continue;
      vis[x]=1;
      nvis[i]=1;
      search(p-1);
      vis[x]=0;
      nvis[i]=0;
      num[x]=-1;
    }
  }
}
int main() {
  cin>>n>>a>>b>>c;
  search(n-1);
  return 0;
}
