// COCI '07 Contest 3 #5 Cudak
// Leonardo Paes
//
// Same solution as this one: https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/COCI/official/2008/contest6_solutions

#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b){
    if(b==0) return a;
    else return gcd(b, a%b);
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int n;

    cin >> n;

    int gcd_acc, a, b;

    cin >> a >> b;

    gcd_acc = abs(a-b);

    for(int i=3; i<=n; i++){
        cin >> a;
        gcd_acc = gcd(gcd_acc, abs(a-b));
        b = a;
    }

    for(int i=2; i*i<=gcd_acc; i++){
        if(gcd_acc%i==0){
            if(i*i==gcd_acc) cout << i << " ";
            else cout << i << " " << gcd_acc/i << " ";
        }
    }

    cout << gcd_acc << endl;

    return 0;
}
