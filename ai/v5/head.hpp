/*
'E' empty_list
'F' fail to run
*/
#pragma once
#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef pair<int,int>P;
typedef vector<int>V;
typedef vector<unsigned>Vu;
inline int tst(const Vu&v,int i){return v[i>>5]>>(i&31)&1;}
inline void setv(Vu&v,int i){v[i>>5]|=1u<<(i&31);}
P F={-114514,0};
int E,zero;
const tuple<int,int,double>Fa=make_tuple(0,0,0);
const int mo=998244353;
mt19937_64 R(1919810);
//mt19937_64 R(time(0));
inline string fixstr(string s){
	assert(s.size()>2);
	return s.substr(2,s.size()-2);
}
int poww(int x,int y){
	int ans=1;
	for(;y;y>>=1,x=min(1ll*x*x,1ll<<30))if(y&1)ans=min(1ll*x*ans,1ll<<30);
	return ans;
}
inline double ra(){
	long long x=(1ll<<50)-1;
	return (R()&x)*1.0/x;
}
struct node{
	int c,l,r;
}t[1<<27];
int tcnt;
int size(int x){
	if(t[x].c==-1)return size(t[x].l)+size(t[x].r);
	return 1;
}
bool equal(int x,int y){
	if(t[x].c==-1 && t[y].c==-1)return equal(t[x].l,t[y].l) && equal(t[x].r,t[y].r);
	return t[x].c==t[y].c;
}
int to_int(int x){//need change now
	if(!t[x].r)return t[x].c==E?0:t[x].c-zero;
	return to_int(t[x].r)<<1|to_int(t[x].l);
}
int cmptree(int x,int y){//need change now
//	return x==y?0:(x<y?1:-1);
	if((t[x].c==-1)!=(t[y].c==-1))return t[x].c==-1?-1:1;
	if(t[x].c!=-1)return t[x].c==t[y].c?0:(t[x].c<t[y].c?1:-1);
	bool fx=!t[x].l,fy=!t[y].l;
	if(fx || fy)return fx==fy?0:(fx>fy?1:-1);
	char cx=t[t[x].l].c,cy=t[t[y].l].c;
	return cx==cy?cmptree(t[x].r,t[y].r):(cx<cy?1:-1);
}
int gethash(int x){//need change now
	if(!t[x].l)return t[x].c+3;
	return (1145ll*gethash(t[x].r)+t[t[x].l].c+3)%mo;
}
/*
type set:
L    l list
Bi   c bit
O    c operator
Bo   l binary operation
T    l expression tree
*/
