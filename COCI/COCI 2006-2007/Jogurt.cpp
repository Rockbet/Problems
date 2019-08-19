// COCI '06 Contest 4 #5 Jogurt
// Leonardo Paes

// The main idea of the solution is to create a tree with depth x+1 from a tree with depth x.
// The base case is x==0, when our root , tree[0], recieves 1.
// Then, we replicate our last tree into our new left and right subtrees, duplicating them.
// To organize the subtrees, we can add 1 to all the non-leaves in the left subtree and add 1 to all leaves in the right one.
// This way, we will be adding 2^x - 1 to the left subtree sum and 2^x to the right subtree sum, maintaining the asked properties.

#include <bits/stdc++.h>

using namespace std;

int tree[1<<15], level[1<<15];

void solve(int x){
    for(int i=(1<<x)-1; i>=1; i--){
        tree[i]=tree[i+(1<<x)-1]=2*tree[i-1];
        level[i]=level[i+(1<<x)-1]=level[i-1]+1;
    }
    for(int i=1; i<=((1<<(x+1))-2); i++){
        //left subtree
        if(level[i]!=x and i<=((1<<x)-1))tree[i]++;
        //right subtree
        if(level[i]==x and i>((1<<x)-1))tree[i]++;
    }
}

int main(){
    int n;

    scanf("%d", &n);

    tree[0]=1, level[0]=0;

    for(int i=1; i<n; i++)solve(i);

    for(int i=0; i<(1<<n)-1; i++)printf("%d ", tree[i]);

    return 0;
}
