// USACO Gold Dec 2014 - Guard Mark
// Leonardo Paes

#include <bits/stdc++.h>

using namespace std;

const int maxn = 22, inf = 0x3f3f3f3f;

int n, H, h[maxn], w[maxn], s[maxn], dp[1<<maxn], ans=-inf;

int solve (int mask){

    if(!mask)return inf;
    if(dp[mask]!=-1)return dp[mask];

    int tot=-inf;
    long long wmask=0;

    for(int i=0; i<n; i++){
        if(mask&(1<<i)){
            wmask+=w[i];
        }
    }

    for(int i=0; i<n; i++){
        if(mask&(1<<i)){
            int rest = wmask-w[i];
            if(rest<=s[i]){
                tot=max(tot, min(s[i]-rest, solve(mask^(1<<i))));
            }
        }
    }

    return dp[mask]=tot;
}

int main(){

    freopen("guard.in", "r", stdin);
	freopen("guard.out", "w", stdout);

    cin >> n >> H;

    for(int i=0; i<n; i++) cin >> h[i] >> w[i] >> s[i];

    memset(dp, -1, sizeof dp);

    for(int mask=0; mask<(1<<n); mask++){

        solve(mask);

        long long hmask=0;

        for(int i=0; i<n; i++){
            if(mask&(1<<i)){
                hmask+=h[i];
            }
        }

        if(hmask>=H){
            ans=max(ans, dp[mask]);
        }
    }

    if(ans==-inf){
        cout << "Mark is too tall\n";
    }
    else{
        cout << ans << "\n";
    }

    return 0;
}
