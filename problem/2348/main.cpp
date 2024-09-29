#include <iostream>
using namespace std;
long long q,opt,m,n,d;

int gcd(int a,int b) {
    if(a%b == 0)return b;
    return gcd(b,a%b);
}
//idiot
int main()
{
    cin >> q;
    for(int i = 1; i <= q; ++i) {
        cin >> opt >> m >> n;
        d=(m<n?gcd(n,m):gcd(m,n));
        if(opt == 1) {
            cout << m/d * n << endl;
        }else {

            cout << m/d << " " << n/d <<endl;
        }
    }
    return 0;
}