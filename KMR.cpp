#include <bits/stdc++.h>
using namespace std;
#define pipii pair<int,pair<int,int>>

string slowo;
int KMR[500002][20];
int lg[500002];
int pow2[24];
pipii tab[500002];

bool sorting(pipii a, pipii b){
    if (a.second.first==b.second.first){
        return a.second.second<b.second.second;
    }
    return a.second.first<b.second.first;
}

void kmr(int n){
    int pow=1,iter;
    for (int i = 0; i<n; i++){
        KMR[i][0]=slowo[i]-'a'+1;
    }
    for (int i = 1; i<=lg[n]; i++){
        for (int j = 0; j<n; j++){
            if (j+pow>=n){
                tab[j]=make_pair(j,make_pair(KMR[j][i-1],n+1));
            }
            else{
                tab[j]=make_pair(j,make_pair(KMR[j][i-1],KMR[j+pow][i-1]));
            }
        }
        sort(tab,tab+n-1,sorting);
        iter=1;
        KMR[tab[0].first][i]=iter;
        for (int j = 1; j<n; j++){
            if (tab[j-1].second!=tab[j].second){
                iter++;
            }
            KMR[tab[j].first][i]=iter;
        }
        pow<<=1;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,pw=1,temp=0;
    cin >> n;
    for (int i = 1; i<=n; i++){
        if (2*pw<=i){
            pw<<=1;
            temp++;
        }
        lg[i]=temp;
    }
    pow2[0]=1;
    for (int i = 1; i<=22; i++){
        pow2[i]=pow2[i-1]<<1;
    }
    cin >> slowo;
    kmr(n);
    for (int i = 0; i<=lg[n]; i++){
        for (int j = 0; j<n; j++){
            cout << KMR[j][i] << '\n';
        }
        cout << '\n';
    }
}