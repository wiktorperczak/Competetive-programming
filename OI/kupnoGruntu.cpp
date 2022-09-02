#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define st first
#define nd second

ll area(vector<vector<ll>> &sum, ll x, ll y, ll X, ll Y) {
    return sum[Y][X] + sum[y][x] - sum[Y][x] - sum[y][X];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, k;
    cin >> k >> n;
    vector<vector<ll>> sum(n, vector<ll> (n, 0));
    vector<vector<bool>> close(n, vector<bool> (n, false));
    for(ll i = 0; i < n; i++) {
        ll all = 0;
        for(ll j = 0; j < n; j++) {
            ll x; cin >> x;
            if(x > 2*k) close[i][j] = true;
            all += x;
            if(i == 0) sum[i][j] = all;
            else sum[i][j] = sum[i-1][j] + all;
        }
    }

    for(auto i : close) {
        for(auto j : i)
            cout << j << " ";
        cout << "\n";
    }

    ll x1, y1, x2, y2; 
    ll Y = -1, X, maxi = 0;
    for(ll y = 0; y < n; y++) {
        stack<pair<ll, ll>> s;
        for(ll x = 0; x < n; x++) {
            if(close[y][x]) Y = y;
            X = x;
            while(!s.empty() && s.top().nd <= Y) {
                if(area(sum, s.top().st, s.top().nd, x-1, y) > maxi) {
                    maxi = area(sum, s.top().st, s.top().nd, x-1, y);
                    x1 = x; y1 = y; x2 = s.top().st; y2 = Y;
                }
                s.pop();
            }
            s.push({X, Y});
        }
    }
    cout << maxi << "\n";
    return 0;
}