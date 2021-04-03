// Leonardo Paes
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
const int maxn = 1e5+10;
inline int gcd(int a, int b){
    while(b){ 
        int c = b;
        b = a%b;
        a = c;
    }
    return a;
}
int v[maxn];
struct Node{
    int g;
    ll fvck;
    map<int,ll> pref, suf; // gcd, freq
    Node(){
        g = 0;
    }
    Node(int x){
        pref[x] = 1;
        suf[x] = 1;
        g = x;
        fvck = x == 1;
    }
};
struct Seg{
    Node tree[1<<19];
    Node join(Node &a, Node &b){
        if(a.g == 0) return b;
        if(b.g == 0) return a;
        Node c;
        c.g = gcd(a.g, b.g);
        c.fvck = a.fvck + b.fvck;
        c.pref = a.pref;
        c.suf = b.suf;
        for(auto it : a.suf){
            int val = gcd(it.f, b.g);
            c.suf[val] += it.s;
        }
        for(auto it : b.pref){
            int val = gcd(it.f, a.g);
            c.pref[val] += it.s;
        }
        for(auto te : a.suf){
            for(auto amo : b.pref){
                int val = gcd(te.f, amo.f);
                if(val == 1) c.fvck += 1LL*te.s*amo.s; // Pietra
            }
        }
        return c;
    }
    void build(int node, int l, int r){
        if(l == r){
            tree[node] = Node(v[l]);
            return;
        }
        int mid = (l + r) >> 1;
        build(2*node, l, mid), build(2*node+1, mid+1, r);
        tree[node] = join(tree[2*node], tree[2*node+1]);
    }
    void update(int node, int l, int r, int pos, int val){
        if(l == r){
            tree[node] = Node(val);
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) update(2*node, l, mid, pos, val);
        else update(2*node+1, mid+1, r, pos, val);
        tree[node] = join(tree[2*node], tree[2*node+1]);
    }
    Node query(int node, int tl, int tr, int l, int r){
        if(tl > r or tr < l) return Node();
        if(tl >= l and tr <= r) return tree[node];
        int mid = (tl + tr) >> 1;
        Node a = query(2*node, tl, mid, l, r), b = query(2*node+1, mid+1, tr, l, r);
        return join(a, b);
    }
}seg;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    for(int i=1; i<=n; i++) cin >> v[i];
    seg.build(1, 1, n);
    while(m--){
        int t, a, b;
        cin >> t >> a >> b;
        if(t == 1){
            seg.update(1, 1, n, a, b);
        }
        else{
            cout << 1LL*(b-a+1)*(b-a+2)/2 - seg.query(1, 1, n, a, b).fvck << "\n";
        }
    }
    return 0;
}
