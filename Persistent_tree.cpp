#include <bits/stdc++.h>
using namespace std;

struct node{
    int left_son;
    int right_son;
    int value;
};

const int base=1<<17;
int new_node=2*base-1;
int timer=0;
node forest[4000000];
int roots[1000004];
int wej[1000004];

int start(int v){
    if (v>=base){
        forest[v].value=wej[v-base];
        return forest[v].value;
    }
    forest[v].left_son=2*v;
    forest[v].right_son=2*v+1;
    forest[v].value=start(2*v)+start(2*v+1);
    return forest[v].value;
}

void update(int from, int pos, int val){
    int old=roots[from];
    roots[++timer]=++new_node;
    int l=0,r=base-1,md;
    while(l<r){
        md=(l+r)/2;
        forest[new_node].value=forest[old].value+val;
        if (pos<=md){
            forest[new_node].right_son=forest[old].right_son;
            forest[new_node].left_son=new_node+1;
            old=forest[old].left_son;
            r=md;
        }
        else{
            forest[new_node].left_son=forest[old].left_son;
            forest[new_node].right_son=new_node+1;
            old=forest[old].right_son;
            l=md+1;
        }
        new_node++;
    }
    forest[new_node].value=forest[old].value+val;
}

int querry(int v, int left, int right, int l, int r){
    int md=(l+r)/2;
    if (r<left || right<l){
        return 0;
    }
    else if (l==left && r==right){
        return forest[v].value;
    }
    else{
        if (right>md && left<=md){
            return querry(forest[v].left_son,left,md,l,md)+querry(forest[v].right_son,md+1,right,md+1,r);
        }
        else if (right<=md){
            return querry(forest[v].left_son,left,right,l,md);
        }
        else{
            return querry(forest[v].right_son,left,right,md+1,r);
        }
    }

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,q,a,b,c,d;
    cin >> n;
    for (int i = 1; i<=n; i++){
        cin >> wej[i];
    }
    roots[0]=1;
    start(1);
    cin >> q;
    for (int i = 1; i<=q; i++){
        cin >> a >> b >> c >> d;
        if (a==1){
            update(b,c,d);
        }
        else{
            cout << querry(roots[b],c,d,0,base-1) << '\n';
        }
    }
}