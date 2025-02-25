#include<bits/stdc++.h>
using namespace std;
string s1,s2,s3;
int f[50000015];

int gett(string s1,string s2,string s3) {
  string s4;
    if(s1.find(s2)!=s1.npos) {
      s4=s1;
    }else {
      for(int i=min(s1.length(),s2.length());i>=1;--i) {
        
      }
    }
}
int main() {
  cin>>s1>>s2>>s3;
  int ans=s1.length()+s2.length()+s3.length();
  ans=min(ans,gett(s1,s2,s3));
  ans=min(ans,gett(s1,s3,s2));
  ans=min(ans,gett(s2,s1,s3));
  ans=min(ans,gett(s2,s3,s1));
  ans=min(ans,gett(s3,s1,s2));
  ans=min(ans,gett(s3,s2,s1));
  cout<<ans;
  return 0;
}