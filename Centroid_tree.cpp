#include <bits/stdc++.h>
using namespace std;

vector<int> graph[200003];
vector<int> odl[200003];
bool del[200003];
int lvl[200003];
int siz[200003];
int par[200003];

int find_centr(int v, int p, int n){
	siz[v]=1;
	int ans=0;
	for (auto u : graph[v]){
		if (u==p || del[u])continue;
		ans=max(ans,find_centr(u,v,n));
		siz[v]+=siz[u];
	}
	if (ans)return ans;
	if (2*siz[v]>=n)return v;
	return 0;
}

void centr(int v, int p, int dist){
	siz[v]=1;
	odl[v].push_back(dist);
	for (auto u : graph[v]){
		if (u==p || del[u])continue;
		centr(u,v,dist+1);
		siz[v]+=siz[u];
	}
}

void build(int v, int p){
	par[v]=p;
	lvl[v]=lvl[p]+1;
	del[v]=true;
	for (auto u : graph[v]){
		if (del[u])continue;
		int st=find_centr(u,0,siz[u]);
		centr(st,0,0);
		build(st,v);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n,v,u;
	cin >> n;
	for (int i = 1; i<n; i++){
		cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	lvl[0]=-1;
	int st=find_centr(1,0,n);
	centr(st,0,0);
	build(st,0);
	for (int i = 1; i<=n; i++){
		for (int j = i; j; j=par[j])cout << j << ' ';
		cout << '\n';
	}
}