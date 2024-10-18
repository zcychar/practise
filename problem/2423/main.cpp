#include <iostream>
using namespace std;
template <typename Tp>
inline void read(Tp &x) {
    x = 0; bool fg = 0; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') fg ^= 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (Tp)(ch ^ 48), ch = getchar();
    if (fg) x = -x;
}
unsigned long long p,x,n,a,y,k,powx=1,ans;
unsigned long long fpow(unsigned long long k1) {
    unsigned long long tmp=0,base=y,cnt=k1;
    while(cnt) {
        if(cnt%2)tmp=(tmp*base)%p;
        base=(base*base)%p;
        cnt/=2;
    }
    return tmp;
}
unsigned long long cal(unsigned long long k1) {
    if(k1<=100) {
        unsigned long long cnt=0,tmp=1;
        for(int i=0;i<=k1;++i) {
            cnt=(cnt+tmp)%p;
            tmp=(tmp*y)%p;
        }
        return cnt;
    }
    if(k1%2) {
        return cal((k1-1)/2)%p*(1+fpow((k1+1)/2))%p;
    }else {
        return 1+y*(cal(k1-1))%p;
    }
}
int main() {
    read(n),read(x),read(p);
    for(int i=0;i<=n;++i) {
        read(a),read(y),read(k);
        ans=(ans+(a*powx)%p*cal(k)%p)%p;
        powx=(powx*x)%p;
    }
    cout<<ans;
    return 0;
}