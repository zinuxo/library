#include"solver.hpp"
inline void init(){
	prog*p;
	p=new prog;p->name="I";p->inputsize=0;name_prog[p->name]=p;
	p=new prog;p->name="L";p->inputsize=1;name_prog[p->name]=p;p->rank=1;p->outputtype="Bi";
	p=new prog;p->name="R";p->inputsize=1;name_prog[p->name]=p;p->rank=1;p->outputtype="L";
	p=new prog;p->name="C";p->inputsize=2;name_prog[p->name]=p;p->rank=1;p->outputtype="L";
	type*q;
	auto fafa=[&](vector<string>atom){
		for(int i=0;i<atom.size();++i){
			name_atomid[atom[i]]=atomid_val.size();
			atomid_val.push_back({q,i});
		}
	};
	q=new type;q->name="R";q->atom={"A","F"};name_type[q->name]=q;
	fafa(q->atom);
	q=new type;q->name="Emp";q->atom={"E"};name_type[q->name]=q;
	fafa(q->atom);
	t[F.first=++tcnt]=node{name_atomid["F"],0,0};E=name_atomid["E"];
}
solver S;
int to_tree(int x){
	if(x<2){
		int a=++tcnt,b=++tcnt,c=++tcnt;
		t[a]=node{(char)-1,b,c};t[b]=node{x+zero,0,0};t[c]=node{E,0,0};
		return a;
	}
	int a=++tcnt,b=++tcnt;
	t[b]={(x&1)+zero,0,0};t[a]=node{-1,b,to_tree(x>>1)};
	return a;
}
int main(){
//	freopen("13","r",stdin);
	init();
	for(;;){
		string s;
		cin>>s;
		if(s=="EXIT")break;
		if(s=="IT"){
			type*p=new type;
			p->input();
			if(p->name=="Bi")zero=name_atomid["0"];
			if(p->name=="L"){
				name_prog["L"]->vec={name_prog["I-L"]};
				name_prog["R"]->vec={name_prog["I-L"]};
				name_prog["C"]->vec={name_prog["I-Bi"],name_prog["I-L"]};
			}
		}
		if(s=="winla"){
			for(int i=0;i<127;++i)for(int j=0;j<127;++j){
//cerr<<i<<' '<<j<<endl;
				V ve={to_tree(i),to_tree(j)};
				int a=name_prog["Cmp"]->exec(ve).first,b=name_prog["Cmp2"]->exec(ve).first;
				assert(!t[a].r && !t[b].r);
				assert(t[a].c==t[b].c);
			}
		}
		if(s=="IF"){
			string s;
			cin>>s;cin>>s;
			auto it=name_prog.find(s);
			if(it!=name_prog.end()){
				it->second->input(1,s);
			}else{
				prog*p=new prog;
				p->input(1,s);
			}
		}
		if(s=="OF"){
			cin>>s;
			name_prog[s]->output();
		}
		if(s=="EF"){
			string s;
			cin>>s;
			prog*p=name_prog[s];
			V vec;
			for(int i=0;i<p->inputsize;++i)vec.push_back(read(fixstr(p->vec[i]->name)));
			int x,y;
			tie(x,y)=p->exec(vec);
			write(x);
			puts("");
			printf("cost:%d\n",y);
		}
		if(s=="PS"){
			S.work();
		}
	}
}
