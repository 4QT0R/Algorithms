#include <bits/stdc++.h>
using namespace std;

int wej[200003];
int med[200003];

vector<int> wavelet_tree[600002];
// vector<int> pth[200002];
// int pivot[600002];

void build(int v, int l, int p){
	if (wavelet_tree[v].size()<=1 || l==p)return;
	int md=(l+p+1)/2;
	// pivot[v]=med[md];
	for (auto t : wavelet_tree[v]){
		if (wej[t]<med[md]){
			wavelet_tree[2*v].push_back(t);
			// pth[t].push_back(2*v);
		}
		else{
			wavelet_tree[2*v+1].push_back(t);
			// pth[t].push_back(2*v+1);
		}
	}
	build(2*v,l,md-1);
	build(2*v+1,md,p);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	for (int i = 1; i<=n; i++){
		cin >> wej[i];
		med[i]=wej[i];
		wavelet_tree[1].push_back(i);
		// pth[i].push_back(1);
	}
	sort(med+1,med+1+n);
	build(1,1,n);
	// for (int i = 1; i<=n; i++){
	// 	cout << i << '\n';
	// 	for (auto u : pth[i])cout << u << ' ';
	// 	cout << '\n';
	// }
}