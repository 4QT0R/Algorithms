// Patrz tu:
// https://codeforces.com/blog/entry/91608

// #include <bits/stdc++.h>
// using namespace std;

// struct edge{
// 	int from;
// 	int to;
// 	int time;
// };

// vector<edge> edges;

// vector<int> lider;
// vector<int> siz;

// void init(int &n, int &m){
// 	cin >> n >> m;
// 	edges.resize(m);
// 	lider.resize(n);
// 	iota(lider.begin(),lider.end(),0);
// 	siz.resize(n,1);
// 	for (int i = 0; i<m; i++){
// 		cin >> edges[i].from >> edges[i].to;
// 		edges[i].time=i;
// 	}
// }

// int Find(int v){
// 	if (lider[v]==v)return v;
// 	return lider[v]=Find(lider[v]);
// }

// void Union(int a, int b){
// 	a=Find(a);
// 	b=Find(b);
// 	if (a==b)return;
// 	if (siz[a]<siz[b])swap(a,b);
// 	lider[b]=a;
// 	siz[a]+=siz[b];
// }

// void scc(vector<edge> ed){

// }

// void rec(int l, int p, vector<edge> ed, int lvl){
// 	int md = (l+p)/2;
// 	vector<edge> lft, rght;


// }

// int main(){
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);

// 	int n,m;
// 	init(n,m);
// }