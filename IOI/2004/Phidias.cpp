// IOI 2004 - Phidias
// Leonardo Paes

// Let's solve the problem using dynamic programming. DP[i][j] = minimum empty area in a i*j rectangle. So, for each i and j, we
// just need to use the minimum between dividing i in two parts or j in two parts, for all possible bipartitions.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 610, inf = 0x3f3f3f3f;

int w, h, n, dp[maxn][maxn];

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    cin >> w >> h >> n;

    memset(dp, inf, sizeof dp);

    for(int i=0; i<n; i++){
        int a, b;
        cin >> a >> b;
        dp[a][b]=0;
    }

    for(int i=1; i<=w; i++){
        for(int j=1; j<=h; j++){
            if(dp[i][j]==inf)dp[i][j]=i*j;
            for(int aux=1; aux<=i/2; aux++){
                dp[i][j]=min(dp[i][j], dp[aux][j] + dp[i-aux][j]);
            }
            for(int aux=1; aux<=j/2; aux++){
                dp[i][j]=min(dp[i][j], dp[i][aux] + dp[i][j-aux]);
            }
        }
    }

    cout << dp[w][h] << endl;

    return 0;
}
