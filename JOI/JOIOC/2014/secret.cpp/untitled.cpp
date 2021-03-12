#include "secret.h"
#include <bits/stdc++.h>

typedef std::pair<int,int> pii;
#define f first
#define s second
const int maxn = 1030;
int v[maxn], n;

class Seg{
public:
	void build(int node, int l, int r){
		if(l == r){
			pref[node].push_back(v[l]);
			return;
		}
		int mid = (l + r) >> 1;
		int val;
		for(int i=mid; i>=l; i--){
			if(i == mid) suf[node].push_back(val = v[i]);
			else suf[node].push_back(val = Secret(v[i], val));
		}
		for(int i=mid+1; i<=r; i++){
			if(i == mid+1) pref[node].push_back(val = v[i]);
			else pref[node].push_back(val = Secret(val, v[i]));
		}
		build(2*node, l, mid), build(2*node+1, mid+1, r);
	}
	int query(int node, int tl, int tr, int l, int r){
		int mid = (tl + tr) >> 1;
		if(tl == tr) return pref[node].front();
		if(l <= mid and mid+1 <= r){
			return Secret(suf[node][mid - l], pref[node][r - mid - 1]);
		}
		else if(l >= mid+1) return query(2*node+1, mid+1, tr, l, r);
		else return query(2*node, tl, mid, l, r);
	}
private:
	std::vector<int> pref[2*maxn], suf[2*maxn];
}seg;

void Init(int N, int A[]) {
	n = N;
	for(int i=1; i<=N; i++) v[i] = A[i-1];
	seg.build(1, 1, n);
}

int Query(int L, int R) {
	L++, R++;
	return seg.query(1, 1, n, L, R);
}