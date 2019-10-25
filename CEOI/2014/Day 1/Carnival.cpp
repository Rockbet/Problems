// CEOI 2014 - Carnival
// Leonardo Paes
//
// To solve the problem, let us use Divide and Conquer technique (D&C) and Union-Find DS. If we have a group of people with different
// costume and we want to know the costume of a new person, we just query the hole group. If the number of costume with this new person
// increase by one, it is using a new costume and we will add it to the group. Otherwise, it has the same costume of another one from
// the group. To find this one, we will recursively divide the group in the middle and query for one half the same way we did. When we
// find the person with the same costume (when the group has only one person), we join both to the same group.
// Overall number of queries N*logN.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 155;

int n, pai[maxn], siz[maxn], ans[maxn], color;

int find(int x){
	if(pai[x]==x) return x;
	return pai[x] = find(pai[x]);
}

void join(int a, int b){
	a = find(a), b = find(b);
	if(a==b) return;
	if(siz[a]<siz[b]) swap(a, b);
	pai[b] = a;
	siz[a] += siz[b];
}

int query(vector<int> const& rep, int u){
	cout << rep.size() + 1;
	for(int i=0; i<rep.size(); i++) cout << " " << rep[i];
	cout << " " << u << endl;
	int x;
	cin >> x;
	return x;
}

int dc(vector<int> const& rep, int u){
	if(rep.size()==1) return rep[0];

	int mid = rep.size()>>1;

	vector<int> half1, half2;

	for(int i=0; i<rep.size(); i++){
		if(i<mid) half1.push_back(rep[i]);
		else half2.push_back(rep[i]);
	}

	if(query(half1, u) == half1.size()) return dc(half1, u);
	return dc(half2, u);
}

int main(){
    cin >> n;

    for(int i=1; i<=n; i++) pai[i] = i, siz[i] = 1;

    for(int i=2; i<=n; i++){
    	vector<int> rep;
    	for(int j=1; j<i; j++) if(j==find(j)) rep.push_back(j);
    	if(query(rep, i) == rep.size()) join(i, dc(rep, i));
    }

    for(int i=1; i<=n; i++) if(i==find(i)) ans[i] = ++color;

    cout << 0;

   	for(int i=1; i<=n; i++) cout << " " << ans[find(i)];

   	cout << endl;

    return 0;
}
