#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int seed,n;
    cin >> seed;
    srand(seed);
    n=rand()%1000000+2;
    cout << n << '\n';
    for (int i = 1; i<=n; i++){
        cout << (char)('a'+(rand()%2));
    }
}