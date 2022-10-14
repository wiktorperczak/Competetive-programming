#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> g(n, vector<int> (m));
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> g[i][j];
            }
        }

        vector<vector<pair<int, int>>> ans(n, vector<pair<int, int>> (m, {0, 0}));
        ans[0][0] = {g[0][0], g[0][0]};
        for(int i = 1; i < n; i++) {
            ans[i][0] = ans[i-1][0];
            ans[i][0].st += g[i][0];
            ans[i][0].nd += g[i][0];
        }
        for(int i = 1; i < m; i++) {
            ans[0][i] = ans[0][i-1];
            ans[0][i].st += g[0][i];
            ans[0][i].nd += g[0][i];
        }

        for(int i = 1; i < n; i++) {
            for(int j = 1; j < m; j++) {
                ans[i][j].st = min(ans[i-1][j].st, ans[i][j-1].st) + g[i][j];
                ans[i][j].nd = max(ans[i-1][j].nd, ans[i][j-1].nd) + g[i][j];
            }
        }

        // for(auto i : ans) {
        //     for(auto j : i)
        //         cout << j.st << "," << j.nd << " ";
        //     cout << "\n";
        // }

        if(ans[n-1][m-1].st <= 0 && ans[n-1][m-1].nd >= 0 && ans[n-1][m-1].nd%2 == 0) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}