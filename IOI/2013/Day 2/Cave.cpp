// IOI 2014 - Cave
// Leonardo Paes

#include <bits/stdc++.h>
#include "cave.h"

using namespace std;

const int maxn = 5e3+10;

int n;

int door[maxn], known[maxn], state[maxn], query[maxn];

bool open(int ans, int k){
	return (ans == -1 ? 1 : ans > k);
}

void dc(int l, int r, int id, int state_id){
	if(l==r){
		door[l] = id;
		known[l] = true;
		state[l] = state_id;
		return;
	}

	int mid = (l+r) >> 1;

	memset(query, 0, sizeof query);

	for(int i=0; i<n; i++){
		if(l<=i and i<=mid) query[i] = state_id;
		else query[i] = state_id ^ 1;
	}

	for(int i=0; i<n; i++){
		if(known[i]) query[i] = state[i];
	}

	if(open(tryCombination(query), id)) dc(l, mid, id, state_id);
	else dc(mid+1, r, id, state_id);
}

void exploreCave(int N) {
	n = N;

	for(int i=0; i<n; i++){
		memset(query, 0, sizeof query);

		for(int j=0; j<n; j++){
			if(known[j]) query[j] = state[j];
		}

		if(open(tryCombination(query), i)) dc(0, n, i, 0);
		else dc(0, n, i, 1);
	}

	answer(state, door);
}
