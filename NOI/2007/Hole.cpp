// The main idea to solve this problem is: Binary search for the answer, for each position (i, j) of the matrix.
// The search will tell us the best solution to each position, and for best solution I mean the biggest solution.
// To check if a hole size is possible starting at position (i, j), we just have to precalculate the number of ones
// starting from (0, 0) and ending in (i, j), for all (i, j) from(0, 0) to (n-1, n-1). So, by the inclusion-exclusion principle
// , for a hole of length x, it exists starting in (i, j), if, and only if:
// pref[i+x][j+x]-pref[i+x][j-1]-pref[i-1][j+xpref[i-1][j-1])==0.
// The solution is as follows:


#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+50;

int n, a, mat[maxn][maxn], pref[maxn][maxn];

void calc(){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            pref[i][j]=mat[i][j]+pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1];
        }
    }
}

bool check(int i, int j, int x){
    x--;
    if((i+x)>n or(j+x)>n)return false;
    int newi = i+x;
    int newj = j+x;
    if((pref[newi][newj]-pref[newi][j-1]-pref[i-1][newj]+pref[i-1][j-1])==0)return true;
    return false;
}

int busca(int i, int j){

    int ini=1, fim=n, meio, best=-1;

    while(ini<=fim){
        meio=(ini+fim)>>1;
        if(check(i, j, meio)){
            ini=meio+1;
            best=meio;
        }
        else{
            fim=meio-1;
        }
    }

    return best;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    cin >> n >> a;

    for(int i=1; i<=a; i++){
        int x, y;
        cin >> x >> y;
        x++, y++;
        mat[x][y]=1;
    }

    calc();

    int ans=0;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            ans=max(ans,busca(i, j));
        }
    }

    cout << ans << endl;
}
