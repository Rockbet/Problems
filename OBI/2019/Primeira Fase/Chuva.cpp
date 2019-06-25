#include <bits/stdc++.h>

using namespace std;

const int maxn = 550;

char mat[maxn][maxn];

void dfs(int x, int y){
    if(mat[x+1][y]=='.'){
        mat[x+1][y]='o';
        dfs(x+1, y);
    }
    else if(mat[x+1][y]=='#'){
        if(mat[x][y-1]=='.'){
            mat[x][y-1]='o';
            dfs(x, y-1);
        }
        if(mat[x][y+1]=='.'){
            mat[x][y+1]='o';
            dfs(x, y+1);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int n, m;

    cin >> n >> m;

    int inii, inij;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cin >> mat[i][j];
            if(mat[i][j]=='o'){
                inii=i;
                inij=j;
            }
        }
    }

    dfs(inii, inij);

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cout << mat[i][j];
        }
        cout << "\n";
    }

    return 0;
}
