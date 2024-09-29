#include <iostream>
using namespace std;
int q,opt,m,n;

int gcd(int a,int b) {
    if(b==0)return a;
    return gcd(b,a%b);
}

int main()
{
    cin >> q;
    for(int i = 1; i <= q; ++i) {
        cin >> opt >> m >> n;
        if(opt == 1) {
            cout << (long long) (m * n) ;
        }else {
            int d;
            d=(m<n?gcd(n,m):gcd(m,n));
            cout << m/d << " " << n/d ;
        }

    }
    return 0;
}
