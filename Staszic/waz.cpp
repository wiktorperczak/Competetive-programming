#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<ll>> v(n, vector<ll> (m)), dp(n, vector<ll> (m));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cin >> v[i][j];
    }

    dp[0][0] = v[0][0];
    for(int i = 1; i < n; i++)
        dp[i][0] = dp[i-1][0] + v[i][0];
    for(int i = 1; i < m; i++)
        dp[0][i] = dp[0][i-1] + v[0][i]; 

    for(int i = 1; i < n; i++) {
        for(int j = 1; j < m; j++)
            dp[i][j] = v[i][j] + max(dp[i][j-1], dp[i-1][j]);
    }

    cout << dp[n-1][m-1] << "\n";
    return 0;
}