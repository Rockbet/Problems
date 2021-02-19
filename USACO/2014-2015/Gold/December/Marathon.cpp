// USACO Gold Dec 2014 - Guard Mark
// Leonardo Paes

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+100;

int n, q, tree[4*maxn], triple[4*maxn];

pair<int,int> point[maxn];

int dist(int x, int y){
    return abs(point[x].first-point[y].first) + abs(point[x].second-point[y].second);
}

void build(int node, int l, int r){
    if(l==r){
        if(l<n)tree[node]=dist(l, l+1);
        if(l<n-1)triple[node]=dist(l, l+1)+dist(l+1,l+2)-dist(l,l+2);
        return;
    }
    int mid = (l+r)>>1;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    tree[node] = tree[2*node] + tree[2*node+1];
    triple[node] = max(triple[2*node], triple[2*node+1]);
}

void update(int node, int l, int r, int id){
    if(l>id or id>r)return;
    if(l==r){
        if(l>=1 and r<n)tree[node] = dist(l, l+1);
        return;
    }
    int mid = (l+r)>>1;
    if(l<=id and id<=mid){
        update(2*node, l, mid, id);
    }
    else{
        update(2*node+1, mid+1, r, id);
    }
    tree[node] = tree[2*node]+tree[2*node+1];
}

void update_triple(int node, int l, int r, int id){
    if(l>id or id>r)return;
    if(l==r){
        if(l>=1 and r<n-1)triple[node]=dist(l, l+1)+dist(l+1, l+2)-dist(l, l+2);
        return;
    }
    int mid = (l+r)>>1;
    if(l<=id and id<=mid){
        update_triple(2*node, l, mid, id);
    }
    else{
        update_triple(2*node+1, mid+1, r, id);
    }
    triple[node] = max(triple[2*node], triple[2*node+1]);
}

int query(int node, int tl, int tr, int l, int r){
    if(tl>r or tr<l)return 0;
    if(l<=tl and tr<=r)return tree[node];
    int mid=(tl+tr)>>1;
    return query(2*node, tl, mid, l, r) + query(2*node+1, mid+1, tr, l, r);
}

int query_triple(int node, int tl, int tr, int l, int r){
    if(tl>r or tr<l)return 0;
    if(l<=tl and tr<=r)return triple[node];
    int mid=(tl+tr)>>1;
    return max(query_triple(2*node, tl, mid, l, r), query_triple(2*node+1, mid+1, tr, l, r));
}

int main(){

    freopen("marathon.in", "r", stdin);
	freopen("marathon.out", "w", stdout);

    cin >> n >> q;

    for(int i=1; i<=n; i++){
        cin >> point[i].first >> point[i].second;
    }

    build(1, 1, n);

    for(int i=1; i<=q; i++){
        char type;

        cin >> type;

        if(type=='U'){
            int id, x, y;

            cin >> id >> x >> y;

            point[id].first=x, point[id].second=y;

            update(1, 1, n, id-1);
            update(1, 1, n, id);

            update_triple(1, 1, n, id-2);
            update_triple(1, 1, n, id-1);
            update_triple(1, 1, n, id);
        }
        if(type=='Q'){
            int l, r;

            cin >> l >> r;

            cout << query(1, 1, n, l, r-1) - query_triple(1, 1, n, l, r-2) << endl;
        }
    }

    return 0;
}
