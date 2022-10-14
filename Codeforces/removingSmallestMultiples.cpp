#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll t; cin >> t;
    while(t--) {
        ll n, cost = 0; cin >> n;
        string s; cin >> s;

        for(ll i = 1; i <= n; i++) {
            for(ll j = i; j <= n; j += i) {
                if(s[j-1] == '1') break;
                else if(s[j-1] == '0') {
                    cost += i;
                    s[j-1] = '2';
                }
            }
        }

        cout << cost << "\n";
    }

    return 0;
}