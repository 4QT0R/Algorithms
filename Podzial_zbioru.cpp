#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
using namespace __gnu_pbds; 
using namespace std;
#define ll long long

ll lider[200003];
ll siz[200003];
ll sm[200003];
ll mn[200003];
ll mx[200003];
ordered_set med[200003];

void init(){
	for (ll i = 1; i<=200000; i++){
		lider[i]=sm[i]=mn[i]=mx[i]=i;
		med[i].insert(i);
		siz[i]=1;
	}
}

ll Find(ll v){
	if (lider[v]==v)return v;
	lider[v]=Find(lider[v]);
	return lider[v];
}

void Union(int a, int b){
	a=Find(a);
	b=Find(b);
	if (a==b)return;
	if (siz[a]<siz[b])swap(a,b);
	lider[b]=a;
	siz[a]+=siz[b];
	sm[a]+=sm[b];
	mn[a]=min(mn[a],mn[b]);
	mx[a]=max(mx[a],mx[b]);
	for (auto u : med[b])med[a].insert(u);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n,m,a,b;
	cin >> n >> m;
	string slowo;
	init();
	for (ll i = 1; i<m; i++){
		cin >> slowo;
		if (slowo[0]=='f'){
			cin >> a;
			a=Find(a);
			cout << sm[a] << ' ' << mn[a] << ' ' << mx[a] << ' ' << *(med[a].find_by_order(siz[a]/2)) << '\n';
		}
		else{
			cin >> a >> b;
			Union(a,b);
		}
	}
}