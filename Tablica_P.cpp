#include <bits/stdc++.h>
using namespace std;

string s;
int p[200003];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> s;
	int n=s.size(),len=0;
	for (int i = 1; i<n; i++){
		while(s[i]!=s[len]){
			if (!len && s[i]!=s[0]){
				len--;
				break;
			}
			len=p[len-1];
		}
		len++;
		p[i]=len;
	}
	for (int i = 0; i<n; i++){
		cout << p[i] << ' ';
	}
	cout << '\n';
}