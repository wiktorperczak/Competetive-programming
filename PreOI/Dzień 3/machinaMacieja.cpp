#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k, l;
    cin >> n >> m >> k >> l;
    int l1 = log2(k), l2 = log2(l);
    vector<vector<vector<vector<int>>>> sparse(l1+1, vector<vector<vector<int>>> (l2+1, vector<vector<int>> (n, vector<int> (m))));
    vector<vector<int>> v(n+1, vector<int> (m+1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++)
            cin >> v[i][j];
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            sparse[0][0][i][j] = v[i+1][j+1];
        for(int o = 1; o <= l2; o++) {
            for(int p = 0; p + (1 << o) <= m; p++)
                sparse[0][o][i][p] = min(sparse[0][o-1][i][p], sparse[0][o-1][i][p + (1 << (o-1))]);
        }
    }
    for(int i = 1; i <= l1; i++) {
        for(int j = 0; j + (1 << i) <= n; j++) {
            for(int o = 0; o <= l2; o++) {
                for(int p = 0; p + (1 << o) <= m; p++)
                    sparse[i][o][j][p] = min(sparse[i-1][o][j][p], sparse[i-1][o][j + (1 << (i-1))][p]);
            }
        }
    }

    int min1, min2, x2, y2;
    for(int y1 = 0; y1 <= n-k; y1++) {
        for(int x1 = 0; x1 <= m-l; x1++) {
            y2 = y1 + k - 1;
            x2 = x1 + l - 1;
            min1 = min(sparse[l1][l2][y1][x1], sparse[l1][l2][y2+1 - (1 << l1)][x1]);
            min2 = min(sparse[l1][l2][y1][x2+1 - (1 << l2)], sparse[l1][l2][y2+1 - (1 << l1)][x2+1 - (1 << l2)]);
            cout << min(min1, min2) << " ";
        }
        cout << "\n";
    }
    return 0;
}