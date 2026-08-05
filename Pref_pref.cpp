#include <bits/stdc++.h>
using namespace std;

string slowo;
int PrefPref[2000005];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int ind,dl,l,p;
    string wej;
    cin >> wej >> slowo;
    slowo+='#';
    slowo+=wej;
    slowo+='$';
    ind=1;
    dl=1;
    for (int i = 1; i<=slowo.size(); i++){
        PrefPref[i]=max(min(PrefPref[i-ind],dl-(i-ind)),0);
        while(PrefPref[i]+i<slowo.size() && slowo[PrefPref[i]]==slowo[PrefPref[i]+i]){
            PrefPref[i]++;
        }
        if (i+PrefPref[i]>ind+dl){
            ind=i;
            dl=PrefPref[i];
        }
    }
    cout << slowo << '\n';
    for (int i = 0; i<slowo.size(); i++){
        cout << PrefPref[i] << ' ';
    }
    cout << '\n';
}