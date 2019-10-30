// JOIOC 2017-2018 - Xylophone
// Leonardo Paes
//
// To solve it, let's find the position of the number 1 and the number n. To do it, let's use binary search. To find 1 we fix the end
// and guess the start, with the inequality query(mid, end) >= (n-1). To find n we fix the start to be to position of number 1 and guess
// the end point, with the same inequality. After knowing it, we find their neighbors using 1 query for each one. Then, we solve to the
// left of the 1 position and to the left of the n position and to the right of the n position. To discover the number i knowning i+1 and
// i+2 we can just use the differences: query(i, i+1) and query(i, i+2), using the inequality:
// query(i, i+1) + abs(ans[i+1] - ans[i+2]) == query(i, i+2). Knowning this, one can determine the answer of ith position. 
// We have to save queries when possible, because using this solution naively costs:
// 2log2(n) + 1 (1 and n are neighbors and one of them doesn't have another neighbor) + 2*(n-3) queries in worst case, 
// which is ~ 10019.

#include <bits/stdc++.h>
#include "xylophone.h"

using namespace std;

const int maxn = 5e3+10;

int n, res[maxn], pos[maxn];

inline void find_1(){
    int ini=1, fim=n, meio, ans=-1;

    while(ini<=fim){
        meio = (ini+fim) >> 1;
        if(query(meio, n)>=(n-1)){
            ans = meio;
            ini = meio+1;
        }
        else{
            fim = meio-1;
        }
    }

    pos[1] = ans;
    res[ans] = 1;
}

inline void find_n(){
    int ini=pos[1]+1, fim=n, meio, ans=-1;

    while(ini<=fim){
        meio = (ini+fim) >> 1;
        if(query(pos[1], meio)>=(n-1)){
            ans = meio;
            fim = meio-1;
        }
        else{
            ini = meio+1;
        }
    }

    pos[n] = ans;
    res[ans] = n;
}

inline void solve_left(int j, int k){
    if(j<=1 or res[j-1]!=0) return;

    int i = j-1;
    int diff1 = query(i, j);

    if((res[j] + diff1) > n or pos[res[j] + diff1]!=0){
        res[i] = res[j] - diff1;
        pos[res[i]] = i;
    }
    else if((res[j] - diff1) < 1 or pos[res[j] - diff1]!=0){
        res[i] = res[j] + diff1;
        pos[res[i]] = i;
    }
    else{
        int diff2 = query(i, k);

        if(diff1 + abs(res[j]-res[k]) == diff2){
            if(res[k]<res[j]){
                res[i] = res[j] + diff1;
                pos[res[i]] = i;
            }
            else{
                res[i] = res[j] - diff1;
                pos[res[i]] = i;
            }
        }
        else{
            if(res[k]<res[j]){
                res[i] = res[j] - diff1;
                pos[res[i]] = i;
            }
            else{
                res[i] = res[j] + diff1;
                pos[res[i]] = i;
            }
        }

    }
    solve_left(i, j);
}

inline void solve_right(int j, int k){
    if(k>=n or res[k+1]!=0) return;

    int l = k+1;
    int diff1 = query(k, l);

    if((res[k] + diff1) > n or pos[res[k] + diff1]!=0){
        res[l] = res[k] - diff1;
        pos[res[l]] = l;
    }
    else if((res[k] - diff1) < 1 or pos[res[k] - diff1]!=0){
        res[l] = res[k] + diff1;
        pos[res[l]] = l;
    }
    else{
        int diff2 = query(j, l);

        if(diff1 + abs(res[j]-res[k]) == diff2){
            if(res[k]>res[j]){
                res[l] = res[k] + diff1;
                pos[res[l]] = l;
            }
            else{
                res[l] = res[k] - diff1;
                pos[res[l]] = l;
            }
        }
        else{
            if(res[k]>res[j]){
                res[l] = res[k] - diff1;
                pos[res[l]] = l;
            }
            else{
                res[l] = res[k] + diff1;
                pos[res[l]] = l;
            }
        }

    }
    solve_right(k, l);
}

void solve(int N){
    n = N;
    find_1();
    find_n();

    int diff;

    if(pos[1]+1 <= n and res[pos[1]+1] == 0){
        diff = query(pos[1], pos[1]+1);
        res[pos[1]+1] = 1 + diff;
        pos[1+diff] = pos[1]+1;
    }

    if(pos[1]-1 >= 1 and res[pos[1]-1] == 0){
        diff = query(pos[1]-1, pos[1]);
        res[pos[1]-1] = 1 + diff;
        pos[1+diff] = pos[1]-1;
    }

    if(pos[n]+1 <=n and res[pos[n]+1] == 0){
        diff = query(pos[n], pos[n]+1);
        res[pos[n]+1] = n - diff;
        pos[n-diff] = pos[n]+1;
    }

    if(pos[n]-1 >= 1 and res[pos[n]-1] == 0){
        diff = query(pos[n]-1, pos[n]);
        res[pos[n]-1] = n - diff;
        pos[n-diff] = pos[n] - 1;
    }

    solve_left(pos[1]-1, pos[1]);
    solve_left(pos[n]-1, pos[n]);
    solve_right(pos[n], pos[n]+1);

    for(int i=1; i<=n; i++){
        answer(i, res[i]);
    }
}
