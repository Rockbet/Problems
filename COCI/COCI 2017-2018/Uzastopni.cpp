// COCI 2017 - Uzastopni
// Leonardo Paes

// The idea to solve this problem is: for each quantity of consecutive integers from 1 to 2*10^5(witch is sqrt(10^10)) we
// will guess the endpoint of the sum that is equal to n. Then we just have to print the answer if it exists in this quantity.

#include <bits/stdc++.h>

using namespace std;

long long sum(long long k){
    return k*(k+1LL)>>1LL;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

    long long n;

    cin >> n;

    for(int i=2; i<=min(n, 200000LL); i++){
        long long ini=1, meio, fim=n, ans=-1LL;

        while(ini<=fim){
            meio = (ini+fim)>>1LL;
            if((meio-i>=0LL) and (sum(meio)-sum(meio-i))>=n){
                fim=meio-1LL;
                ans=meio;
            }
            else{
                ini=meio+1LL;
            }
        }

        if((ans-i>=0LL) and (sum(ans)-sum(ans-i))==n){
            cout << ans-i+1LL << " " << ans << "\n";
        }
    }

    return 0;
}
