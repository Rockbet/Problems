// USACO Gold Dec 2014 - Cowjog
// Leonardo Paes

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+100;

long long n, t, vet[maxn];

multiset<long long> m;

int main(){

    freopen("cowjog.in", "r", stdin);
	freopen("cowjog.out", "w", stdout);

    cin >> n >> t;

    for(int i=1; i<=n; i++){
        long long id, acc;

        cin >> id >> acc;

        vet[i] = id + acc*t;
    }

    for(int i=1; i<=n; i++){
        multiset<long long>::iterator it = lower_bound(m.begin(), m.end(), vet[i]);
        
        if(it!=m.begin()) m.erase(--it);
        m.insert(vet[i]);
    }

    cout << m.size() << endl;

    return 0;
}
