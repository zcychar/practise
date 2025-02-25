#include <iostream>
#include <algorithm>
using namespace std;
const double eps=1e-4;
double c[100015],a[100015],b[100015];
int n,k;
bool cmp(double x,double y) {
  return x>y;
}
void search(double l,double r) {
  if(r-l<=eps) {
    cout<<int(100*l+0.5);
    exit(0);
  }
  double mid=(l+r)/2,sum=0;
  for(int i=1;i<=n;++i)c[i]=b[i]-mid*a[i];
  sort(c+1,c+n+1,cmp);
  for(int i=1;i<=k;++i) {
    sum+=c[i];
  }
  if(sum>=0)search(mid,r);
  else search(l,mid);
}
int main() {
  cin>>n>>k;
  for(int i=1;i<=n;++i)cin>>a[i];
  for(int i=1;i<=n;++i) {
    cin>>b[i];
  }
  search(0.0,1.0);
  return 0;
}
