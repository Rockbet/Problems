// The code is really ugly so I will explain the idea.
// For each K use a freq array to count the frequency of the first p elements.
// Use the two pointers technic in the freq array. Then, all elements with indices <= p are ordered.
// When we add a new element to our algo, we have two choices:
// Or it is <= our r pointer, or it is greater. If it is <=, we just do: freq[element]++;
// Otherwise, it is the greater element now! So, we just have to give it to the other player.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n, q, vet[maxn], freq[maxn];

int main(){

    cin >> n >> q;

    for(int i=1; i<=n; i++){
        cin >> vet[i];
    }

    for(int i=1; i<=q; i++){

        int p;

        cin >> p;

        memset(freq, 0, sizeof freq);

        for(int j=1; j<=p; j++){
            freq[vet[j]]++;
        }

        long long a=0, b=0;
        for(int j=n, player=0, cur=p, added=0; added<=n;){
            cur++;
            while(j>-1 and freq[j]==0){
                j--;
                if(j==-1)break;
            }
            if(j==-1){
                if(player==0){
                    a+=vet[cur];
                    added++;
                    if(added==n)break;
                    player^=1;
                }
                else{
                    b+=vet[cur];
                    added++;
                    if(added==n)break;
                    player^=1;
                }
            }
            else{
                if(player==0){
                    a+=j;
                    freq[j]--;
                    added++;
                    if(added==n)break;
                    if(cur<=n){
                        while(vet[cur]>j){
                            player^=1;
                            if(player==0)a+=vet[cur];
                            else b+=vet[cur];
                            cur++;
                            added++;
                            if(added==n)break;
                            if(cur==n+1){
                                player^=1;
                                break;
                            }
                        }
                        if(added==n)break;
                        if(cur==n+1)continue;
                        freq[vet[cur]]++;
                        player^=1;
                    }
                    else player^=1;
                }
                else{
                    b+=j;
                    freq[j]--;
                    added++;
                    if(added==n)break;
                    if(cur<=n){
                        while(vet[cur]>j){
                            player^=1;
                            if(player==0)a+=vet[cur];
                            else b+=vet[cur];
                            cur++;
                            added++;
                            if(added==n)break;
                            if(cur==n+1){
                                player^=1;
                                break;
                            }
                        }
                        if(added==n)break;
                        if(cur==n+1)continue;
                        freq[vet[cur]]++;
                        player^=1;
                    }
                    else player^=1;
                }
            }
        }
        cout << a-b << '\n';
    }

    return 0;

}
