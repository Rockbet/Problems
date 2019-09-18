// OBI 2018 - Baldes
// Leonardo Paes

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+100;

struct Node{
    int mi, ma, ans;
} tree[4*maxn];

Node noth = {-1, -1, -1};

Node op(Node const& a, Node const& b){
    if(a.mi==-1) return b;
    if(b.mi==-1) return a;
    return {min(a.mi, b.mi), max(a.ma, b.ma), max({a.ans, b.ans, abs(a.ma-b.mi), abs(b.ma-a.mi)})};
}

int n, m, vet[maxn];

void build(int node, int l, int r){
    if(l==r){
        tree[node].mi = tree[node].ma = vet[l];
        return;
    }
    int mid = (l+r) >> 1;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    tree[node] = op(tree[2*node], tree[2*node+1]);
}

void update(int node, int l, int r , int idx, int val){
    if(l==r){
        tree[node].mi = min(tree[node].mi, val);
        tree[node].ma = max(tree[node].ma, val);
        return;
    }
    int mid = (l+r) >> 1;
    if(idx<=mid){
        update(2*node, l, mid, idx ,val);
    }
    else{
        update(2*node+1, mid+1, r, idx, val);
    }
    tree[node] = op(tree[2*node], tree[2*node+1]);
}

Node query(int node, int tl, int tr, int l, int r){
    if(tl>r or tr<l) return noth;
    if(tl>=l and tr<=r) return tree[node];
    int mid = (tl+tr) >> 1;
    return op(query(2*node, tl, mid, l, r), query(2*node+1, mid+1, tr, l, r));
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

    cin >> n >> m;

    for(int i=1; i<=n; i++){
        cin >> vet[i];
    }

    build(1, 1, n);

    for(int i=1; i<=m; i++){
        int type, a, b;

        cin >> type >> a >> b;

        if(type==1){
            update(1, 1, n, b, a);
        }
        if(type==2){
            cout << query(1, 1, n, a, b).ans << "\n";
        }
    }

    return 0;
}
