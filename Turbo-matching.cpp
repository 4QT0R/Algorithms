#include <bits/stdc++.h>
using namespace std;

const int maxN=200003; 

vector<int> graph[maxN];
int vis[maxN];
int timer;
int match[maxN];

bool update(int v){
	vis[v]=timer;
	for (auto u : graph[v]){
		if (match[u]==-1){
			match[v]=u;
			match[u]=v;
			return true;
		}
	}
	for (auto u : graph[v]){
		if (vis[match[u]]!=timer && update(match[u])){
			match[v]=u;
			match[u]=v;
			return true;
		}
	}
	return false;
}

void init(int &n, int &m){
	cin >> n >> m;
	int a,b;
	for (int i = 1; i<=m; i++){
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
}

void turbo_matching(int n){
	while(true){
		timer++;
		bool any=false;
		for (int i = 1; i<=n; i++){
			if (match[i]==-1 && update(match[i])){
				any=true;
			}
		}
		if (!any)return;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n,m;
	init(n,m);
	turbo_matching(n);
}