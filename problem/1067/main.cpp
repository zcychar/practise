#include <iostream>
using namespace std;
int k,v,n,a[1015],b[1015];
int f[5005][105],now[105];
int main() {
  cin>>k>>v>>n;
  for(int i=1;i<=n;++i) {
    cin>>a[i]>>b[i];
  }
  for(int i=0;i<=v;++i) {
    for(int j=0;j<=k;++j) {
      f[i][j]=-1000015;
    }
  }
  f[0][1]=0;
  for(int i=1;i<=n;++i) {
    for(int j=v;j>=a[i];--j) {
      int k1=1,k2=1;
      for(int l=1;l<=k;++l) {
         if(f[j-a[i]][k1]+b[i]>f[j][k2]) {
           now[l]=f[j-a[i]][k1]+b[i];
           k1++;
         }else {
           now[l]=f[j][k2];
           k2++;
         }
      }
      for(int l=1;l<=k;++l) {
        f[j][l]=now[l];
      }
    }
  }
  int ans=0;
  for(int i=1;i<=k;++i) {
    ans+=f[v][i];
  }
  cout<<ans;
  return 0;
}
