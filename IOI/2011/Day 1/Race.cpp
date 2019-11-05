// IOI - Race
// Leonardo Paes
//
// To solve the problem let us use Centroid Decomposition. For each centroid, let's suppose that the best path has this centroid
// in it. So, we just need to calculate the paths from this centroid to each of its subtrees and get the min paths with dist == k
// and less amount of edges possible. Remember that these paths must be from different subtrees!

#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second

const int maxn = 2e5+10, maxk = 1e6+10;

typedef pair<int,int> pii;

int n, k, l[maxn], aux;

bitset<maxn> mark; // Centroids visited

vector<pii> grafo[maxn];

int siz[maxn], dp[maxk], used[maxk], lastused, ans = 0x3f3f3f3f;

inline void dfs(const int &u, const int &p){
    siz[u] = 1;

    for(int i=0; i<grafo[u].size(); i++){
        int v = grafo[u][i].f;

        if(v==p or mark[v]) continue;

        dfs(v, u);

        siz[u] += siz[v];
    }
}

inline int centroid(const int &u, const int &p, const int &s){
    for(int i=0; i<grafo[u].size(); i++){
        int v = grafo[u][i].f;

        if(v==p or mark[v]) continue;

        if(siz[v] > s/2) return centroid(v, u, s);
    }

    return u;
}

vector<pii> updates;

inline void solve(const int &u, const int &p, const int &dist, const int &length){
    if(dist > k) return;

    ans = min(ans, dp[k-dist] + length);

    updates.push_back(make_pair(dist, length));

    used[lastused++] = dist;

    for(int i=0; i<grafo[u].size(); i++){
        int v = grafo[u][i].f, d = grafo[u][i].s;

        if(v==p or mark[v]) continue;

        solve(v, u, dist + d, length + 1);
    }

    if(p==aux){
        for(int j=0; j<updates.size(); j++){
            dp[updates[j].f] = min(dp[updates[j].f], updates[j].s);
        }
        updates.clear();
    }
}

inline void decompose(const int &u, const int &p){
    dfs(u, p);

    int c = centroid(u, p, siz[u]);

    aux = c;

    mark[c] = 1;

    dp[0] = 0;

    solve(c, -1, 0, 0);

    for(int i=0; i<lastused; i++){
        dp[used[i]] = 0x3f3f3f3f;
    }

    lastused = 0;

    for(int i=0; i<grafo[c].size(); i++){
        int v = grafo[c][i].f;

        if(!mark[v]) decompose(v, c);
    }
}

int best_path(int N, int K, int H[][2], int L[]){
    n = N, k = K;

    for(int i=0; i<(n-1); i++){
        l[i] = L[i];

        grafo[H[i][0]].push_back(make_pair(H[i][1], l[i]));
        grafo[H[i][1]].push_back(make_pair(H[i][0], l[i]));
    }

    for(int i=1; i<=k; i++) dp[i] = 0x3f3f3f3f;

    decompose(0, -1);

    return (ans == 0x3f3f3f3f ? -1 : ans);
}

/*
int main(){

    int mat[10][2] = {0, 1, 0, 2, 2, 3, 3, 4, 4, 5, 0, 6, 6, 7, 6, 8, 8, 9, 8, 10}, mat2[10] = {3, 4, 5, 4, 6, 3, 2, 5, 6, 7};

    cout << best_path(11, 12, mat, mat2) << endl;

    return 0;
}
*/
