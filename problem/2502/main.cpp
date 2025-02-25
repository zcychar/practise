#include <iostream>
using namespace std;
int n,m,a[10015];
int dp[105][105][105];
const int p=1e6+7;
int main() {
  cin>>n>>m;
  for(int i=1;i<=m;++i)cin>>a[i];
  for(int i=1;i<=m;++i) {
    dp[1][i][1]=1;
  }
  for(int i=2;i<=n;++i) {
    for(int j=1;j<=m;++j) {
      for(int k=2;k<=a[j];++k) {
        dp[i][j][k]=(dp[i][j][k]+dp[i-1][j][k-1])%p;
      }
      for(int k=j+1;k<=m;++k) {
        for(int l=1;l<=a[k];++l)
        dp[i][j][1]=(dp[i][j][1]+dp[i-1][k][l])%p;
      }
    }
  }
  int ans=0;
  for(int i=1;i<=m;++i) {
    for(int j=1;j<=a[i];++j) {
      ans=(ans+dp[n][i][j])%p;
    }
  }
  cout<<ans;
  return 0;
}
