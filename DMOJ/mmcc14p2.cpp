#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3+10, maxm = 5e3;
int n, m;
struct node{
    bitset<maxm> band, bor;
} tree[maxm];
bitset<maxm> v[maxn];
node join(node a, node b){
    node c;
    c.band = a.band & b.band;
    c.bor = a.bor | b.bor;
    return c;
}
void build(int node, int l, int r){
    if(l == r){
        tree[node].band = tree[node].bor = v[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(2*node, l, mid), build(2*node+1, mid+1, r);
    tree[node] = join(tree[2*node], tree[2*node+1]);
}
void update(int node, int l, int r, int pos){
    if(l == r){
        tree[node].band = tree[node].bor = v[l];
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) update(2*node, l, mid, pos);
    else update(2*node+1, mid+1, r, pos);
    tree[node] = join(tree[2*node], tree[2*node+1]);
}
node nul;
node query(int node, int tl, int tr, int l, int r){
    if(tl > r or tr < l) return nul;
    if(tl >= l and tr <= r) return tree[node];
    int mid = (tl + tr) >> 1;
    return join(query(2*node, tl, mid, l, r), query(2*node+1, mid+1, tr, l, r));
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    nul.band.set();
    nul.bor.reset();
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        for(int j=0; j<m; j++){
            char a;
            cin >> a;
            if(a == '1') v[i][j] = 1;
        }
    }
    build(1, 1, n);
    int q;
    cin >> q;
    while(q--){
        int i, j;
        cin >> i >> j;
        node ans = query(1, 1, n, i, j);
        int a = 0;
        for(int l=0; l<m; l++){
            if(ans.band[l] == ans.bor[l]) a++;
            else break;
        }
        cout << a*(j-i+1) << "\n";
        swap(v[i], v[j]);
        update(1, 1, n, i);
        update(1, 1, n, j);
    }
    return 0;
}
