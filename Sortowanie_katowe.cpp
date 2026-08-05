#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct pll{
    ll x;
    ll y;
    ll ind;
};
vector<pll> otoczka;
pll punkty[500003];
ll n,ind;
pll center={(ll)1e9,(ll)1e9,0};

pll add(pll a, pll b){
    return (pll){a.x+b.x,a.y+b.y};
}

pll sub(pll a, pll b){
    return (pll){a.x-b.x,a.y-b.y};
}

ll dot_product(pll a, pll b){
    return a.x*b.x+a.y*b.y;
}

ll cross_product(pll a, pll b){
    return a.x*b.y-a.y*b.x;
}

bool sorting(pll a, pll b){
    if (a.x==center.x && a.y==center.y){
        return true;
    }
    if (b.x==center.x && b.y==center.y){
        return false;
    }
    ll temp=cross_product(sub(a,center),sub(b,center));
    if (temp==0){
        return a.x<b.x;
    }
    return temp<0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i<=n; i++){
        cin >> punkty[i].x >> punkty[i].y;
        punkty[i].ind=i;
        if (punkty[i].x<center.x){
            center=punkty[i];
            ind=i;
        }
        else if (punkty[i].x==center.x){
            if (punkty[i].y<center.y){
                center=punkty[i];
                ind=i;
            }
        }
    }
    sort(punkty+1,punkty+n+1,sorting);
    for (int i = 1; i<=n; i++){
        cout << punkty[i].x << ' ' << punkty[i].y << '\n';
    }
}