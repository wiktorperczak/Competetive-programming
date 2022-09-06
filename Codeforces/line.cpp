#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll t; cin>> t;
    while(t--) {
        ll n, start = 0; cin >> n;
        ll k = n;
        vector<char> c(n);
        for(ll i = 0; i < n; i++) {
            cin >> c[i];
            if(c[i] == 'L') start += i;
            else start += n-1-i;
        }

        vector<ll> ans(k, start);
        for(ll i = 0; i < (n+1)/2; i++) {
            if(k > 0 && c[i] == 'L') {
                start -= i;
                start += n-i-1;
                ans[n-k] = start;
                k--;
            }
            if(k > 0 && c[n-i-1] == 'R') {
                start -= i;
                start += n-i-1;
                ans[n-k] = start;
                k--;
            }
        }

        for(ll i = 1; i < n; i++)
            ans[i] = max(ans[i], ans[i-1]);
        for(auto i : ans) cout << i << " ";
        cout << "\n";
    }
    return 0;
}