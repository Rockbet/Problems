// USACO Tree Delegation
// Leonardo Paes

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10, inf = 0x3f3f3f3f;
vector<int> grafo[maxn];
bool bad;
int k;

bool ok(vector<int> &v, int mid){
    int l = 0, r = (int)v.size()-1;
    for(int i=0; i<(int)v.size()/2; i++){
        if(l == mid) l++;
        if(r == mid) r--;
        if(v[l] + v[r] < k) return 0;
        l++;
        r--;
    }
    return 1;
}

int dfs(int u, int p){
    if(bad) return -1;
    vector<int> v;
    for(int vv : grafo[u]){
        if(vv == p) continue;
        int d = dfs(vv, u) + 1;
        if(bad) return -1;
        v.push_back(min(k, d));
    }
    sort(v.begin(), v.end());
    bool aux = 1;
    int mx = -inf;
    {// se eu consigo parear normalmente
        vector<int> V = v; if(V.size()&1) V.insert(V.begin(), 0);
        aux = ok(V, -1);
    }
    {// se eu consigo fazer sobrar um, o máximo possível
        vector<int> V = v; if(!(V.size()&1)) V.insert(V.begin(), 0);
        int ini = -1, meio, fim = (int)v.size()-1;
        while(ini < fim){
            meio = (ini + fim + 1) >> 1;
            if(ok(v, meio)){
                ini = meio;
            }
            else{
                fim = meio - 1;
            }
        }
        if(ini >= 0) mx = v[ini];
    }
    if(u == 1){
        if(!aux) bad = 1;
        return -1;
    }
    if(mx != -inf) return mx;
    if(aux) return 0;
    bad = 1; return -1;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
    int n;
    cin >> n;
    for(int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    int ini = 1, meio, fim = n-1, ans = 1;
    while(ini <= fim){
        meio = (ini + fim) >> 1;
        bad = 0;
        k = meio;
        dfs(1, 0);
        if(!bad){
            ans = meio;
            ini = meio+1;
        }
        else{
            fim = meio-1;
        }
    }
    cout << ans << "\n";
    return 0;
}
