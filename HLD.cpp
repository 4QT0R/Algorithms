#include <bits/stdc++.h>
using namespace std;

struct edge{
	int to;
};

const int base=1<<19;
int tree[2*base];
vector<edge> graph[200003];
vector<int> paths[200003];
pair<int,int> ind[200003];
int siz[200003];
int odl[200003];
int par[200003];
int wys[200003];
int licz=1,ord=0;

int comp(int a, int b){
	return odl[a]<odl[b]?a:b;
}

void prep(int v, int p){
	siz[v]=1;
	tree[++ord+base]=v;
	wys[v]=ord;
	for (auto u : graph[v]){
		if (u.to==p)continue;
		prep(u.to,v);
		tree[++ord+base]=v;
		par[u.to]=v;
		odl[u.to]=odl[v]+1;
		siz[v]+=siz[u.to];
	}
}

int start(int v){
	if (v>=base)return tree[v];
	tree[v]=comp(start(2*v),start(2*v+1));
	return tree[v];
}

void build(int v, int p, int iter){
	for (auto u : graph[v]){
		if (u.to==p)continue;
		if (2*siz[u.to]>=siz[v])build(u.to,v,iter);
		else build(u.to,v,++licz);
	}
	ind[v]={iter,paths[iter].size()};
	paths[iter].push_back(v);
}

int lca(int a, int b){
	a=wys[a];
	b=wys[b];
	if (a>b)swap(a,b);
	a+=base-1;
	b+=base+1;
	int ans=0;
	while(a/2!=b/2){
		if (!(a&1))ans=comp(ans,tree[a+1]);
		if (b&1)ans=comp(ans,tree[b-1]);
		a>>=1;
		b>>=1;
	}
	return ans;
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n,v,u;
	cin >> n;
	odl[0]=1e9;
	for (int i = 1; i<n; i++){
		cin >> v >> u;
		graph[v].push_back({u});
		graph[u].push_back({v});
	}
	prep(1,0);
	start(1);
	build(1,0,1);
	for (int i = 1; i<=licz; i++){
		for (auto u : paths[i])cout << u << ' ';
		cout << '\n';
	}
}