#include"head.hpp"
inline int dist(int x,int y){
	bool b1=t[x].c==-1,b2=t[y].c==-1;
	if(!b1 && b2)return 114514;
	if(!b1 && !b2)return t[x].c==t[y].c?0:1;
	if(b1 && b2){
		if(!t[y].r)return 1;
		int sx=size(x),sy=size(y);
		if(sx<sy)return 114514;
		int z=x;
		for(int i=sx;i>sy;--i)z=t[z].r;
		return equal(z,y)?sx-sy:114514;
	}
	if(b1 && !b2){
		if(!t[x].r)return 114514;
		if(t[t[x].l].c==t[y].c)return 0;
		return 1;
	}
	assert(0);
}
