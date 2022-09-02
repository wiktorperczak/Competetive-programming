#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, q, ans = 0;
    cin >> n >> m >> q;
    vector<vector<bool>> obs(m+1, vector<bool> (n+1, false));
    while(q--) {
        int x, y;
        cin >> x >> y;
        obs[y][x] = true;
    }
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= m-i+1; k++) {
                for(int l = 1; l <= n-j+1; l++) {
                    bool h = true;
                    for(int o = k; o < k+i; o++) {
                        for(int p = l; p < l+j; p++) {
                            if(obs[o][p]) {
                                h = false;
                                break;
                            }
                        }
                        if(!h) break;
                    }
                    if(h) ans++;
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}