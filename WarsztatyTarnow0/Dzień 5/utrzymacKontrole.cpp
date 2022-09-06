#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, ans;
    bool check = false;
    cin >> n >> m;
    vector<pair<int, int>> edg(m);
    vector<int> v;
    for(int i = 0; i < m; i++) cin >> edg[i].first >> edg[i].second;
    for(int i = 0; i < (1 << m); i++) {
        v.assign(n+1, 0);
        int x = i;
        for(int j = 0; j < m; j++) {
            if(x % 2 == 1) v[edg[j].first]++;
            else v[edg[j].second]++;
            x /= 2;
        }
        bool h = true;
        for(int j = 1; j <= n; j++) {
            if(v[j] % 2 != 0) {
                h = false;
                break;
            }
        }
        if(h) {
            check = true;
            ans = i;
            break;
        }
    }
    if(check) {
        for(int i = 0; i < m; i++) {
            if(ans % 2 == 1) cout << edg[i].first << " " << edg[i].second << "\n";
            else cout << edg[i].second << " " << edg[i].first << "\n";
            ans /= 2;
        }
    }
    else cout << "BRAK\n";
    return 0;
}