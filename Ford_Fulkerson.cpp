#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct edge{
	int to;
	int ind;
};

const int maxN=5003;
const int maxM=30003;
const ll oo=1e18;

vector<edge> graph[maxN];
ll unused[4*maxM];
ll vis[maxN];
ll iter=1;

vector<int> path;

bool dfs(int v, int nd){
	vis[v]=iter;
	if (v==nd)return true;
	for (auto [u,x] : graph[v]){
		if (vis[u]==iter || !unused[x])continue;
		path.push_back(x);
		if (dfs(u,nd))return true;
		path.pop_back();
	}
	return false;
}

ll FordFulkerson(int s, int t){
	ll value=0;
	while(true){
		dfs(s,t);
		if (path.empty())break;
		ll diff=oo;
		for (auto x : path)diff=min(diff,unused[x]);
		for (auto x : path){
			unused[x]-=diff;
			unused[x^1]+=diff;
		}
		path.clear();
		value+=diff;
		iter++;
	}
	return value;
}

void init(int &n, int &m){
	cin >> n >> m;
	int u,v;
	ll c;
	for (int i = 1; i<=m; i++){
		cin >> u >> v >> c;
		graph[u].push_back({v,4*i});
		graph[v].push_back({u,4*i+1});
		unused[4*i]=c;
		unused[4*i+2]=c;
		graph[v].push_back({u,4*i+2});
		graph[u].push_back({v,4*i+3});
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n,m;
	init(n,m);
	cout << FordFulkerson(1,n) << '\n';
}