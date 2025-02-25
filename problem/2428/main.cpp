#include <iostream>
#include<algorithm>
using namespace std;
int n,a[100015],tot;
bool vis[100015],flag;
void search(int now,int left){
    if(now==4&&left==0){
        flag=1;
        return;
    }
    if(left==0){
        search(now+1,tot/4);
        return;
    }
    for(int i=n;i>=1;--i){
        if(vis[i])continue;
        if(a[i]<=left){
            vis[i]=1;
            search(now,left-a[i]);
            vis[i]=0;
            if(flag)return;
        }
    }
    return;
}
int main() {
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        tot+=a[i];
    }
    if(tot%4){
        cout<<"no";
        return 0;
    }
    sort(a+1,a+n+1);
    search(1,tot/4);

    if(!flag) {
        cout<<"no";
    }else {
        cout<<"yes";
    }
    return 0;
}