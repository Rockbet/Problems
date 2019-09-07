// COCI 2017 - Poklon
// Leonardo Paes

// Same solution as the editorial: http://hsin.hr/coci/archive/2016_2017/contest7_solutions.zip

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

int n, a, b, sum;

struct nod{
    int l=0, r=0;
}node[maxn];

void get_max(int newa, int newb){
    int length = 32-__builtin_clz(newa), lengtha = 32-__builtin_clz(a);
    int newsum = length + newb;
    if(newsum>sum){
        a = newa, b = newb, sum = newsum;
    }
    else if(newsum==sum){
        while(length--){
            lengtha--;
            if(newa&(1<<length) and (a&(1<<lengtha))==0){
                a = newa, b = newb, sum = newsum;
                return;
            }
            else if((newa&(1<<length))==0 and a&(1<<lengtha)){
                return;
            }
        }
    }
}

void dfs(int u, int d){
    d++;
    if(node[u].l>0)dfs(node[u].l, d);
    else get_max(-node[u].l, d);
    if(node[u].r>0)dfs(node[u].r, d);
    else get_max(-node[u].r, d);
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

    cin >> n;

    for(int i=1; i<=n; i++){
        cin >> node[i].l >> node[i].r;
    }

    dfs(1, 0);

    int length = 32-__builtin_clz(a);

    while(length--)cout << (a&(1<<length)? 1 : 0);

    while(b--)cout << 0;

    cout << "\n";

    return 0;
}
