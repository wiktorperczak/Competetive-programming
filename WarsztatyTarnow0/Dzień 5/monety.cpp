#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> x(n+1);
    for(int i = 1; i <= n; i++) cin >> x[i];
    while(q--) {
        int l, r, ans = 0;
        cin >> l >> r;
        vector<int> seg(r-l+1);
        for(int i = 0; i < r-l+1; i++) seg[i] = x[i+l];
        sort(seg.begin(), seg.end());
        for(int i = 0; i < r-l+1; i++) {
            if(seg[i] <= ans+1) ans += seg[i];
            else break;
        }
        cout << ans+1 << "\n";
    }
    return 0;
}