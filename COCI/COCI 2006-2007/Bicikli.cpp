// We are using Dynamic Programming to solve this problem. The ideia is that: dp[i] is the number of different paths from 2 to i. 
// So, the base case is: dp[2]=1. Then, for each i: dp[i] = sum of all j's, j having an edge pointing to i and there is at least 1 path
// from 1 to j and from j to 2. We have to take care about the answer, cause we will recieve WA if we don't print the leading zeros,
// if necessary, after taking all the mod 1e9. Ex: Sample Input 3, the answer is 073741824, and printing 73741824 will give you WA.

#include <bits/stdc++.h>

using namespace std;

#define gc getchar

const int maxn = 1e4+10, mod = 1e9;

int n, m, dp[maxn], cnt=0;

vector<int> grafo[2][maxn];

bool zeros=false, path[2][maxn];

inline void dfs(int start, int u){
    path[start][u]=1;
    for(int i=0; i<grafo[start][u].size(); i++){
        int v = grafo[start][u][i];
        if(!path[start][v]){
            dfs(start, v);
        }
    }
}

inline int solve(int u){
    if(cnt>n)return -1;
    if(dp[u]!=-1)return dp[u];
    cnt++;
    int tot = 0;
    for(int i=0; i<grafo[0][u].size(); i++){
        int v = grafo[0][u][i];
        if(path[0][v] and path[1][v]){
            tot += solve(v);
            if(tot>=1000000000){
                zeros=true;
                tot%=mod;
            }
        }
    }
    return dp[u]=tot;
}

inline int scan(void){
	int n = 0, x = gc(), s =1;
	for (;x<'0'||x>'9';x=gc()) if(x=='-') s=-1;
	for (;x>='0'&&x<='9';x=gc()) n = (n<<3) + (n<<1) + x-'0';
	return n;
}

int main(){

    n = scan(), m = scan();

    for(int i=1; i<=m; i++){
        int u, v;

        u = scan(), v = scan();

        grafo[0][u].push_back(v);
        grafo[1][v].push_back(u);
    }

    dfs(0, 1);
    dfs(1, 2);

    memset(dp, -1, sizeof dp);

    dp[2]=1;

    solve(1);

    if(cnt>n)printf("inf\n");

    else{
        if(zeros){
            int ans[9]={0};
            int i=0;
            while(dp[1]!=0){
                ans[i++]=dp[1]%10;
                dp[1]/=10;
            }
            reverse(ans, ans+9);
            for(int i=0; i<9; i++){
                printf("%d", ans[i]);
            }
            printf("\n");
        }
        else{
            printf("%d\n", dp[1]);
        }
    }

    return 0;
}
