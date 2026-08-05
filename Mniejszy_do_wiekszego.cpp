#include <bits/stdc++.h>
using namespace std;

vector<int> graph[200003];

int val[200003];
set<int> *zbiory[200003];
int rozm[200003];

void dfs(int v, int p){
	for (auto u : graph[v]){
		if (u==p)continue;
		dfs(u,v);
	}
	int syn=0;
	for (auto u : graph[v]){
		if (rozm[u]>rozm[v]){
			rozm[v]=rozm[u];
			syn=u;
		}
	}
	if (syn==0)zbiory[v]=new set<int>;
	else zbiory[v]=zbiory[syn];
	for (auto u : graph[v]){
		if (u==syn || u==p)continue;
		zbiory[v]->merge(*zbiory[u]);
	}
	zbiory[v]->insert(val[v]);
	rozm[v]=(zbiory[v]->size());
}

void Init(int &n){
	cin >> n;
	for (int i = 1; i<=n; i++)cin >> val[i];
	int a,b;
	for (int i = 1; i<n; i++){
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs(1,0);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	Init(n);
}