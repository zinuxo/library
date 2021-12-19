#include"type.hpp"
/*
input
type-checking
*/
inline prog*newRe(P a,vector<P>ve){
	static int count;
	prog*p=new prog;
	p->name="Re"+to_string(count++);
	p->isre=1;p->rev=a;p->rel=ve;
	assert(ve.size()%2==0);
	name_prog[p->name]=p;
	return p;
}
//inline void prog::input(bool tp=0,string sss=""){
inline void prog::input(bool tp,string sss){
/*
Def And 2
	I-Bi ;
	I-Bi ;
	Re '0' If v0 = '0' ;
	Re v1 ;
End
*/
	string s;
	if(!tp){
		cin>>s;//s=="Def" this time
		cin>>name;
	}else name=sss;
	name_prog[name]=this;
	cin>>inputsize>>rank>>outputtype;
	for(;;){
		cin>>s;
		if(s=="End")break;
		auto in=[&](){
			char c[99];int x;
			cin>>c;
			if(c[0]=='v'){
				sscanf(c+1,"%d",&x);
				return P{1,x};
			}else return P{0,name_atomid[string(c+1,c+strlen(c)-1)]};
		};
		if(s=="Re"){
			edge.push_back({});
			auto a=in();
			cin>>s;
			if(s=="If"){
				vector<P>ve;
				for(;;){
					if(s!="If")cin>>s;
					if(s==";")break;
					ve.push_back(in());
					cin>>s;
					ve.push_back(in());
				}
				vec.push_back(newRe(a,ve));
			}else vec.push_back(newRe(a,{}));
			continue;
		}
		auto p=name_prog[s];
		vec.push_back(p);
		edge.push_back(V(p->inputsize));
		for(int&x:edge.back())x=in().second;
		cin>>s;
	}
}
inline void prog::inner_input(string st){
	stringstream cin(st);
	string s;
	cin>>s;//s=="Def" this time
	cin>>name;
	name_prog[name]=this;
	cin>>inputsize>>rank>>outputtype;
	for(;;){
		cin>>s;
		if(s=="End")break;
		auto in=[&](){
			char c[99];int x;
			cin>>c;
			if(c[0]=='v'){
				sscanf(c+1,"%d",&x);
				return P{1,x};
			}else return P{0,name_atomid[string(c+1,c+strlen(c)-1)]};
		};
		if(s=="Re"){
			edge.push_back({});
			auto a=in();
			cin>>s;
			if(s=="If"){
				vector<P>ve;
				for(;;){
					if(s!="If")cin>>s;
					if(s==";")break;
					ve.push_back(in());
					cin>>s;
					ve.push_back(in());
				}
				vec.push_back(newRe(a,ve));
			}else vec.push_back(newRe(a,{}));
			continue;
		}
		auto p=name_prog[s];
		vec.push_back(p);
		edge.push_back(V(p->inputsize));
		for(int&x:edge.back())x=in().second;
		cin>>s;
	}
	name_prog.erase(name_prog.find(name));
}
inline P prog::exec(V input){
if(name=="T-Tree1")
input=input;
	if(name=="I")return P{1,1};//useless。
	if(input.size()!=inputsize)return F;
	int i,x,y,cost=0;
	V res(vec.size());
	for(i=0;i<vec.size();++i){
//cerr<<i<<' '<<name<<endl;
//if(i==15 && name=="T-Tree1")
//++i,--i;
		if(i<inputsize){
			res[i]=input[i];
			if(vec[i]->name=="I")continue;
			string s=fixstr(vec[i]->name);
			auto z=name_type[s]->check->exec({input[i]});
			if(z==F)return F;
			cost+=z.second;
		}else if(vec[i]->name=="L"){
			x=res[edge[i][0]];
			if(t[x].c!=E && t[x].c!=-1)return F;
			cost+=1;
			if(!t[x].l)res[i]=x;
				else res[i]=t[x].l;
		}else if(vec[i]->name=="R"){
			x=res[edge[i][0]];
			if(t[x].c!=E && t[x].c!=-1)return F;
			cost+=1;
			if(!t[x].r)res[i]=x;
				else res[i]=t[x].r;
		}else if(vec[i]->name=="C"){
			x=res[edge[i][0]];y=res[edge[i][1]];
			cost+=1;
			res[i]=++tcnt;
			t[res[i]]=node{-1,x,y};
		}else if(vec[i]->isre){
			cost+=1;
			if(vec[i]->rev.first==0){
				res[i]=++tcnt;
				t[res[i]]=node{vec[i]->rev.second,0,0};
			}else res[i]=res[vec[i]->rev.second];
			auto getval=[&](P u){
				return u.first?t[res[u.second]].c:u.second;
			};
			bool fl=1;
			for(int j=0;j<vec[i]->rel.size();j+=2){
				int a=getval(vec[i]->rel[j]),b=getval(vec[i]->rel[j+1]);
				++cost;
//				if(a<0 && b<0)return Fa;
				if(a<0 && b<0){fl=0;break;}//just ban compare between two tree. need change later.
				if(a!=b){fl=0;break;}
			}
			if(fl)return {res[i],cost};
		}else{
			V newinput(edge[i].size());
			for(int j=0;j<edge[i].size();++j)newinput[j]=res[edge[i][j]];
			int f1,f2;
			auto z=vec[i]->exec(newinput);
//			if(z==F)return F;
			tie(f1,f2)=z;
			res[i]=f1;cost+=f2;
		}
	}
	return F;
}
inline void prog::output(){
	cout<<"Def "<<name<<' '<<inputsize<<' '<<rank<<' '<<outputtype<<'\n';
	for(int i=0;i<vec.size();++i){
		cout<<'	';
		if(vec[i]->isre){
			auto out=[&](P u){
				if(u.first==1)cout<<'v'<<u.second;else{
					type*a;int b;tie(a,b)=atomid_val[u.second];
					cout<<'\"'<<a->atom[b]<<'\"';
				}
			};
			cout<<"Re ";
			out(vec[i]->rev);
			if(!vec[i]->rel.empty()){
				cout<<" If ";
				assert(vec[i]->rel.size()%2==0);
				for(int j=0;j<vec[i]->rel.size();j+=2){
					out(vec[i]->rel[j]);
					cout<<" = ";
					out(vec[i]->rel[j+1]);cout<<' ';
					if(j+2<vec[i]->rel.size())cout<<"&& ";
				}
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
