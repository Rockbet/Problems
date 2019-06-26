// The idead I used to solve this problem is Dynamic Programming. I used a dp[position][number], it saves the winner if
// whe are the animal at position == position and with this animal being able to choose a number from number+1 to number+1+k.
// The base case is when number == m, because we know that the other animal type will win ( animal[i]^1 ).
// To solve the dp, we just have to know if all the possible answers from the next animal in the range (number+1 -> number+k+1)
// are all the same, if they are, we have no option but choosing them. Otherwise, we will have at least one answer 0 and one 1.
// In this case, we know witch number to choose to have our animal as the winner, so the answer is my animal[number].
// Inside the code I wrote more comments to indicate the answers to each DP state.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3 + 10;

int vet[maxn], dp[maxn][maxn];

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int n, m, k;

    cin >> n >> m >> k;

    m--;

    for(int i=0; i<n; i++){
        cin >> vet[i];
        dp[i][m] = vet[i]^1;
    }

    for(int j=m-1; j>=0; j--){
        for(int i=0; i<n; i++){
            int possible_answers = dp[(i+1)%n][j+1];
            int length = m-j;
            if(j+k<m){
                possible_answers -= dp[(i+1)%n][j+k+1];
                length = k;
            }
            // if all of the possible answers are equal we have no choice
            if(possible_answers==0) dp[i][j] = dp[i][j+1];
            else if(possible_answers==length) dp[i][j] = 1 + dp[i][j+1];
            // otherwise it is possible to choose wich one we prefer
            else dp[i][j] = vet[i] + dp[i][j+1];
            // we are incrementing our dp[i][j] with dp[i][j+1] to maintain
            // a sufix of all the previous answers, to get the actual dp[i][j]
            // we just need to use dp[i][j] - dp[i][j+1]
        }
    }

    for(int i=0; i<n; i++){
        cout << dp[i][0] - dp[i][1] << " ";
    }
	cout << "\n";

    return 0;
}
