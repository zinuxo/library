#include"solver.hpp"
inline void init(){
/*
	basetype["C"]='c';
	basetype["L"]='l';
	basetype["Bi"]='c';
	basetype["O"]='c';
	basetype["Bo"]='l';
	basetype["T"]='l';
*/
	prog*p;
	p=new prog;p->name="I";p->inputsize=0;name_prog[p->name]=p;
	p=new prog;p->name="L";p->inputsize=1;name_prog[p->name]=p;p->rank=1;p->outputtype="Bi";//p->vec={name_prog["I-L"]};
	p=new prog;p->name="R";p->inputsize=1;name_prog[p->name]=p;p->rank=1;p->outputtype="L";//p->vec={name_prog["I-L"]};
	p=new prog;p->name="C";p->inputsize=2;name_prog[p->name]=p;p->rank=1;p->outputtype="L";//p->vec={name_prog["I-Bi"],name_prog["I-L"]};
//	t[0].c='F';
/*
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
*/
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
//solver S;
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
/*
input type
input function
output function
execute function
problem solve
*/
//	freopen("1tmp","r",stdin);
	freopen("13","r",stdin);
	init();
	for(;;){
		string s;
		cin>>s;
		if(s=="EXIT")break;
		if(s=="IT"){
			type*p=new type;
			p->input();
			if(p->name=="Bi")zero=name_atomid["0"];
		}
		if(s=="IF"){
			string s;
			cin>>s;cin>>s;
if(s=="EBT")
s=s;
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
//			S.work();
		}
		if(s=="Runcmp"){
int tot=0;
			vector<tuple<int,int,int>>vect,vect2;
//			for(int T=100;T--;){
//				int x=(R()%127),y=(R()%127);		
//cerr<<x<<' '<<y<<endl;
			for(int x=0;x<32;++x)for(int y=0;y<32;++y){
				V ve={to_tree(x),to_tree(y)};
//write(ve[0]);write(ve[1]);return 0;
				for(;;){
					int x=name_prog["Cmp"]->exec(ve).first;
					vect2.push_back({ve[0],ve[1],x});
					if(!t[ve[0]].r || !t[ve[1]].r)break;
					bool fl=0;
					for(int&x:ve)x=t[x].r,fl|=!x;
					if(fl)break;
				}
			}
			printf("Data1\n%d\n\n",(int)vect2.size());
			for(auto u:vect2){
				int a,b,c;tie(a,b,c)=u;
				write(a);puts("");
				write(b);puts("");
				write(c);puts("");
				puts("");
			}
			printf("Data2\n0\n\n");
		}
	}
}
