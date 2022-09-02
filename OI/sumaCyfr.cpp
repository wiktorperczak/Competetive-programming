#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); // cout.tie(0);

    ll s, m, q;
    cin >> s >> m >> q;
    vector<vector<ll>> dp(200, vector<ll> (s+1, 0));
    for(ll i = 0; i <= min((ll)9, s); i++) dp[0][i] = 1;
    for(ll i = 1; i < 200; i++) {
        for(ll j = 0; j <= s; j++) {
            for(ll k = 0; k <= min((ll)9, j); k++)
                dp[i][j] += dp[i-1][j-k];
        }
    }
    while(q--) {
        ll k, sum = 0;
        cin >> k;
        for(auto i : dp[199]) sum += i;
        if(k > s) {
            cout << "NIE\n";
            continue;
        }
        vector<ll> ans;
        ll used = 0;
        for(ll i = 199; i > 0; i--) {
            for(ll j = 0; j <= 9; j++) {
                ll num = dp[i-1][s-j-used];
                // if(i == 1) cout<< num << " " << s-used << "\n";
                if(num >= k) {
                    ans.push_back(j);
                    used += j;
                    break;
                }
                else k -= num;
            }
        }
        ans.push_back(s-used);
        bool zero = false;
        for(ll i = 0; i < 200; i++) {
            if(ans[i] != 0) {
                zero = true;
                cout << ans[i];
            }
            else if(zero) cout << ans[i] << " ";
        }
        cout << "\n";
    }
    /* for(ll i = 0; i < 4; i++) {
        for(ll j = 0; j <= s; j++)
            cout << dp[i][j] << " ";
        cout << "\n";
    } */
    return 0;
}