#include <bits/stdc++.h>

using namespace std;

const int maxn = 550;

int vet[maxn];

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int n;

    cin >> n;

    for(int i=1; i<=n; i++){
        cin >> vet[i];
    }

    int ans = 1;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(i==j)continue;
            int last=i;
            int atual=0;
            for(int k=1; k<=n; k++){
                if(last==i and vet[k]==j){
                    atual++;
                    last=j;
                }
                else if(last==j and vet[k]==i){
                    atual++;
                    last=i;
                }
            }
            ans=max(ans, atual);
        }
    }

    cout << ans << endl;

    return 0;
}
