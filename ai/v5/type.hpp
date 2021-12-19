#pragma once
#include"prog.hpp"
struct type{
	string name;
	vector<string>atom;
	prog*check;
	inline void input();
};
map<string,type*>name_type;
map<string,int>name_atomid;
vector<pair<type*,int>>atomid_val;
inline void type::input(){
	cin>>name;
	assert(!name_type.count(name));
	name_type[name]=this;
	int s;cin>>s;atom.resize(s);
	for(int i=0;i<s;++i){
		cin>>atom[i];
		if(atom[i]!="E"){
			assert(!name_atomid.count(atom[i]));
			name_atomid[atom[i]]=atomid_val.size();
			atomid_val.push_back({this,i});
		}
	}
	check=new prog;
	check->input();
	auto p=new prog;p->name="I-"+name;p->inputsize=0;name_prog[p->name]=p;p->outputtype=name;
}
inline int read(string type){
	static int st[9999];int w=0;
	for(;;){
		string s;
		cin>>s;
		if(s=="(")st[++w]=-1;else if(s==")"){
			int u=++tcnt;
			t[u]=node{-1,st[w-1],st[w]};
			st[w-=2]=u;
		}else{
			s=s.substr(1,s.size()-2);
			t[st[++w]=++tcnt]=node{name_atomid[s],0,0};
		}
		if(w==1 && st[w]!=-1)break;
	}
//	assert(w==1 && t[name_type[type]->check->exec({st[1]}).first].c==name_atomid["A"]);
	return st[1];
}
inline void write(int x){
	if(!t[x].l){
		type*p;int i;tie(p,i)=atomid_val[t[x].c];
		cout<<"\""<<p->atom[i]<<"\"";
	}else{
		cout<<"( ";
		write(t[x].l);
		cout<<' ';
		write(t[x].r);
		cout<<" )";
	}
}
