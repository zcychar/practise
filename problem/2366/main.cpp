#include<iostream>
#include<vector>
using namespace std;

int happy,birthday,a[500015],b[500015],cnt,pos1[500015],pos2[500015];
bool c[500015];

vector<vector<int>>ayaka;


int main() {
  cin>>happy>>birthday;
  ayaka.push_back(vector<int>());
  for(int i=1;i<=happy;++i) cin>>a[i];
  for(int i=1;i<=happy;++i) cin>>b[i];
  for(int i=1;i<=happy;++i) {
    if(!c[i]) {
      int nt=i;
      ayaka.push_back(vector<int>());
      cnt++;
      while(!c[nt]) {
        c[nt]=1;
        pos1[nt]=cnt;
        ayaka[cnt].push_back(nt);
        pos2[nt]=ayaka[cnt].size()-1;
        nt=b[nt];
      }
    }
    int p=pos1[i],total=ayaka[p].size();
    cout<<a[ayaka[p][( (birthday%total) + pos2[i] )%total] ]<< " ";
  }
  return 0;
}