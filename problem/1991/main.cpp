#include <iostream>
#include<string>
using namespace std;
unsigned long long MAX,m,n,num,a,b,dig[105];
unsigned long long s[100015];
string opt;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin>>n>>m>>num;
    dig[0]=1;
    MAX=1;
    for(int i=2;i<=n;++i) {
        MAX=(MAX<<1)|1;
    }
    for(int i=1;i<n;++i)dig[i]=(dig[i-1]<<1);
    while(num--) {
        cin>>opt;
        switch(opt[0]) {
            case 'r': {
                cin>>a;
                s[a]=0;
                break;
            }
            case 'f': {
                cin>>a;
                s[a]=MAX;
                break;
            }
            case 'q': {
                if(opt[6]=='e') {
                    cin>>a>>b;
                    if(s[a]&dig[b]) {
                        cout<<"yes\n";
                    }else {
                        cout<<"no\n";
                    }
                }else {
                    cin>>a;
                    bool flag=0;
                    for(int i=0;i<n-1;++i) {
                        unsigned long long d=dig[i]+dig[i+1];
                        if((s[a]&d)==d) {
                            flag=1;
                            cout<<"adj\n";
                            break;
                        }
                    }
                    if(!flag) {
                        cout<<"not adj\n";
                    }
                }
                break;
            }
            case 'a': {
                cin>>a>>b;
                s[a]|=dig[b];
                break;
            }
            case 'e': {
                cin>>a>>b;
                s[a]&=(MAX^dig[b]);
                break;
            }
            case 'i': {
                cin>>a>>b;
                s[a]&=s[b];
                break;
            }
            case'u': {
                cin>>a>>b;
                s[a]|=s[b];
                break;
            }
            default: {
                break;
            }
        }
    }
    return 0;
}
