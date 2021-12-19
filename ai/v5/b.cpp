/*
'E' empty_list
'F' fail to run
*/
#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef pair<int,int>P;
typedef vector<int>V;
const int mo=998244353;
mt19937_64 R(1919810);
inline double ra(){
	long long x=(1ll<<50)-1;
	return (R()&x)*1.0/x;
}
struct node{
	char c;
	//'c' char | -1 list
	int l,r;
}t[1<<26];
int tcnt;
int size(int x){
	if(t[x].c==-1)return size(t[x].l)+size(t[x].r);
	return 1;
}
bool equal(int x,int y){
	if(t[x].c==-1 && t[y].c==-1)return equal(t[x].l,t[y].l) && equal(t[x].r,t[y].r);
	return t[x].c==t[y].c;
}
int to_int(int x){
	if(t[x].c>0)return t[x].c-'0';
	if(!t[x].r)return 0;
	return to_int(t[x].r)<<1|to_int(t[x].l);
}
/*
type set:
L    l list
Bi   c bit
O    c operator
Bo   l binary operation
T    l expression tree
*/
//map<string,char>basetype;
struct prog{
	string name,outputtype;
	int inputsize,rank;
	vector<prog*>vec;
	vector<V>edge;
	int isre;
	P re0,re1,re2;
	inline void input();
	inline P exec(V input);
	inline void output(){
		cout<<"Def "<<name<<' '<<inputsize<<' '<<rank<<'\n';
		for(int i=0;i<vec.size();++i){
			cout<<'	';
			if(vec[i]->isre){
				auto out=[&](P u){
					if(u.first==1)cout<<'v'<<u.second;
						else cout<<'\''<<char(u.second)<<'\'';
				};
				cout<<"Re ";
				out(vec[i]->re0);
				if(vec[i]->isre==1){
				}else{
					cout<<" If ";
					out(vec[i]->re1);cout<<" = ";out(vec[i]->re2);
				}
				cout<<" ;\n";
			}else{
				cout<<vec[i]->name;
				for(int x:edge[i])cout<<" v"<<x;
				cout<<" ;\n";
			}
		}
		cout<<"End\n";
	}
};
/*
input
type-checking
*/
map<string,prog*>name_prog;
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
	p=new prog;p->name="I-Bi";name_prog[p->name]=p;p->outputtype="Bi";
	p=new prog;p->name="I-L";name_prog[p->name]=p;p->outputtype="L";
	p=new prog;p->name="L";p->inputsize=1;name_prog[p->name]=p;p->rank=1;p->outputtype="Bi";p->vec={name_prog["I-L"]};
	p=new prog;p->name="R";p->inputsize=1;name_prog[p->name]=p;p->rank=1;p->outputtype="L";p->vec={name_prog["I-L"]};
	p=new prog;p->name="C";p->inputsize=2;name_prog[p->name]=p;p->rank=1;p->outputtype="L";p->vec={name_prog["I-Bi"],name_prog["I-L"]};
	t[0].c='F';
}
inline prog*newRe(P a){
	static int count;
	prog*p=new prog;
	p->name="Re"+to_string(count++);
	p->isre=1;p->re0=a;
	name_prog[p->name]=p;
	return p;
}
inline prog*newReIf(P a,P b,P c){
	static int count;
	prog*p=new prog;
	p->name="ReIf"+to_string(count++);
	p->isre=2;p->re0=a;p->re1=b;p->re2=c;
	name_prog[p->name]=p;
	return p;
}
inline void prog::input(){
/*
Def And 2
	I-Bi ;
	I-Bi ;
	Re '0' If v0 = '0' ;
	Re v1 ;
End
*/
	string s;
	cin>>s;//s=="Def" this time
	cin>>name;
if(name=="Plus01")
s=s;
	name_prog[name]=this;
	cin>>inputsize>>rank>>outputtype;
	for(;;){
		cin>>s;
		if(s=="End")break;
		auto in=[&](){
			char c[99];int x;
			scanf("%s",c);
			if(c[0]=='v'){
				sscanf(c+1,"%d",&x);
				return P{1,x};
			}else return P{0,(int)c[1]};
		};
		if(s=="Re"){
			edge.push_back({});
			auto a=in();
			cin>>s;
			if(s=="If"){
				auto b=in();
				cin>>s;
				auto c=in();
				cin>>s;
				vec.push_back(newReIf(a,b,c));
			}else vec.push_back(newRe(a));
			continue;
		}
		auto p=name_prog[s];
		vec.push_back(p);
		edge.push_back(V(p->inputsize));
		for(int&x:edge.back())x=in().second;
		cin>>s;
	}
}
const P F={0,0};
inline P prog::exec(V input){
	if(name=="I-Bi")return t[input[0]].c=='0' || t[input[0]].c=='1'?P{1,1}:F;
	if(name=="I-L")return t[input[0]].c==-1?P{1,1}:F;//need changing
	if(input.size()!=inputsize)return F;
	int i,x,y,cost=0;
	V res(vec.size());
	for(i=0;i<vec.size();++i){
		if(i<inputsize){
			auto z=vec[i]->exec({input[i]});
			if(z==F)return F;
			cost+=z.second;
			res[i]=input[i];
		}else if(vec[i]->name=="L"){
			x=res[edge[i][0]];
			if(t[x].c!=-1)return F;
			cost+=1;
			res[i]=t[x].l;
		}else if(vec[i]->name=="R"){
			x=res[edge[i][0]];
			if(t[x].c!=-1)return F;
			cost+=1;
			res[i]=t[x].r;
		}else if(vec[i]->name=="C"){
			x=res[edge[i][0]];y=res[edge[i][1]];
			cost+=1;
			res[i]=++tcnt;
			t[res[i]]=node{-1,x,y};
		}else if(vec[i]->isre==1){
			cost+=1;
			if(vec[i]->re0.first==0){
				res[i]=++tcnt;
				t[res[i]]=node{vec[i]->re0.second=='E'?-1:(char)vec[i]->re0.second,0,0};
			}else res[i]=res[vec[i]->re0.second];
			return {res[i],cost};
		}else if(vec[i]->isre==2){
			cost+=2;
			if(vec[i]->re0.first==0){
				res[i]=++tcnt;
				t[res[i]]=node{(char)vec[i]->re0.second,0,0};
			}else res[i]=res[vec[i]->re0.second];
			auto getval=[&](P u){
				return u.first?t[res[u.second]].c:u.second;
			};
			int a=getval(vec[i]->re1),b=getval(vec[i]->re2);
			if(b=='E' && a==-1){
				if(t[res[vec[i]->re1.second]].l==0)return {res[i],cost};
				continue;
			}
			if(a<0 || b<0)return F;
			if(a==b)return {res[i],cost};
		}else{
			V newinput(edge[i].size());
			for(int j=0;j<edge[i].size();++j)newinput[j]=res[edge[i][j]];
			int f1,f2;
			auto z=vec[i]->exec(newinput);
			if(z==F)return F;
			tie(f1,f2)=z;
			res[i]=f1;cost+=f2;
		}
	}
	return F;
}
inline int read(string type){
	if(type[0]=='I')type=type.substr(2,type.size()-2);
	char c[999],*p;int ret;
	for(p=c;*p=getchar(),isspace(*p););++p;
	for(;*p=getchar(),*p++!='\n';);
	if(type=="Bi"){
		ret=++tcnt;
		t[ret]=node{c[0],0,0};
		assert(t[ret].c=='0' || t[ret].c=='1');
		return ret;
	}
	if(type=="L"){
		p=c;
		vector<char>vec;
		for(;;){
			for(;*p!='\n' && isspace(*p);++p);
			if(*p=='\n')break;
			vec.push_back(*p++);
		}
		reverse(vec.begin(),vec.end());
		int u=++tcnt,v;t[u]=node{-1,0,0};
		if(vec==vector<char>{'E'})return u;
		for(char c:vec){
			v=++tcnt;t[v]=node{c,0,0};
			ret=++tcnt;t[ret]=node{-1,v,u};u=ret;
		}
		return ret;
	}
	assert(0);
}
inline void write(string type,int x){
	if(type=="Bi"){
		putchar(t[x].c);
	}else if(type=="L"){
		if(t[x].r)write("Bi",t[x].l),write("L",t[x].r);
	}
}
const tuple<int,int,double>Fa=make_tuple(0,0,0);
//const double w1=0.9,w2=1.5,w3=0.7;
const double w1=0.99,w2=1,w3=0.7,w4=100;
struct solver{
	map<V,int>in_out;
	V out;
	vector<double>reward_prog_0;
	vector<prog*>prog_list;
	double reward_rec;
	inline void work();
	inline void init();
}S;
struct Prog:prog{
	vector<V>Res;
	inline tuple<int,int,double>exec(solver&S,prog*p,const vector<V>&res,V&nres,const V&edge,int i);
};
Prog start;//fuck。
int To_int(int u){
	if(!t[u].r)return -1;
	return to_int(u);
}
inline void solver::init(){
	int maxrank=1,i,j;
	prog_list.clear();
	in_out.clear();
	for(auto u:name_prog){
		auto p=u.second;
		if(p->name[0]=='I')continue;
		if(p->name[0]=='R' && p->name[1]=='e')continue;
		maxrank=max(maxrank,p->rank);
//		if(p->name=="L")continue;
//		if(p->name=="R")continue;
//		if(p->name=="C")continue;
		prog_list.push_back(p);
	}
	reward_prog_0.resize(maxrank+1);
	for(i=0;i<=maxrank;++i)reward_prog_0[i]=pow(w2,i);
	cin>>start.name>>start.inputsize;
	string s,output_type;vector<string>input_type;int datanum;
	input_type.resize(start.inputsize);
	start.Res.resize(start.inputsize);
	for(i=0;i<start.inputsize;++i){
		cin>>input_type[i];
		start.vec.push_back(name_prog["I-"+input_type[i]]);
		start.edge.push_back({});
	}
	cin>>output_type;
	cin>>s;assert(s=="Data1");
	cin>>datanum;
	for(i=0;i<start.inputsize;++i)start.Res[i].resize(datanum);
	out.resize(datanum);
	for(i=0;i<datanum;++i){
		V ve(start.inputsize);
		for(j=0;j<start.inputsize;++j){
			start.Res[j][i]=read(input_type[j]);
			ve[j]=To_int(start.Res[j][i]);
		}
		out[i]=read(output_type);
		in_out[ve]=out[i];
	}
	cin>>s;assert(s=="Data2");
	int datanum2;
	cin>>datanum2;
	for(;datanum2--;){
		V ve(start.inputsize);
		for(j=0;j<start.inputsize;++j){
			ve[j]=To_int(read(input_type[j]));
		}
		in_out[ve]=read(output_type);
	}
	static prog pp;pp.name=start.name;pp.vec=start.vec;pp.inputsize=start.inputsize;pp.outputtype=output_type;
	prog_list.push_back(&pp);
}
struct state{
	double W;
	Prog pr;
	int id,cost;
	vector<unsigned>used;
};
typedef __gnu_pbds::priority_queue<pair<double,int>>H;
inline void solver::work(){
	init();
	static const int N=1145141;
	static state st[N];
	static H::point_iterator it[N];
	int scnt=0;
	map<vector<V>,int>mp;
	H q;
	auto upd=[&](state ns){
		auto ve=ns.pr.Res;
//if(ve.size()>20)return;
//if(ns.cost>200)return;
		sort(ve.begin(),ve.end());
		auto iter=unique(ve.begin(),ve.end());if(iter!=ve.end())return;
		auto ite=mp.find(ve);
		if(ite==mp.end()){
			int id=++scnt;
			st[id]=ns;st[id].id=id;
			mp[ve]=id;
			it[id]=q.push({st[id].W/(st[id].cost+w4),id});
		}else{
			int id=ite->second;
			if(ra()<0.5)st[id].pr=ns.pr,st[id].cost=ns.cost;//need change
			q.erase(it[id]);
			st[id].W=(st[id].W+ns.W)/2;
			it[id]=q.push({st[id].W/(st[id].cost+w4),id});
		}
	};
	state u;
	u.W=1;u.pr=start;u.id=u.cost=0;u.used.resize(prog_list.size()+31>>5);
	upd(u);
	for(;;){
		int id=q.top().second;q.pop();
		state&v=st[id];
fprintf(stderr,"%d %.6f\n",scnt,v.W);
if(scnt>1e4){
++id,--id;
}
if(scnt>6e5){
	puts("gang ke lian");
	exit(0);
}
		int zz=0;
		for(int i=0;i<v.pr.vec.size();++i){
			if(v.pr.vec[i]->name=="L" && v.pr.edge[i]==V{0})++zz;
			if(v.pr.vec[i]->name=="L" && v.pr.edge[i]==V{1})++zz;
			if(v.pr.vec[i]->name=="R" && v.pr.edge[i]==V{0})++zz;
			if(v.pr.vec[i]->name=="R" && v.pr.edge[i]==V{1})++zz;
		}
if(zz==4)
++zz,--zz;
		v.W*=w1;
		it[id]=q.push({v.W/(v.cost+w4),id});		
		int i;
		if(1<<prog_list.size()==v.used[0]+1)continue;
		for(;;){
			i=R()%prog_list.size();
			if(v.used[i>>5]>>(i&31)&1)continue;
			break;
		}
if(id==6126)
++i,--i;
		v.used[i>>5]|=1<<(i&31);
		V nres;V edge(prog_list[i]->inputsize);
		function<void(int)>dfs=[&](int d){
			if(d==prog_list[i]->inputsize){
				auto ns=v;
if(id==6126 && i==9 && edge==V{3,1})
++d,--d;
				auto ret=ns.pr.exec(*this,prog_list[i],v.pr.Res,nres,edge,v.pr.Res.size());
				if(ret==Fa)return;
				ns.pr.Res.push_back(nres);
				ns.pr.edge.push_back(edge);
				ns.pr.vec.push_back(prog_list[i]);
				ns.W+=get<2>(ret);ns.W*=w3;
				ns.cost=v.cost+get<1>(ret);
				for(auto&x:ns.used)x=0;
				upd(ns);
				bool fl=1;
				for(int i=0;i<out.size();++i)fl&=equal(out[i],ns.pr.Res.back().at(i));
				if(fl){
					ns.pr.output();
					exit(0);
				}
				return;
			}
//static int cnt=0;cerr<<++cnt<<endl;
			for(int k=0;k<v.pr.Res.size();++k)
				if("I-"+v.pr.vec[k]->outputtype==prog_list[i]->vec[d]->name)
					edge[d]=k,dfs(d+1);
		};
		dfs(0);		
	}
}
int main(){
/*
input type
input function
output function
execute function
problem solve
*/
	freopen("1","r",stdin);
	init();
	for(;;){
		string s;
		cin>>s;
		if(s=="EXIT")break;
		if(s=="IT");
		if(s=="IF"){
			prog*p=new prog;
			p->input();
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
			for(int i=0;i<p->inputsize;++i)vec.push_back(read(p->vec[i]->name));
			int x,y;
			tie(x,y)=p->exec(vec);
			if(t[x].c==-1)write("L",x);else write("Bi",x);
			puts("");
			printf("cost:%d\n",y);
		}
		if(s=="PS"){
			S.work();
		}
	}
}
inline tuple<int,int,double>Prog::exec(solver&S,prog*p,const vector<V>&res,V&nres,const V&edge,int i){
	int cost=0,x,y;
	int datanum=res[0].size();
	nres.resize(datanum);
	if(p->name==name){
//cerr<<"winwinwin"<<endl;
		for(int j=0;j<datanum;++j){
			int s1=0,s2=0;
			for(int k=0;k<inputsize;++k)s1+=size(res[k][j]),s2+=size(res[edge[k]][j]);
			if(s1<=s2)return Fa;//size doesn't decrease.
		}
		for(int j=0;j<datanum;++j){
			V v(inputsize);
			for(int k=0;k<inputsize;++k)v[k]=To_int(res[edge[k]][j]);
			auto it=S.in_out.find(v);
			if(it==S.in_out.end())
				return Fa;//result can't rec.
			nres[j]=it->second;
		}
		return {-1,cost,1145};
	}else if(p->name=="L"){
		for(int j=0;j<datanum;++j){
			x=res[edge[0]][j];
			if(t[x].c!=-1)return Fa;
			cost+=1;
			nres[j]=t[x].l;
		}
		return {-1,cost,S.reward_prog_0[1]};
	}else if(p->name=="R"){
		for(int j=0;j<datanum;++j){
			x=res[edge[0]][j];
			if(t[x].c!=-1)return Fa;
			cost+=1;
			nres[j]=t[x].r;
		}
		return {-1,cost,S.reward_prog_0[1]};
	}else if(p->name=="C"){
		for(int j=0;j<datanum;++j){
			x=res[edge[0]][j];y=res[edge[1]][j];
			cost+=1;
			nres[j]=++tcnt;
			t[nres[j]]=node{-1,x,y};
		}
		return {-1,cost,S.reward_prog_0[1]};
	}else{
		V newinput(edge.size());
		for(int j=0;j<datanum;++j){
			for(int k=0;k<edge.size();++k)newinput[k]=res[edge[k]][j];
			int f1,f2;
			auto z=p->exec(newinput);
			if(z.first==0)return Fa;
			tie(f1,f2)=z;
			nres[j]=f1;cost+=f2;
		}
		return {-1,cost,S.reward_prog_0[p->rank]};
	}
}
