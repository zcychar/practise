#include<bits/stdc++.h>
using namespace std;

unsigned long long n,m,num;
unsigned long long a[100010];
unsigned long long full[70], bit[70] = {1};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin >> n >> m >> num;
    full[1] = 1;

    for(int i = 2; i <= n; i++) full[i] = (unsigned long long)((full[i - 1] << 1) | 1);
    bit[0] = 1;
    for(int i = 1; i < n; i++) bit[i] = (unsigned long long)(bit[i - 1] << 1);

    //  for(int i = 0; i <= 64; i++) cout << bit[i] << ' ' << full[i] << endl;

    string st;
    int x, y;
    for(int i = 1; i <= num; i++) {
        cin >> st;
        switch(st[0]) {
            case 'r': {
                cin >> x;
                a[x] = 0;
                break;
            }
            case 'f': {
                cin >> x;
                a[x] = full[n];
                break;
            }
            case 'a': {
                cin >> x >> y;
                a[x] |= bit[y]
                break;
            }
            case 'e': {
                cin >> x >> y;
                a[x] &= (full[n] ^ bit[y]);
                break;
            }
            case 'i': {
                cin >> x >> y;
                a[x] &= a[y];
                break;
            }
            case 'u': {
                cin >> x >> y;
                a[x] |= a[y];
                break;
            }
            default: {
                if(st[6] == 'e') {
                    cin >> x >> y;
                    if(a[x] & bit[y]) cout << "yes" << endl;
                    else cout << "no" << endl;
                }
                else {
                    cin >> x;
                    bool flag = false;
                    for(int i = 0; i < n - 1; i++) {
                        unsigned long long tmp = bit[i] | bit[i + 1];
                        if((tmp & a[x]) == tmp) {
                            flag = true;
                            break;
                        }
                    }
                    if(flag) cout << "adj" << endl;
                    else cout << "not adj" << endl;
                }
                break;
            }
        }
    }
    return 0;
}
