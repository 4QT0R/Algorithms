#include <bits/stdc++.h>
using namespace std;

string slowo="#";
int palindrom[1000005];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,ind,dl,l,p;
    char zn;
    cin >> n;
    for (int i = 1; i<=n; i++){
        cin >> zn;
        slowo+=zn;
        slowo+='#';
    }
    ind=0;
    dl=0;
    for (int i = 0; i<slowo.size(); i++){
        palindrom[i]=max(min(palindrom[2*ind-i],dl-(i-ind)),0);
        while(i-palindrom[i]>=0 && palindrom[i]+i<slowo.size() && slowo[i-palindrom[i]]==slowo[palindrom[i]+i]){
            palindrom[i]++;
        }
        if (i+palindrom[i]>ind+dl){
            ind=i;
            dl=palindrom[i];
        }
    }
    cout << slowo << '\n';
    for (int i = 0; i<slowo.size(); i++){
        cout << (palindrom[i]-1)/2 << ' ';
        for (int j = i-palindrom[i]+2; j<i+palindrom[i]-1; j+=2){
            cout << slowo[j];
        }
        cout << '\n';
    }
    cout << '\n';
}