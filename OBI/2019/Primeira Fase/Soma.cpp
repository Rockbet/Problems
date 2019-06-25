#include <bits/stdc++.h>

using namespace std;

const int maxn = 500100;

int vet[maxn], prefl[maxn], prefr[maxn];

long long int sum(long long a){
    if(a==0LL)return 0LL;
    return (a*(a+1LL))/2LL;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int n, k;

    cin >> n >> k;

    for(int i=1; i<=n; i++){
        cin >> vet[i];
    }
    long long ans=0;

    if(k!=0){
        for(int i=1; i<=n; i++){
            if(vet[i]==0){
                prefl[i]+=prefl[i-1]+1;
            }
            else{
                prefl[i]=0;
            }
        }
        for(int i=n; i>=1; i--){
            if(vet[i]==0){
                prefr[i]+=prefr[i+1]+1;
            }
            else{
                prefr[i]=0;
            }
        }

        int l=1, r=1;

        long long int soma=vet[1];

        for(int l=1, r=1; r<=n;){
            if(soma<(long long int)k){
                r++;
                soma+=(long long int)vet[r];
            }
            else if(soma>(long long int)k){
                soma-=(long long int)vet[l];
                l++;
            }
            else if(soma==(long long int)k){
                while(vet[l]==0){
                    l++;
                }
                if(prefl[l-1]!=0 or prefr[r+1]!=0){
                    if(prefl[l-1]==0){
                        ans+=prefr[r+1]+1;
                    }
                    else if(prefr[r+1]==0){
                        ans+=prefl[l-1]+1;
                    }
                    else{
                        ans+=(long long int)(prefl[l-1]+1)*(long long int)(prefr[r+1]+1);
                    }
                }
                else{
                    ans++;
                }
                r++;
                soma+=(long long int)vet[r];
                soma-=(long long int)vet[l];
                l++;
            }
        }

        cout << ans << "\n";
    }
    else{
        long long int atual=0;
        for(int i=1; i<=n; i++){
            if(vet[i]==0)atual++;
            else{
                ans+=sum(atual);
                atual=0;
            }
        }
        ans+=sum(atual);
        cout << ans << "\n";
    }
    return 0;
}
