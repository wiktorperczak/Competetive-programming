#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;
    int a, l, d, sq = sqrt(n);
    vector<int> ans(n+1, 0);
    vector<vector<int>> dis(sq+1, vector<int>(n+1, 0));
    while(k--) {
        cin >> a >> l >> d;
        if(d > sq) {
            for(int i = a; i <= min(n, a+(l-1)*d); i += d)
                ans[i]++;
        }
        else {
            dis[d][a]++;
            if(a+l*d <= n) dis[d][a+l*d]--;
        }
    }
    for(int i = 1; i <= sq; i++) {
        for(int j = 1; j <= i; j++) {
            int add = 0;
            for(int m = j; m <= n; m += i) {
                add += dis[i][m];
                ans[m] += add;
            }
        }
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    return 0;
}