// The idea here is to, from the first day, "brute force" all the other days, using bitmasks, as we have a maximum
// of 2^n possible different types of days, at maximum. If we have to calculate all of them, it is fine, because
// it is fast enough. Otherwise, after precalcuting some of them, we will reach a precalculated day.
// Then we know the answer because a cycle will begin! To solve the cycle just use a prefix sum on the number of
// watermelons used at precalculated days.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 20;

int n, h, viz[22], temp[(1<<maxn)+10];
long long ans, pref[(1<<maxn)+10];

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    cin >> n >> h;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            char c;
            cin >> c;
            int x = c - '0';
            if(x==1) viz[i] |= (1<<(j));
        }
    }

    int mask = viz[0];
    ans = __builtin_popcount(viz[0]);
    h--;
    for(int day=1; day<=h; day++){
        if(temp[mask]==0){
            temp[mask]=day;
            int atual = 0;
            int sum = 0;
            for(int i=0; i<n; i++){
                if(mask&(1<<i)) {
                    atual ^= viz[i];
                    sum += __builtin_popcountll(viz[i]);
                }
                else sum += 2*__builtin_popcountll(viz[i]);
            }
            pref[day]=1LL*sum+pref[day-1];
            ans+=sum;
            mask=atual;
        }
        else{
            int ini = temp[mask];
            int tam = day - ini;
            h = h - day + 1;
            ans += 1LL*(pref[day - 1] - pref[ini - 1])*(h/tam);
            int rest = h % tam;
            if(rest != 0) ans += pref[ini + rest - 1] - pref[ini - 1];
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
