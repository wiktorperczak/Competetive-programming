#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    constexpr int inf = INT_MAX - 10;
    int n, k;
    cin >> n;
    vector<int> val(n+1), num(n+1);
    for(int i = 1; i <= n; i++) cin >> val[i];
    for(int i = 1; i <= n; i++) cin >> num[i];
    cin >> k;

    vector<vector<pair<int, int>>> dp(n+1, vector<pair<int, int>> (k+1, {inf, 0}));
    for(int i = 0; i <= n; i++) dp[i][0].st = 0;
    for(int i = 1; i <= n; i++) {
        int c = val[i];
        for(int j = 1; j <= k; j++) {
            if(dp[i-1][j].st != inf) {
                dp[i][j].st = dp[i-1][j].st;
                dp[i][j].nd = 0;
            }
            if(dp[i][j].st != inf && c+j <= k && num[i] > dp[i][j].nd) {
                dp[i][j+c].st = dp[i][j].st + 1;
                dp[i][j+c].nd = dp[i][j].nd + 1;
            }
        }
        for(int j = k; j >= c; j--) {
            if(num[i] > dp[i][j-c].nd && dp[i][j-c].st + 1 < dp[i][j].st) {
                dp[i][j].st = dp[i][j-c].st + 1;
                dp[i][j].nd = dp[i][j-c].nd + 1;
            }
        }
        for(int j = c; j <= k; j++) {
            if(num[i] > dp[i][j-c].nd && dp[i][j-c].st + 1 < dp[i-1][j].st) {
                dp[i][j].st = dp[i][j-c].st + 1;
                dp[i][j].nd = dp[i][j-c].nd + 1;
            }
        }
    }
    vector<int> ans(n+1, 0);
    int x = k, y = n;
    while(y > 0) {
        ans[y] += dp[y][x].nd;
        x -= (dp[y][x].nd * val[y]);
        y--;
    }
    cout << dp[n][k].st << "\n";
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
    return 0;
}