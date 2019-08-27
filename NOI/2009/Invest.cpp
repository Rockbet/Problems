// Singapore NOI 2009 - Invest
// Leonardo Paes

// To solve this problem, let's use Dynamic Programming. Let DP[obj][id] be the best profit if we start from the id-th month buying
// the product obj. So, when we call solve(obj, id), we know the cost from id to id+14, using the product obj, as the problem tell us.
// From id+15 to m, we have to choose the best option between: Continue using product obj or changing to the product obj', obj'!=obj.
// Notice that the "profit" of a product is 2520/cost[product][month] * final_cost[product], just by using the rule of three.
// Our final answer is the maximum profit starting in month 1 and product i, 1 <= i <= 5.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

int m, cost[6][maxn], price[6];

long long dp[6][maxn];

long long solve(int obj, int id){
    if(id>m) return 0;
    if(dp[obj][id]!=-1) return dp[obj][id];

    long long tot = 0;

    for(int i=id; i<min(id+15, m+1); i++){
        tot += 2520LL/cost[obj][i]*price[obj];
    }

    long long sum = 0, tot2 = 0;

    for(int i=id+15; i<=m; i++){
        for(int j=1; j<=5; j++){
            if(obj!=j) tot2 = max(tot2, solve(j, i) + sum);
        }
        sum += 2520LL/cost[obj][i]*price[obj];
        tot2 = max(tot2, solve(obj, i+1) + sum);
    }

    return dp[obj][id] = tot + tot2;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    cin >> m;

    for(int i=1; i<=m; i++){
        for(int j=1; j<=5; j++){
            cin >> cost[j][i];
        }
    }

    for(int i=1; i<=5;i++){
        cin >> price[i];
    }

    long long ans=0;

    memset(dp, -1, sizeof dp);

    for(int i=1; i<=5; i++){
        ans=max(ans, solve(i, 1));
    }

    cout << ans << "\n";

    return 0;
}
