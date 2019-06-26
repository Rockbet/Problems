// The idea to solve this problem is to use a map<vector<int>, int> that answer us about the number
// of strings of some type. For each extra character, we increase it`s frequence on our current vector.
// after that, we use vector aux to have the current - the minimum frequence at current, this way we have our minimum possible
// number of different charcters to decrease. Then, we add to the answer the number of vectors of the same type of aux that we
// had already saved in our map. We fix the answer with the mod and then increse map[aux] in 1.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+100, mod = 1e9+7;

int freq[55];

map<vector<int>, int> m;

int now(char x){
    if(x>='a'){
        return (int)x-71;
    }
    else return (int)x-65;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int n, k=0;

    string s;

    cin >> n;

    cin >> s;

    for(int i=0; i<n; i++){
        freq[now(s[i])]=1;
    }

    vector<int> chars;

    for(int i=0; i<26*2; i++){
        if(freq[i]==1){
            chars.push_back(i);
        }
    }

    vector<int> current(chars.size()), aux(chars.size());

    long long ans=0;

    m[current]++;

    for(int i=0; i<n; i++){
        int minimum=n;
        for(int j=0; j<chars.size(); j++){
            if(chars[j]==now(s[i])){
                current[j]++;
            }
            minimum=min(minimum, current[j]);
        }
        for(int j=0; j<chars.size(); j++){
            aux[j] = current[j] - minimum;
        }
        ans += m[aux];
        if(ans>=mod)ans-=mod;
        m[aux]++;
    }

    cout << ans << '\n';

    return 0;
}
