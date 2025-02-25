#include <bits/stdc++.h>
using namespace std;
int f[2000015];
char s[2000015],t[2000015];
void p(int pl) {
  int j=f[pl];
  if(j==0)return;
  p(j-1);
  cout<<j<<endl;
}

int main() {
  cin>>s>>t;
  int n=strlen(s),m=strlen(t);
  for(int i=1;i<m;++i) {
    int j=f[i-1];
    while(j!=0&&t[i]!=t[j]) {
      j=f[j-1];
    }
    if(t[i]==t[j]) {
      j++;
    }
    f[i]=j;
  }
  for(int i=0,j=0;i<n;++i) {
    j=f[i-1];
    while(s[i]!=t[j]&&j!=0) {
      j=f[j-1];
    }
    if(s[i]==t[j]) {
      j++;
    }
    if(j==m-1) {
      cout<<i-m<<endl;
    }
  }
  return 0;
}
