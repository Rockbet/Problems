// BOI 2011 - Switch the Lamp On
// Leonardo Paes

// My solution has the same idea of the official solution: 
// https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2011_solutions/lamp-sol.pdf
// The only difference is that in my code I used Dijkstra algorithm to find the shortest path from 1,1 to n,m, but it can be done with
// a deque in O(NM), since the weight of the edges are either 0 or 1. This algorithm is called "0-1 BFS". 
// Notice that my solution is a little bit slower, with a complexity of O(NM*log2(NM)).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 510, inf = 0x3f3f3f3f;

typedef pair<int,int> pii;
typedef pair<int,pii> pip;

int n, m, mat[maxn][maxn], dist[maxn][maxn];

int xh[8]={-1, -1, -1, 0, 0, 1, 1, 1};
int yh[8]={-1, 0, 1, -1, 1, -1, 0, 1};

bool mark[maxn][maxn];

void dijkstra(){
    memset(dist, inf, sizeof dist);
    dist[1][1]=mat[1][1];
    priority_queue<pip, vector<pip>, greater<pip> > fila;
    fila.push({dist[1][1],{1, 1}});
    while(!fila.empty()){
        int d = fila.top().first;
        int x = fila.top().second.first, y = fila.top().second.second;
        fila.pop();
        if(!mark[x][y]){
            mark[x][y]=1;
            for(int i=0; i<8; i++){
                if((x+y)%2==0){
                    if(i==2 or i==5)continue;
                    int newx = x + xh[i];
                    int newy = y + yh[i];
                    if(newx>=1 and newx<=n and newy>=1 and newy<=m){
                        if(dist[newx][newy] > dist[x][y] + mat[newx][newy]){
                            dist[newx][newy] = dist[x][y] + mat[newx][newy];
                            fila.push({dist[newx][newy], {newx, newy}});
                        }
                    }
                }
                else{
                    if(i==0 or i==7)continue;
                    int newx = x + xh[i];
                    int newy = y + yh[i];
                    if(newx>=1 and newx<=n and newy>=1 and newy<=m){
                        if(dist[newx][newy] > dist[x][y] + mat[newx][newy]){
                            dist[newx][newy] = dist[x][y] + mat[newx][newy];
                            fila.push({dist[newx][newy], {newx, newy}});
                        }
                    }
                }
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    cin >> n >> m;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            char a;
            cin >> a;
            int aux = i+j;
            if(a=='/'){
                if(aux%2==0){
                    mat[i][j]=1;
                }
            }
            else{
                if(aux%2){
                    mat[i][j]=1;
                }
            }
        }
    }

    if(n%2 != m%2){
        cout << "NO SOLUTION\n";
        return 0;
    }

    dijkstra();

    cout << dist[n][m] << "\n";

    return 0;
}
