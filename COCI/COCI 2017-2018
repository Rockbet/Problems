// COCI 2017/2018 - Cover
// Leonardo Paes
// 
// Same solution as in: https://codeforces.com/blog/entry/57508?#comment-411980

#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

const int maxn = 5e3+10;

const long long inf = 2e18+10;

typedef pair<int,int> pii;

pii points[maxn], useful_points[maxn];

int n;

long long dp[maxn];

bool mark[maxn];

int main(){
    cin >> n;

    for(int i=1; i<=n; i++){
        cin >> points[i].x >> points[i].y;

        points[i].x = abs(points[i].x);
        points[i].y = abs(points[i].y);
    }

    sort(points+1, points+n+1);

    int id = 0;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(!mark[j] and i!=j and points[i].x >= points[j].x and points[i].y >= points[j].y){
                mark[j] = 1;
            }
        }
    }

    for(int i=1; i<=n; i++){
        if(!mark[i]) useful_points[++id] = points[i];
    }

    for(int i=1; i<=id; i++) dp[i] = inf;

    dp[0] = 0;

    for(int i=1; i<=id; i++){
        for(int j=1; j<=id; j++){
            dp[i] = min(dp[i], dp[j-1] + 4LL*(useful_points[i].x)*(useful_points[j].y));
        }
    }

    cout << dp[id] << endl;

    return 0;
}
