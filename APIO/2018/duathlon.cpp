// Leonardo Paes

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5+10;
vector<int> grafo[maxn], bcc[2*maxn];
int n, m, in[maxn], low[maxn], sub[2*maxn], t, sz, bccs = 1; // tempo de entrada e menor tempo de entrada de back-edge
stack<int> s;
 
void dfs(int u, int p = 0){
    in[u] = low[u] = ++t;
    s.push(u);
    ++sz;
    for(int v : grafo[u]){
        if(v == p) continue;
        if(!in[v]){
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= in[u]){
                int id = n + bccs;
                bcc[u].push_back(id);
                while(bcc[id].empty() or bcc[id].back() != v){
                    bcc[id].push_back(s.top());
                    s.pop();
                }
                bccs++;
            }
        }
        else low[u] = min(low[u], in[v]);
    }
}
 
ll solve(int u){
    ll ans = 0, tam;
    sub[u] = (u <= n);
    tam = (ll)bcc[u].size();
    for(int v : bcc[u]){
        ans += solve(v);
        sub[u] += sub[v];
        if(u > n) ans += tam * sub[v] * (sub[v] - 1);
    }
    if(u > n) ans += tam * (sz - sub[u]) * (sz - sub[u] - 1);
    return ans;
}
 
int32_t main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1; i<=m; i++){
        int u, v;
        cin >> u >> v;
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    ll ans = 0;
    for(int i=1; i<=n; i++){
        if(!in[i]){
            sz = 0;
            dfs(i);
            ans += 1LL * sz * (sz-1) * (sz-2); // total
            ans -= solve(i); // triplas ruins
        }
    }
    cout << ans << "\n";
    return 0;
}
