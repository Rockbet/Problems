// Let's define: state==0 means a vertice has it initial edges and state==1 means a vertice swapped its edges.
// We have to consider two cases: If an edge was given in the input or not. If it was, we have two options: both vertices of
// the edge have state 0 or both have state 1, because we need to continue having this edge.
// If the edge wasn't given in the input, we have one case: one of the vertices of the edge must have state==1 and the other one
// must have state==0, because we need to "create" this edge.
// To begin our checking, lets consider only one vertice to each vertice, to start our state array with right values, the vertice
// vertice-1.
// After creating the state array, we have to check all pairs of vertices, and check if the state arrays is still right. If it is not
// we know it is impossible, because this state was needed to calculate another vertice.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+3;

bool state[maxn], tab[maxn][maxn], ok=1;

#define gc getchar

inline int scan(void){
	int n = 0, x = gc(), s =1;
	for (;x<'0'||x>'9';x=gc()) if(x=='-') s=-1;
	for (;x>='0'&&x<='9';x=gc()) n = (n<<3) + (n<<1) + x-'0';
	return n;
}

int main(){

    int n, m;

    n = scan(), m = scan();

    for(int i=0; i<m; i++){
        int x, y;
        x = scan(), y = scan();
        tab[x][y]=tab[y][x]=1;
    }

    for(int i=2; i<=n; i++){
        state[i]=state[i-1];
        if(tab[i][i-1]==0)state[i]^=1;
    }

    for(int i=1; i<=n; i++){
        for(int j=i+1; j<=n; j++){
            int sum = state[i]+state[j];
            if(tab[i][j]==0)if(sum%2==0)ok=0;
            if(tab[i][j]==1)if(sum%2==1)ok=0;
        }
        if(ok==0){
            printf("NE\n");
            return 0;
        }
    }
    printf("DA\n");
}
