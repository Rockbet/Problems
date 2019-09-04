// OBI 2013 - Cachecol da Vovó Vitória
// Leonardo Paes

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1e9+7;

template<int n, int m>
struct Matrix{
    ll v[n][m];

    static Matrix ones(){
        Matrix<n, m> ans{};
        for(int i=0; i<n; i++)
            ans.v[i][i]=1;
        return ans;
    }
};

template<int n, int m, int p>
Matrix<n, p> operator*(Matrix<n, m> const& a, Matrix<m, p> const& b){
    Matrix<n, p> ans{};
    for(int i=0; i<n; i++)
        for(int j=0; j<p; j++)
            for(int k=0; k<m; k++)
                ans.v[i][j] = (ans.v[i][j] + a.v[i][k] * b.v[k][j])%mod;
    return ans;
}

template<int n>
Matrix<n, n> power(Matrix<n, n> a, ll b){
    Matrix<n, n> ans = Matrix<n, n>::ones();
    while(b){
        if(b&1)ans = ans*a;
        a = a*a;
        b = b>>1;
    }
    return ans;
}

int main(){
    ll n;

    cin >> n;

    Matrix<2, 1> base = {12, 54};

    Matrix<2, 2> exp = {0, 1,
                       -2, 5};

    Matrix<2, 1> ans = power(exp, n-1)*base;

    cout << ans.v[0][0] << "\n";
}
