// The idea is to use digit dp to solve the problem. Suppose that we have calc(x)
// that returns the answer to the problem from 0 to x. So, our answer is:
// calc(B) - calc(A-1). To know the answer from 0 to x, we have to try for all digits
// from 0 to 9 all the possible intervals (l, r) filled fully with this digit.
// To calculate the answer for the interval (l, r) and digit i we just have:
// (r-l+1)^2*i*(number of numbers <=B that has such interval l->r filled with i),
// which is calculated as a dp[maxn][2].
// The dp is the position we are now and a flag, telling if we are smaller then B or not
// flag == 1 means we are higher than B and flag==0 means we are smaller than B.
// to understand the dp (solve function) the best option is reading it carefully :D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 20;

ll A, B, dp[maxn][2];
ll l, r, n, digit;
vector<ll>num;

ll solve(int pos, int flag){
    if(dp[pos][flag]!=-1) return dp[pos][flag];
    if(pos==n) return dp[pos][flag]=1;
    if(flag){
        ll ans = 0;

        if(l<=pos and pos<=r){
            if(digit<=num[pos]) ans += solve(pos+1, (digit==num[pos]));
        }
        else{
            for(int i=0; i<=num[pos]; i++){
                if(pos==l-1 and i==digit)continue;
                if(pos==r+1 and i==digit)continue;
                ans += solve(pos+1, (i==num[pos]));
            }
        }

        return dp[pos][flag]=ans;
    }
    else{
        ll ans = 0;

        if(l<=pos and pos<=r){
            ans += solve(pos+1, 0);
        }
        else{
            for(int i=0; i<10; i++){
                if(pos==l-1 and i==digit)continue;
                if(pos==r+1 and i==digit)continue;
                ans += solve(pos+1, 0);
            }
        }
        return dp[pos][flag]=ans;
    }
}

ll calc (ll now){

    if(now==0)return 0;

    num.clear();

    while(now>0){
        num.push_back(now%10);
        now/=10;
    }

    reverse(num.begin(), num.end());

    n = num.size();

    ll ans = 0;

    for(digit=0; digit<10; digit++){
        for(l=0; l<n; l++){
            for(r=l; r<n; r++){
                memset(dp, -1, sizeof dp);
                ans += (r-l+1)*(r-l+1)*digit*solve(0, 1);
            }
        }
    }

    return ans;
}

int main(){

    cin >> A >> B;

    cout << calc(B) - calc(A-1) << endl;

    return 0;
}
