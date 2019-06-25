// The idea is to use digit dp to solve the problem. Suppose that we have calc(x)
// that returns the answer to the problem from 0 to x. So, our answer is:
// calc(B) - calc(A-1). To know the answer from 0 to x, we have a dp[pos][sum][flag]
// pos is the position we are in the number right now, sum is what we have left from our original sum
// and flag is a bool: if flag==0 our number is less than x, otherwise, we dont know yet.
// To calculate the solve function, the above code may explain ( it is just a simulation, a smarter brute force):

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const int maxn = 16, maxs = 136;

ll a, b, dp[maxn][maxs][2];

int s;

vector<ll> digits;

ll solve(int pos, int sum, bool flag){
    if(pos==0){
        if(sum<0 or sum>9) return 0;
        if(flag==0) return 1;
        if(sum<=digits[pos]) return 1;
        return 0;
    }
    if(dp[pos][sum][flag]!=-1) return dp[pos][sum][flag];
    if(flag==1){
        ll ans = 0;
        for(int i=0; i<digits[pos]; i++) ans += solve(pos-1, sum-i, 0);
        ans += solve(pos-1, sum-digits[pos], 1);
        return dp[pos][sum][flag] = ans;
    }
    if(flag==0){
        ll ans = 0;
        for(int i=0; i<=9; i++) ans += solve(pos-1, sum-i, 0);
        return dp[pos][sum][flag] = ans;
    }
}

ll calc(ll num, int sum){
    if(num==0) return 0;
    digits.clear();
    while(num!=0){
        digits.push_back(num%10);
        num/=10;
    }
    memset(dp, -1, sizeof dp);
    return solve(digits.size()-1, sum, 1);
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    cin >> a >> b >> s;

    ll ansb = calc(b, s);
    ll ansa = calc(a-1, s);

    cout << ansb - ansa << "\n";

    ll ini=a, fim=b, meio, ans2;

    while(ini<=fim){
        meio=(ini+fim)>>1;
        if(calc(meio, s)-ansa>=1){
            ans2=meio;
            fim=meio-1;
        }
        else ini=meio+1;
    }

    cout << ans2 << "\n";
}
