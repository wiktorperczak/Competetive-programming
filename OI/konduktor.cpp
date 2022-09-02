#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> in(n, vector<int> (n, 0));
    for(int i = 1; i < n; i++) {
        for(int j = i; j < n; j++) 
            cin >> in[i][j];
    }
    vector<vector<int>> sum(n, vector<int> (n, 0));
    sum[1][n-1] = in[1][n-1];
    for(int i = n-2; i > 0; i--) sum[1][i] = sum[1][i+1] + in[1][i];
    for(int i = 2; i < n; i++) sum[i][n-1] = sum[i-1][n-1] + in[i][n-1]; 
    for(int i = 2; i < n; i++) {
        for(int j = n-2; j > 0; j--)
            sum[i][j] = in[i][j] + sum[i-1][j] + sum[i][j+1] - sum[i-1][j+1];
    }

    vector<vector<pair<int, int>>> dp(k+1, vector<pair<int, int>> (n, {0, 0}));
    vector<vector<int>> anc(k+1, vector<int> (n, 0));
    for(int i = 1; i <= k; i++) {
        for(int j = 1; j < n; j++) {
            int val =  0, a, b; 
            for(int m = 1; m <= j; m++) {
                a = dp[i-1][j-m].st;
                b = dp[i-1][j-m].nd;
                if(a + sum[j][j] - sum[b][j] > val) {
                    val = a + sum[j][j] - sum[b][j];
                    anc[i][j] = j-m;
                }
            }
            if(val >= max(dp[i-1][j].st, dp[i][j-1].st)) dp[i][j] = {val, j};
            else if(dp[i-1][j].st >= max(val, dp[i][j-1].st)) {
                dp[i][j] = dp[i-1][j];
                anc[i][j] = anc[i-1][j];
            }
            else {
                dp[i][j] = dp[i][j-1];
                anc[i][j] = anc[i][j-1];
            }
        }
    }
    
    vector<int> ans;
    int x = n-1, y = k;
    while(y != 0) {
        ans.push_back(dp[y][x].nd);
        x = anc[y][x];
        y--;
    }
    reverse(ans.begin(), ans.end());
    for(auto i : ans) cout << i << " ";
    cout << "\n";
    return 0;
}