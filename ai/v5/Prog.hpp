#pragma once
#include"head.hpp"
struct prog{
	string name,outputtype;
	int inputsize,rank;
	vector<prog*>vec;
	vector<V>edge;
	int isre;
	P rev;
	vector<P>rel;
	prog(){isre=0;}
	inline void input(bool tp=0,string sss="");
	inline void inner_input(string st);
	inline P exec(V input);
	inline void output();
};
map<string,prog*>name_prog;
