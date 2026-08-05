#include <bits/stdc++.h>
using namespace std;

struct node{
    int id;
    int fat;
    int l_son;
    int r_son;
    int val;
};

int wej[1000008];
node graph[1000008];
int T[1000008];

void build_Cartesian_tree(int *tab, int n){
    int st[n+1], k, top = -1;
    for (int i = 1; i<=n; i++){
        k = top;
        while (k >= 0 && tab[st[k]] > tab[i])
            k--;
        if (k != -1)
            T[i] = st[k];
        if (k < top)
            T[st[k + 1]] = i;
        st[++k] = i;
        top = k;
    }
    T[st[0]] = -1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i<=n; i++){
        cin >> wej[i];
    }
    build_Cartesian_tree(wej,n);
    for (int i = 1; i<=n; i++){
        cout << i << ' ' << T[i] << '\n';
    }
}