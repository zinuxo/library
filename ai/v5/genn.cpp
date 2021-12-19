#include<bits/stdc++.h>
using namespace std;
mt19937 R(time(0));
vector<int>q;
int ch[99][2],i,xb=1,x;
char c[3][99]={"andb","xorb","orb"};
void dfs(int x){
	if(ch[x][1]){
		printf("( \"%s\" ( ",c[R()%3]);
		dfs(ch[x][0]);
		printf(" ( ");
		dfs(ch[x][1]);
		printf(" \"E\" ) ) )");
	}else if(ch[x][0]){
		printf("( \"notb\" ( ");
		dfs(ch[x][1]);
		printf(" \"E\" ) )");
	}else{
		printf("\"%d\"",R()%2);
	}
}
int main(){
	q.push_back(1);
	for(;xb<10;){
		int i=R()%q.size();
		x=q[i];q.erase(q.begin()+i);
		if(R()%5){
			ch[x][0]=++xb;ch[x][1]=++xb;
			q.push_back(xb-1);q.push_back(xb);
		}else{
			ch[x][0]=++xb;q.push_back(xb);
		}
	}
	dfs(1);puts("");
}
