// OBI 2018 - Cinco
// Leonardo Paes

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3 + 10;

int n, leftmost0=maxn, leftmost5=maxn, rightmost5=-1, vet[maxn];

bool ans = true;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

    cin >> n;

    for(int i=1; i<=n; i++){
        cin >> vet[i];
        if(vet[i]==0 and leftmost0==maxn) leftmost0 = i;
        if(vet[i]==5 and leftmost5==maxn) leftmost5 = i;
        if(vet[i]==5) rightmost5 = max(rightmost5, i);
    }

    if(vet[n]<5 and leftmost0!=maxn){
        swap(vet[n], vet[leftmost0]);
    }
    else if(vet[n]<5 and leftmost0==maxn){
        if(rightmost5!=-1){
            swap(vet[n], vet[rightmost5]);
        }
        else{
            ans = false;
        }
    }
    else if(vet[n]>5 and min(leftmost0, leftmost5)!=maxn){
        swap(vet[n], vet[min(leftmost0, leftmost5)]);
    }
    else{
        ans = false;
    }

    if(ans){
        for(int i=1; i<=n; i++){
            cout << vet[i] << " ";
        }
        cout << "\n";
    }
    else{
        cout << -1 << "\n";
    }
}
