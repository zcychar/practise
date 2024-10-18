#include <iostream>
#include<queue>
using namespace std;
int m, n;
char map[1005][1005];
int magic[55][10];
int nx[4] = {-1, 0, 1, 0}, ny[4] = {0, 1, 0, -1};
bool vis[1005][1005];
string s;

struct node {
  int x, y, time;
} step;

queue<node> q;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> s;
    for (int j = 1; j <= m; ++j) {
      map[i][j] = s[j - 1];
      if (map[i][j] == '@') {
        q.push(node{i, j, 0});
      } else if (map[i][j] >= 'A' && map[i][j] <= 'Z') {
        int p = map[i][j] - 'A';
        magic[p][++magic[p][0]] = i, magic[p][++magic[p][0]] = j;
      }
    }
  }
  while (!q.empty()) {
    node t = q.front();
    q.pop();
    if (map[t.x][t.y] >= 'A' && map[t.x][t.y] <= 'Z') {
      int p = map[t.x][t.y] - 'A', tranx, trany;
      if (magic[p][1] == t.x&&magic[p][2] == t.y) {
        tranx = magic[p][3], trany = magic[p][4];
      } else {
        tranx = magic[p][1], trany = magic[p][2];
      }
      t.x = tranx, t.y = trany;
    }
    for (int i = 0; i < 4; ++i) {
      int tx = t.x + nx[i], ty = t.y + ny[i];
      if (tx <= 0 || tx > n || ty <= 0 || ty > m || map[tx][ty] == '#') {
        continue;
      }
      if (map[tx][ty] == '=') {
        cout << t.time + 1;
        return 0;
      }
      if (vis[tx][ty])continue;
      vis[tx][ty] = 1;
      node nt;
      nt.x = tx, nt.y = ty, nt.time = t.time + 1;
      q.push(nt);
    }
  }
  return 0;
}
