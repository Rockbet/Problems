// Leonardo Paes
// same from Nson's code https://oj.uz/submission/243889

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> pip;
#define f first
#define s second
const int maxn = 3e4+10, magic = 200, inf = 0x3f3f3f3f;
int b[maxn], p[maxn], dist1[maxn], dist2[maxn][magic+5];
vector<int> doges[maxn];
bool mark[maxn];
vector<pii> fila[maxn*magic];
int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> b[i] >> p[i];
        doges[b[i]].push_back(i);
    }
    memset(dist1, inf, sizeof dist1);
    memset(dist2, inf, sizeof dist2);
    fila[0].push_back({b[0], 0});
	for(int d = 0; !fila[d].empty(); d++) {
		while(!fila[d].empty()){
			int u = fila[d].back().f, id = fila[d].back().s;
			int power = p[id];
			fila[d].pop_back();
			if(power <= magic){
				if(dist2[u][power] == inf) dist2[u][power] = d;
				if(u + power < n and dist2[u + power][power] == inf){
					fila[d + 1].push_back({u + power, id});
					dist2[u + power][power] = d + 1;
				}
				if(u - power >= 0 and dist2[u - power][power] == inf){
					fila[d + 1].push_back({u - power, id});
					dist2[u - power][power] = d + 1;
				}
			}
			else{
				if(dist1[u] == inf) dist1[u] = d;
				if(!mark[id]){
					mark[id] = 1;
					for(int v=u+power, qtd=1; v<n; v+=power, qtd++) fila[d+qtd].push_back({v, id});
					for(int v=u-power, qtd=1; v>=0; v-=power, qtd++) fila[d+qtd].push_back({v, id});
				}
			}
			if(!doges[u].empty()){
				for(auto v : doges[u]) fila[d].push_back({u, v});
				doges[u].clear();
			}
		}
	}
    int ans = dist1[b[1]];
    for(int i=1; i<=magic; i++) ans = min(ans, dist2[b[1]][i]);
    cout << (ans == inf ? -1 : ans) << "\n";
    return 0;
}
