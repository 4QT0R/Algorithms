#include <bits/stdc++.h>
using namespace std;

string slowo;
int KMR[500002][20];
int lg[500002];
vector<int> buckets[500002];
vector<pair<int,int>> sup;
vector<int> product;
void kmr(int n){
    int pow=1,iter;
    for (int i = 0; i<n; i++){
        KMR[i][0]=slowo[i]-'a'+1;
    }
    for (int i = 1; i<=lg[n]; i++){
        for (int j = 0; j<n; j++){
            if (j+pow>=n){
                buckets[n+1].push_back(j);
            }
            else{
                buckets[KMR[j+pow][i-1]].push_back(j);
            }
        }
        iter=1;
        for (int j = 1; j<=n+1; j++){
            if (!buckets[j].empty()){
                for (auto v : buckets[j]){
                    sup.push_back({v,iter});
                }
                iter++;
                buckets[j].clear();
            }
        }
        // for (int j = 0; j<n; j++){
        //     buckets[KMR[sup[j].first][i-1]].
        // }
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
    cin >> slowo;
    kmr(n);
    for (int i = 0; i<=lg[n]; i++){
        for (int j = 0; j<n; j++){
            cout << KMR[j][i] << '\n';
        }
        cout << '\n';
    }
}