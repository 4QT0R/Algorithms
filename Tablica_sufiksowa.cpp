#include <bits/stdc++.h>
using namespace std;
#define pipii pair<int,pair<int,int>>

string slowo;
int KMR[500002][22];
int SA[500002];
int LCP[500002];
int lg[500002];
int pow2[24];
int RANK[500002];
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
        KMR[i][0]=slowo[i]-'a';
    }
    for (int i = 1; i<=lg[n]+1; i++){
        for (int j = 0; j<n; j++){
            if (j+pow>=n){
                tab[j]=make_pair(j,make_pair(KMR[j][i-1],-1));
            }
            else{
                tab[j]=make_pair(j,make_pair(KMR[j][i-1],KMR[j+pow][i-1]));
            }
        }
        sort(tab,tab+n,sorting);
        iter=0;
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
        if (2*pw<i){
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
    int fin=lg[n]+1;
    for (int i = 0; i<n; i++){
        SA[KMR[i][fin]]=i;
    }
    for (int i = 0; i<n; i++){
        cout << SA[i] << ' ';
        for (int j = SA[i]; j<n; j++){
            cout << slowo[j];
        }
        cout << '\n';
    }
    for (int i = 0; i<n; i++){
        RANK[i]=KMR[i][fin];
    }
    int j,k=0;
    for (int i = 0; i<n; i++){
        if (RANK[i]==n-1){
            k=0;
            continue;
        }
        j=SA[RANK[i]+1];
        while(i+k<n && j+k<n && slowo[i+k]==slowo[j+k]){
            k++;
        }
        LCP[RANK[i]+1]=k;
        if (k){
            k--;
        }
    }
    for (int i = 0; i<n; i++){
        cout << LCP[i] << ' ';
    }
    cout << '\n';
}