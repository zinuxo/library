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
		auto iter=unique(ve.begin(),ve.end());if(iter!=ve.end())return;
		auto ite=mp.find(ve);
		if(ite==mp.end()){
			int id=++scnt;
			st[id]=ns;st[id].id=id;
			mp[ve]=id;
			it[id]=q.push({st[id].W,id});
int tot=0;
for(int i=0;i<out.size();++i)if(tst(ns.svd,i))++tot;
cout<<id<<' '<<tot<<endl;
auto tmp=ns;tmp.pr.output();
if(tot==out.size())exit(0);
		}
	};
	state u;
	u.isre=0;
	u.W=100;u.pr=start;u.id=u.cost=0;
	u.used.resize(prog_list.size()+31>>5);
	u.svd.resize(out.size()+31>>5);
	upd(u);
	for(;;){
		int id=q.top().second;q.pop();
		state&v=st[id];
if(id==3)
++id,--id;
static int lst;
if(scnt>lst+1e3){
	lst=scnt,fprintf(stderr,"%d %.6f\n",scnt,v.W);
	st[scnt/1000*1000].pr.output();
}
bool pb=1;
for(int i=0;i<out.size();++i)if(!tst(v.svd,i) && t[start.Res[0][i]].c==E && t[start.Res[1][i]].c==E)
	pb=0;
if(pb)
++id,--id;
if(v.pr.vec.size()==3 && v.pr.vec[2]->name=="Getb")
++id,--id;
if(v.pr.vec.size()==4 && v.pr.vec[2]->name=="Getb" && v.pr.vec[3]->isre
	 && v.pr.vec[3]->rev==P{1,2})
++id,--id;
if(v.pr.vec.size()==4 && v.pr.vec[2]->name=="Getb" && v.pr.vec[3]->isre
	 && v.pr.vec[3]->rev==P{1,2} && v.pr.vec[3]->rel==vector<P>{P{1,0},P{1,2}})
++id,--id;
		v.W*=0.95;
		it[id]=q.push({v.W,id});
		int i;
		vector<prog*>func_type;
		prog*np;
		bool ffl;double nnw;
		if(v.isre){
			for(int j=0;j<v.pr.vec.size();++j)if(!v.pr.vec[j]->isre){
				auto work=[&](state&ns){
					V nres;
					auto ret=ns.pr.exec(*this,ns.pr.vec.back(),v.pr.Res,nres,v.svd,ns.svd,{},v.pr.Res.size());
					if(ret==Fa)return;
					int wa=-1-get<0>(ret),datanum=out.size();
					if(wa==0)ns.W*=get<2>(ret),ns.isre=0;else{
						return;
//						if(ns.pr.vec.back()->rel.size()==2)ns.W*=pow(0.5,wa*1.0/datanum);
//						if(ns.pr.vec.back()->rel.size()==4)return;
					}
					ns.cost=v.cost+get<1>(ret);//need change
					ns.pr.Res.back()=nres;
					upd(ns);
				};
				for(int k=0;k<v.pr.vec.size();++k)if(k>j && !v.pr.vec[k]->isre){
if(j==0 && k==1 && v.pr.vec[2]->name=="Geta" && v.pr.vec[3]->rev==P{1,2})
++j,--j;
					auto ns=v;
					ns.pr.vec.back()=new prog;*ns.pr.vec.back()=*v.pr.vec.back();
					ns.pr.vec.back()->rel.push_back({1,j});
					ns.pr.vec.back()->rel.push_back({1,k});
					work(ns);
				}
				type*tp=name_type[v.pr.vec[j]->outputtype];
if(tp->name=="L")
++id,--id;
				for(int k=0;k<tp->atom.size();++k){
if(j==0 && k==0 && id==66)
++j,--j;
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
			ns.W*=1.05;
			ns.pr.Res.push_back(nres);
			ns.pr.edge.push_back({});
			ns.pr.vec.push_back(np);
			ns.cost=v.cost+get<1>(ret);
			upd(ns);
		};
		int ss=prog_list.size()-1;
		if(!tst(v.used,ss) && ra()<0.3){
			for(int i=0;i<v.pr.vec.size();++i)if(check_re(i))
				pbre(i);
			setv(v.used,ss);
			continue;
		}
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
