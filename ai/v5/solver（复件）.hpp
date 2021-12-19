#include"Prog.hpp"
#include"measure.hpp"
struct state{
	double W;
	Prog pr;
	int id,cost;
	vector<unsigned>used,used2,svd;
	bool isre;
};
typedef __gnu_pbds::priority_queue<pair<double,int>>H;
inline void solver::work(){
	init();
	static const int N=1145141;
	static state st[N];
	static H::point_iterator it[N];
	int scnt=0;
	map<vector<P>,int>mp0;int id0=0;
	map<vector<int>,int>mp;
	H q;
	Prog sample;
/*
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
	);
*/
	sample.Res=start.Res;
	static int cntt[99];int limm=0;
	auto getid0=[&](const vector<P>&v){
		auto zz=mp0.insert({v,id0+1});
		int ret;
		if(!zz.second)ret=zz.first->second;
			else ret=++id0;
		if(ret<=limm){
			if(!cntt[ret])cerr<<"found "<<ret<<endl;
			++cntt[ret];
		}
		return ret;
	};
	Vu sample_svd(out.size()+31>>5);
	for(int i=2;i<sample.vec.size();++i){
//inline tuple<int,int,double>Prog::exec(solver&S,prog*p,const vector<V>&res,V&nres,const V&edge,int i){
		V nres;
		sample.exec(*this,sample.vec[i],sample.Res,nres,sample_svd,sample_svd,sample.edge[i],i);
		sample.Res.push_back(nres);
		getid0(trans(sample.Res.back()));
	}
	limm=id0;
	auto upd=[&](const state&ns){
		vector<int>ve(ns.pr.Res.size());
		for(int i=0;i<ns.pr.Res.size();++i)ve[i]=getid0(trans(ns.pr.Res[i]));
		sort(ve.begin(),ve.end());
//		if(unique(ve.begin(),ve.end())!=ve.end())return;
		set<int>se(ve.begin(),ve.end());
		if(se.size()!=ve.size())
++id0,--id0;
		if(se.count(8)){
//for(int x:se)if(x<=limm)cerr<<x<<' ';cerr<<"ffdsafdsa\n";
		}
		auto iter=unique(ve.begin(),ve.end());if(iter!=ve.end())return;
		auto ite=mp.find(ve);
		if(ite==mp.end()){
			int id=++scnt;
			st[id]=ns;st[id].id=id;
			mp[ve]=id;
//			it[id]=q.push({st[id].W/(st[id].cost+w4),id});
			it[id]=q.push({st[id].W,id});
auto tmp=ns;tmp.pr.output();
if(tmp.pr.vec.back()->isre)
++id,--id;
		}else{
			return;//???
			int id=ite->second;
			if(ra()<0.5)st[id].pr=ns.pr,st[id].cost=ns.cost;//need change
			q.erase(it[id]);
			st[id].W=(st[id].W+ns.W)/2;
//			it[id]=q.push({st[id].W/(st[id].cost+w4),id});
			it[id]=q.push({st[id].W,id});
		}
	};
	state u;
	u.isre=0;
	u.W=100;u.pr=start;u.id=u.cost=0;
	u.used.resize(prog_list.size()+31>>5);
//	u.used2.resize(faa.a.size()+31>>5);
	u.svd.resize(out.size()+31>>5);
	upd(u);
	for(;;){
		int id=q.top().second;q.pop();
		state&v=st[id];
if(v.pr.vec.back()->rel.size()==6)
++id,--id;
//cerr<<scnt<<' '<<id<<endl;
static int steppp;
//cerr<<++steppp<<endl;
if(steppp==2630)
++id,--id;
if(steppp==84)
++id,--id;
static int lst;
if(scnt>lst+1e3){
	lst=scnt,fprintf(stderr,"%d %d %.6f\n",id0,scnt,v.W);
//	st[scnt/1000*1000].pr.output();
}
if(scnt>80000)exit(0);
//st[id].pr.output();
		v.W*=0.99;
		it[id]=q.push({v.W,id});
		int i;
		vector<prog*>func_type;
		prog*np;
		bool ffl;double nnw;
		if(v.isre){
			for(int j=0;j<v.pr.vec.size();++j)if(v.pr.vec[j]->outputtype=="Bi" || v.pr.vec[j]->outputtype=="Bo-opt"){
				auto work=[&](state&ns){
					V nres;
					auto ret=ns.pr.exec(*this,ns.pr.vec.back(),v.pr.Res,nres,v.svd,ns.svd,{},v.pr.Res.size());
if(ns.pr.vec.back()->rel.size()>0)
++i,--i;
					if(ret==Fa)return;
					int wa=-1-get<0>(ret),datanum=out.size();
					if(wa==0)ns.W*=get<2>(ret),ns.isre=0;else{
						if(ns.pr.vec.back()->rel.size()==2)ns.W*=pow(0.8,wa*1.0/datanum);
						if(ns.pr.vec.back()->rel.size()==4)return;
					}
					ns.cost=v.cost+get<1>(ret);//need change
					ns.pr.Res.back()=nres;
if(ns.pr.vec.back()->rel.size()==6)
++i,--i;
					upd(ns);
				};
				for(int k=0;k<v.pr.vec.size();++k)if(j!=k && v.pr.vec[k]->outputtype==v.pr.vec[j]->outputtype){
					auto ns=v;
					ns.pr.vec.back()=new prog;*ns.pr.vec.back()=*v.pr.vec.back();
					ns.pr.vec.back()->rel.push_back({1,j});
					ns.pr.vec.back()->rel.push_back({1,k});
					work(ns);
				}
				type*tp=name_type[v.pr.vec[j]->outputtype];
				for(int k=0;k<tp->atom.size();++k){
					auto ns=v;
					ns.pr.vec.back()=new prog;*ns.pr.vec.back()=*v.pr.vec.back();
					ns.pr.vec.back()->rel.push_back({1,j});
					ns.pr.vec.back()->rel.push_back({0,name_atomid[tp->atom[k]]});
					work(ns);
				}
			}
			continue;
		}
		auto check_re=[&](int i){
			if(v.pr.vec[i]->outputtype!=output_type)return 0;
			int datanum=out.size();
			for(int j=0;j<datanum;++j)if(equal(v.pr.Res[i][j],out[j]))return 1;
			return 0;
		};
		auto pbre=[&](int id){
			auto ns=v;ns.isre=1;
			prog*np=new prog;np->isre=1;np->rev={1,id};
			V nres;
			auto ret=ns.pr.exec(*this,np,v.pr.Res,nres,v.svd,ns.svd,{},v.pr.Res.size());
			if(ret==Fa)return;
			ns.W*=0.95;
			ns.pr.Res.push_back(nres);
			ns.pr.edge.push_back({});
			ns.pr.vec.push_back(np);
			ns.cost=v.cost+get<1>(ret);
			upd(ns);
		};
		int ss=prog_list.size()-1;
if(v.pr.vec.back()->name=="Geta")
++ss,--ss;
		if(!tst(v.used,ss) && ra()<0.3){
			for(int i=0;i<v.pr.vec.size();++i)if(check_re(i))
				pbre(i);
			setv(v.used,ss);
			continue;
		}
//		if(ra()<w9){
		if(true){
			ffl=0;
			if(1<<prog_list.size()-1==v.used[0]+1)continue;
			if(1<<prog_list.size()==v.used[0]+1)continue;
			for(;;){
				i=R()%prog_list.size();
				if(tst(v.used,i) || i==ss)continue;
				break;
			}
			setv(v.used,i);
			np=prog_list[i];
			func_type.resize(prog_list[i]->inputsize);
		}else{
//			ffl=1;
//			bool fl=0;for(int i=0;i<faa.a.size();++i)if(v.used2[i>>5]>>(i&31)&1)fl=1;if(!fl)continue;
//			tie(nnw,np,func_type)=faa.ask(v.used2);
		}
		V nres;V edge(np->inputsize);
		function<void(int)>dfs=[&](int d){
			if(d==np->inputsize){
				auto ns=v;
				auto ret=ns.pr.exec(*this,np,v.pr.Res,nres,v.svd,ns.svd,edge,v.pr.Res.size());
				int datanum=v.pr.Res[0].size(),tot=0,mx=0;
				if(ret==Fa)return;
				if(np->name==v.pr.name){
					int x=get<1>(ret);
					if(x>=114514)return;
//					ns.W*=2*poww(0.8,x*1.0/datanum);
					ns.W*=2;
				}else{
					for(int i=0;i<datanum;++i){
						int x=dist(out[i],nres[i]);
						for(int j=0;j<v.pr.inputsize;++j)x=min(x,dist(v.pr.Res[j][i],nres[i]));
						tot+=x;mx=max(mx,x);
					}
					if(mx>1)return;
					ns.W*=poww(0.8,tot*1.0/datanum);
				}
				ns.pr.Res.push_back(nres);
				ns.pr.edge.push_back(edge);
				ns.pr.vec.push_back(np);
//				ns.W+=get<2>(ret);
//				if(ffl)ns.W+=nnw*w6;
//				ns.W*=w3;
//				ns.W*=pow(0.9,1.0/np->rank);//need change
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
			for(int k=0;k<v.pr.Res.size();++k){
				if(func_type[d]==0?"I-"+v.pr.vec[k]->outputtype==np->vec[d]->name:func_type[d]==v.pr.vec[k])
					edge[d]=k,dfs(d+1);
			}
		};
		dfs(0);		
	}
}
