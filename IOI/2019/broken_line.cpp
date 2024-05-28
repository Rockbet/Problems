#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define x first
#define y second
struct compy{
	bool operator()(pii a, pii b) const{
		if(a.y == b.y) return a.x < b.x; // doesnt matter
		return a.y < b.y;
	}
};
vector<pii> diag[2]; // diag0 = \, diag1 = /, from top to bottom
vector<vector<pii>> spiral;
set<pii> px; // points sorted by smaller x
set<pii, compy> py; // points sorted by smaller y
void rem(vector<pii> &v){
	for(pii p : v){
		px.erase(p);
		py.erase(p);
	}
	//cout << "removal good" << endl;
}
void decompose(){
	//cout << "left is " << px.size() << endl;
	if(px.empty()) return; // px and py size should always be the same
	set<pii> sz;
	vector<pii> border; // up, right, down, left
	border.push_back(*py.rbegin());
	sz.insert(border.back());
	border.push_back(*px.rbegin());
	sz.insert(border.back());
	border.push_back(*py.begin());
	sz.insert(border.back());
	border.push_back(*px.begin());
	sz.insert(border.back());
	//cout << "size is " << sz.size() << endl;
	if(sz.size() == 1){
		diag[0].push_back(border.back());
		rem(border);
		decompose();
		return;
	}
	else if(sz.size() == 2){
		int iddiag = (border[0] == border[1]); // up right or up left (diag1 or diag0)
		diag[iddiag].push_back(border[0]);
		rem(border);
		decompose();
		diag[iddiag].push_back(border[2]);
		return;
	}
	else if(sz.size() == 3){
		for(int i=0; i<4; i++){
			for(int j=i+1; j<4; j++){
				if(border[i] == border[j]){
					int iddiag = ((i == 0 and j == 1) or (i == 2 and j == 3)); // up right or down left is diag1
					vector<pii> aux;
					aux.push_back(border[i]);
					rem(aux);
					if(i == 0){
						diag[iddiag].push_back(border[i]);
						decompose();
						return;
					}
					else{
						decompose();
						diag[iddiag].push_back(border[i]);
						return;
					}
				}
			}
		}
	}
	else if(sz.size() == 4){
		//cout << "wtf" << endl;
		spiral.push_back(border);
		rem(border);
		//cout << "decompose some more" << endl;
		decompose();
	}
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	freopen("tests/10.in", "r", stdin);
	freopen("tests/10.out", "w", stdout);
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		pii p;
		cin >> p.x >> p.y;
		px.insert(p);
		py.insert(p);
	}
	decompose();
	vector<pii> ans;
	vector<int> type; // 0 is up, 1 is down, 2 can be both
	for(int i=0; i<spiral.size(); i++){
		pii up = spiral[i][0], right = spiral[i][1], down = spiral[i][2], left = spiral[i][3]; 
		if(i+1<spiral.size() and spiral[i+1][0].y < left.y){ // 2 1 0 3
			type.push_back(1);
		}
		else if(i+1<spiral.size() and spiral[i+1][2].y > left.y) { // 0 1 2 3
			type.push_back(0);
		}
		else type.push_back(2);
		if(type.back() != 2){
			int i = type.size() - 2;
			while(i >= 0 and type[i] == 2){
				type[i] = type[i+1];
				i--;
			}
		}
	}
	for(int i=0; i<spiral.size(); i++){
		pii up = spiral[i][0], right = spiral[i][1], down = spiral[i][2], left = spiral[i][3]; 
		if(type[i] == 1){ // 2 1 0 3
			ans.push_back({(ans.empty() ? 0 : ans.back().x), down.y});
			ans.push_back({right.x, down.y});
			ans.push_back({right.x, up.y});
			ans.push_back({left.x, up.y});
		}
		else{ // 0 1 2 3
			ans.push_back({(ans.empty() ? 0 : ans.back().x), up.y});
			ans.push_back({right.x, up.y});
			ans.push_back({right.x, down.y});
			ans.push_back({left.x, down.y});
		}
	}
	if(!type.empty()){ // prepare for diagonals
		if(type.back() == 1) ans.push_back({ans.back().x, 0});
		else ans.push_back({ans.back().x, 1000000001});
	}
	// cout << "diag0:\n";
	// for(pii p : diag[0]) cout << p.x << " " << p.y << endl;
	// cout << "diag1:\n";
	// for(pii p : diag[1]) cout << p.x << " " << p.y << endl;
	// cout << ans.back().y << endl;
	if(ans.empty() or ans.back().y == 0){ // go left first, then up, right, up, right, ....
		// SOLVING DIAG 1
		if(!diag[1].empty()) ans.push_back({diag[1].back().x, (ans.empty() ? 0 : ans.back().y)});
		int dir = 1;
		for(int i=diag[1].size()-2; i>=0; i--){ 
			//dir 1 == up, dir 0 == right
			if(dir) ans.push_back({ans.back().x, diag[1][i].y});
			else ans.push_back({diag[1][i].x, ans.back().y});
			dir^=1;
		}
		if(dir == 1){
			ans.push_back({(ans.empty() ? 0 : ans.back().x), 1000000001});
			// SOLVING DIAG 0
			// go left first, then down, right, down, right, ....
			if(!diag[0].empty()) ans.push_back({diag[0][0].x, ans.back().y});
			int dir = 1;
			for(int i=1; i<diag[0].size(); i++){ 
				//dir 1 == down, dir 0 == right
				if(dir) ans.push_back({ans.back().x, diag[0][i].y});
				else ans.push_back({diag[0][i].x, ans.back().y});
				dir^=1;
			}
			if(dir) ans.push_back({ans.back().x, 0});
			else ans.push_back({1000000001, ans.back().y});
		}
		else{
			ans.push_back({1000000001, (ans.empty() ? 0 : ans.back().y)});
			// SOLVING DIAG 0
			// go down first, then left, up, left, up ...
			if(!diag[0].empty()) ans.push_back({ans.back().x, diag[0].back().y});
			int dir = 1;
			for(int i=diag[0].size()-2; i>=0; i--){ 
				//dir 1 == left, dir 0 == up
				if(dir) ans.push_back({diag[0][i].x, ans.back().y});
				else ans.push_back({ans.back().x, diag[0][i].y});
				dir^=1;
			}
			if(dir) ans.push_back({0, ans.back().y});
			else ans.push_back({ans.back().x, 1000000001});
		}
	}
	else{ // 1000000001
		// SOLVING DIAG 0

		// go left first, then down, right, down, right...
		// SAME CODE AS DIR == 1 OF PREVIOUS IF
		if(!diag[0].empty()) ans.push_back({diag[0][0].x, ans.back().y});
		int dir = 1;
		for(int i=1; i<diag[0].size(); i++){ 
			//dir 1 == down, dir 0 == right
			if(dir) ans.push_back({ans.back().x, diag[0][i].y});
			else ans.push_back({diag[0][i].x, ans.back().y});
			dir^=1;
		}
		if(dir){
			ans.push_back({ans.back().x, 0});
			// SOLVING DIAG 1
			// go up, right, up right, ...
			if(!diag[1].empty()) ans.push_back({diag[1].back().x, ans.back().y});
			int dir = 1;
			for(int i=diag[1].size()-2; i>=0; i--){ 
				//dir 1 == up, dir 0 == right
				if(dir) ans.push_back({ans.back().x, diag[1][i].y});
				else ans.push_back({diag[1][i].x, ans.back().y});
				dir^=1;
			}
			if(dir == 1) ans.push_back({ans.back().x, 1000000001});
			else ans.push_back({1000000001, ans.back().y});
		}
		else{
			ans.push_back({1000000001, ans.back().y});
			// SOLVING DIAG 1
			// go up, then left, down, left, down
			if(!diag[1].empty()) ans.push_back({ans.back().x, diag[1][0].y});
			int dir = 1;
			for(int i=1; i<diag[1].size(); i++){ 
				//dir 1 == left, dir 0 == down
				if(dir) ans.push_back({diag[1][i].x, ans.back().y});
				else ans.push_back({ans.back().x, diag[1][i].y});
				dir^=1;
			}
			if(dir) ans.push_back({0, ans.back().y});
			else ans.push_back({ans.back().x, 0});
		}
	}
	cout << ans.size() << "\n";
	for(pii p : ans) cout << p.x << " " << p.y << "\n";
}
