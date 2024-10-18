#include <iostream>
#include<algorithm>
using namespace std;
int a[105],tot,n,res;
bool vis[105];
bool cmp(int a,int b) {
    return a>b;
}
void search(int left,int len,int pos) {
    if(len==0) {
        if(left==1) {
            cout<<res;
            exit(0);
        }
        for(int i=1;i<=n;++i) {
            if(!vis[i]) {
                vis[i]=1;
                search(left-1,res-a[i],i);
                vis[i]=0;
                break;
            }
        }
        return;
    }
    int tmp=0;
    for(int i=pos+1;i<=n;++i) {
        if(!vis[i]&&len>=a[i]&&a[i]!=tmp) {
            vis[i]=1;
            search(left,len-a[i],i);
            vis[i]=0;
            if(len==a[i])return;
            tmp=a[i];
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;++i) {
        cin>>a[i];
        tot+=a[i];
    }
    sort(a+1,a+n+1,cmp);
    for(int i=a[1];i<=tot/2;++i) {
        if(tot%i!=0)continue;
        res=i;
        vis[1]=1;
        search(tot/i,i-a[1],1);
        vis[1]=0;
    }
    cout<<tot;
    return 0;
}
