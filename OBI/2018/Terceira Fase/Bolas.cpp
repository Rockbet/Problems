// OBI 2018 - Bolas
// Leonardo Paes

#include <bits/stdc++.h>

using namespace std;

int freq[15];

bool ans = true;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

    for(int i=1; i<=8; i++){
        int x;
        cin >> x;
        freq[x]++;
        if(freq[x]>4) ans = false;
    }

    cout << (ans ? "S\n" : "N\n");
}
