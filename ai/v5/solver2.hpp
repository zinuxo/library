#include"prog.hpp"
//const double w1=0.9,w2=1.5,w3=0.7;
//const double w1=0.9,w2=1,w3=0.75,w4=150;
//const double w1=0.99,w2=1.5,w3=0.7,w4=150;
const double w1=0.99,w2=1,w3=0.7,w4=100;
struct solver{
	map<V,int>in_out;
	V out;
	vector<double>reward_prog_0;
	vector<prog*>prog_list;
	double reward_rec;
	inline void work();
	inline void init();
};
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
/*
	prog sample;
	sample.inner_input(
"Def AnotherMul 2 5 L\n"
"	I-L ;\n"
"	I-L ;\n"
"	R v0 ;\n"
"	AnotherMul v2 v1 ;\n"
"	L v0 ;\n"
"	Mul01' v4 v1 ;\n"
"	L v5 ;\n"
"	R v5 ;\n"
"	Plus v3 v7 ;\n"
"	C v6 v8 ;\n"
"	Re v9 ;\n"
"End\n"
*/
/*
"Def Mul 2 5 L\n"
"	I-L ;\n"
"	I-L ;\n"
"	L v0 ;\n"
"	R v0 ;\n"
"	L v1 ;\n"
"	R v1 ;\n"
"	Mul v3 v1 ;\n"
"	Mul01 v2 v5 ;\n"
"	And v2 v4 ;\n"
"	Plus v6 v7 ;\n"
"	C v8 v9 ;\n"
"	Re v11 ;\n"
"End\n"
*/
//	);
//	for(auto&u:sample.vec)if(u->name==sample.name)u=prog_list.back();
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
static int lst;
if(scnt>lst+1e3){
	lst=scnt,fprintf(stderr,"%d %.6f\n",scnt,v.W);
	st[scnt].pr.output();
}
if(scnt>=273){
	static bool fl;
	if(!fl){
		bool fll=1;
//		for(int i=0;i<7;++i)if(st[id].pr.vec[i]!=sample.vec[i] || st[id].pr.edge[i]!=sample.edge[i])fll=0;
//		if(fll){
//cerr<<"found"<<endl;
//fl=1;
//		}
	}
}
if(id==273)
cerr<<id<<endl;
if(scnt>1e4){
++id,--id;
}
//if(scnt>6e4){
//	puts("gang ke lian");
//	exit(0);
//}
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
if(id==273)
cerr<<id<<endl;
int nnn=5;
if(v.pr.vec.size()==nnn){
	bool fll=1;
//	for(int i=0;i<nnn;++i)if(v.pr.vec[i]!=sample.vec[i] || v.pr.edge[i]!=sample.edge[i])fll=0;
if(fll && i==5)
++i,--i;
//	if(fll)
//++id,--id
//,cerr<<i<<endl;
;
}
		v.used[i>>5]|=1<<(i&31);
		V nres;V edge(prog_list[i]->inputsize);
		function<void(int)>dfs=[&](int d){
			if(d==prog_list[i]->inputsize){
int nnn=5;
if(v.pr.vec.size()==nnn){
	bool fll=1;
//	for(int i=0;i<nnn;++i)if(v.pr.vec[i]!=sample.vec[i] || v.pr.edge[i]!=sample.edge[i])fll=0;
if(fll && i==5 && edge==V{4,1})
++i,--i;
//	if(fll)
//++id,--id
//,cerr<<i<<endl;
;
}
				auto ns=v;
if(id==6126 && i==9 && edge==V{3,1})
++d,--d;
bool fll;
fll=1;
//for(int i=0;i<5;++i)if(ns.pr.vec[i]!=sample.vec[i] || ns.pr.edge[i]!=sample.edge[i])fll=0;
//if(fll)
//++i,--i,cerr<<5<<endl;
fll=1;
//for(int i=0;i<6;++i)if(ns.pr.vec[i]!=sample.vec[i] || ns.pr.edge[i]!=sample.edge[i])fll=0;
//if(fll)
//++i,--i,cerr<<6<<endl;
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
			cost+=pow(30,s1-s2-1);
		}
		for(int j=0;j<datanum;++j){
			V v(inputsize);
			for(int k=0;k<inputsize;++k)v[k]=To_int(res[edge[k]][j]);
			auto it=S.in_out.find(v);
			if(it==S.in_out.end())
				return Fa;//result can't rec.
			nres[j]=it->second;
		}
//		cost+=datanum*3;
//		return {-1,cost,30<<rank};
		return {-1,cost,1145};
	}else if(p->name=="L"){
		for(int j=0;j<datanum;++j){
			x=res[edge[0]][j];
			if(t[x].c!=-1)return Fa;
			cost+=1;
//			nres[j]=t[x].l;
			if(!t[x].l)nres[j]=x;
				else nres[j]=t[x].l;
		}
		return {-1,cost,S.reward_prog_0[1]};
	}else if(p->name=="R"){
		for(int j=0;j<datanum;++j){
			x=res[edge[0]][j];
			if(t[x].c!=-1)return Fa;
			cost+=1;
//			nres[j]=t[x].r;
			if(!t[x].r)nres[j]=x;
				else nres[j]=t[x].r;
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
