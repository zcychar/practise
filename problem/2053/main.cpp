  #include <bits/stdc++.h>
  using namespace std;

  int minlen[5000015],n,a,ans;

  int main(){
    cin>>n;
    for(int i=0;i<=n;++i) {
      minlen[i]=1e8;
    }
    for(int i=1;i<=n;++i) {
      cin>>a;
      *upper_bound(minlen+1,minlen+n+1,a)=a;
    }
    for(int i=1;i<=n;++i) {
      if(minlen[i]!=1e8)ans=i;
    }
    cout<<ans;
    return 0;
  }
