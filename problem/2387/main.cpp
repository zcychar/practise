#include <iostream>
using namespace std;
long long current_length[15];
long long x[15],y[15],n,xm,ym;
long long ans;
bool flag[15];
long long MaxLength(int p) {
    long long max_length=min(min(x[p],y[p]),min(xm-x[p],ym-y[p]));
    for(int i=1;i<=n;++i) {
        if(i==p)continue;
        if(flag[i]) {
            if(abs(x[i]-x[p])+abs(y[i]-y[p])-current_length[i]<=0) {
                return 0;
            }
            max_length=min(max_length,abs(x[i]-x[p])+abs(y[i]-y[p])-current_length[i]);
        }
    }
    return max_length;
}
long long search(int p,int num) {
    if(num==n) {
        return MaxLength(p)*MaxLength(p)*2;
    }
    current_length[p]=MaxLength(p);
    flag[p]=1;
    long long tmp=0;
    for(int i=1;i<=n;++i) {
        if(flag[i])continue;
        tmp=max(tmp,search(i,num+1));
    }
    tmp+=2*current_length[p]*current_length[p];
    current_length[p]=0;
    flag[p]=0;
    return tmp;
}
int main(){
    cin>>n>>xm>>ym;;
    for(int i=1;i<=n;++i) {
        cin>>x[i]>>y[i];
    }
    for(int i=1;i<=n;++i) {
        ans=max(ans,search(i,1));
    }
    cout<<ans;
    return 0;
}
