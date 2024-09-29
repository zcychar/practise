#include<iostream>
#include<string>
using namespace std;
int main(){
	string s[600];
    cnt = 0-;
	while(scanf("%s",&s[++cnt]));
	for(int i=cnt;i>=1;--i){
		int len=s[i].length();
		if(int(s[i][0])>=int('A')&&int(s[i][0])<=int('Z')){
			for(int j=0;j<=len-1;++j)cout<< s[i][j]-'A'+'a';
		}else if(int(s[i][0])>=int('a')&&int(s[i][0])<=int('z')){
			for(int j=0;j<=len-1;++j)cout<< s[i][j]-'a'+'A';
		}else{
			for(int j=len-1;j>=0;--j)cout<< s[i][j];
		}
		cout<<" ";
	}
	return 0;
}