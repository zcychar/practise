#include <iostream>
using namespace std;
constexpr int kMod = 2022;
long long a, n, ans=1;

int main() {
  cin >> a >> n;
  while (n) {
    if (n & 1)ans = (ans * a) % kMod;
    a = (a * a) % kMod;
    n >>= 1;
  }
  cout << ans;
  return 0;
}
