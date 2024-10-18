#include <iostream>
#include<string>
using namespace std;
int n, num[35];
string a, b, c;
bool vis[35], nvis[35];
int searchqueue[35];
bool Vcheck() {
    for (int i = n - 1; i >= 0; --i) {
        int x1 = a[i] - 'A', x2 = b[i] - 'A', x3 = c[i] - 'A';
        if (vis[x1] && vis[x2] && vis[x3]) {
            if (((num[x1] + num[x2]) % n != num[x3]) && ((num[x1] + num[x2] + 1) % n != num[x3])) {
                return 0;
            }
        }
    }
    return 1;
}

void finalcheck() {
    int x[35], y[35], z[35], tmp = 0;
    for (int i = n - 1; i >= 0; --i) {
        x[i] = num[a[i] - 'A'];
        y[i] = num[b[i] - 'A'];
        z[i] = num[c[i] - 'A'];
    }
    for (int i = n - 1; i >= 0; --i) {
        int ans = (x[i] + y[i] + tmp) % n;
        tmp = (x[i] + y[i] + tmp) / n;
        if (ans != z[i]) {
            return;
        }
    }
    if (tmp) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        cout << num[i] << " ";
    }
    exit(0);
}

void search(int p) {
    if (p >n) {
        finalcheck();
        return;
    }
    int x=searchqueue[p];
    for (int i = n - 1; i >= 0; --i) {
        if (!nvis[i]) {
            num[x] = i;
            if (Vcheck()) {
                vis[x] = 1;
                nvis[i] = 1;
                search(p + 1);
                vis[x] = 0;
                nvis[i] = 0;

            }
            num[x] = 0;
        }
    }
}

int main() {
    cin >> n >> a >> b >> c;
    int cnt=0;
    for(int i=n-1;i>=0;--i) {
        if(!vis[a[i]-'A']) {
            searchqueue[++cnt]=a[i]-'A';
            vis[a[i]-'A']=1;
        }
        if(!vis[b[i]-'A']) {
            searchqueue[++cnt]=b[i]-'A';
            vis[b[i]-'A']=1;
        }
        if(!vis[c[i]-'A']) {
            searchqueue[++cnt]=c[i]-'A';
            vis[c[i]-'A']=1;
        }
    }
    for(int i=0;i<n;++i)vis[i]=0;
    search(1);
    return 0;
}
