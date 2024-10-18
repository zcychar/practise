#include <iostream>
#include<queue>
using namespace std;
int m, n,ansx,ansy;
char map[1005][1005];
int magic[35][5];
int nx[4]={-1,0,1,0},ny[4]={0,1,0,-1};
int mintime[1005][1005];

struct node {
  int x, y, time;
} step;

queue<node> q;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> map[i][j];
      mintime[i][j]=m*n*10;
      if (map[i][j] == '@') {
        node a;
        a.x = i, a.y = j, a.time = 0;
        q.push(a);
        map[i][j] = '.';
        mintime[i][j]=0;
      } else if (map[i][j] >= 'A' && map[i][j] <= 'Z') {
        int p=map[i][j]-'A';
        magic[p][++magic[p][0]]=i,magic[p][++magic[p][0]]=j;
      }else if(map[i][j]=='=') {
        ansx=i,ansy=j;
      }
    }
  }

  while(!q.empty()) {
    node t=q.front();
    q.pop();
    for(int i=0;i<4;++i) {
      int tx=t.x+nx[i],ty=t.y+ny[i];
      if(tx<=0||tx>n||ty<=0||ty>m||map[tx][ty]=='#') {
        continue;
      }
      if(map[tx][ty]=='.') {
        if(mintime[tx][ty]<=t.time+1)continue;
        mintime[tx][ty]=t.time+1;
        node nt;
        nt.x=tx,nt.y=ty,nt.time=t.time+1;
        q.push(nt);
      }else if(map[tx][ty]=='=') {
        cout<<t.time+1;
      }else if(map[tx][ty]>='A'&&map[tx][ty]<='Z') {
        int p=map[tx][ty]-'A',tranx,trany;
        if(magic[p][1]==tx) {
          tranx=magic[p][3],trany=magic[p][4];
        }else {
          tranx=magic[p][1],trany=magic[p][2];
        }
        if(mintime[tranx][trany]<=t.time+1)continue;
        mintime[tranx][trany]=t.time+1;
        node nt;
        nt.x=tranx,nt.y=trany,nt.time=t.time+1;
        q.push(nt);
      }
    }
  }
  return 0;
}
