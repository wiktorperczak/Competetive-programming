#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);

    ll n, k;
    cin >> n >> k;
    ll lg = ceil(log2(n));
    vector<ll> a(3*n);
    vector<vector<ll>> nxt(3*n, vector<ll> (lg+1, -1));
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i+n] = a[i];
        a[i+2*n] = a[i];
    }
    ll sum = 0, l = 0;
    for(int r = 0; l < 2*n && r < 3*n; r++) {
        if(r-l > n) {
            nxt[l][0] = r;
            l = r-n;
        }
        while(sum + a[r] > k) {
            nxt[l][0] = r;
            sum -= a[l];
            l++;
        }
        sum += a[r];
    }

    for(int i = 1; i <= lg; i++) {
        for(int j = 0; j < n; j++) {
            if(nxt[j][i-1] == -1 || nxt[nxt[j][i-1]][i-1] > j + n) nxt[j][i] = -1;
            else nxt[j][i] = nxt[nxt[j][i-1]][i-1];
        }
        for(int j = n; j < 2*n; j++) {
            if(nxt[j-n][i] == -1) nxt[j][i] = -1;
            else nxt[j][i] = nxt[j-n][i] + n;
        }
    }
/* 
    for(int i = 0; i < 2*n; i++) {
        cout << i << ": ";
        for(auto j : nxt[i])
            cout << j << " ";
        cout << "\n";
    } */

    ll ans = LONG_LONG_MAX;
    for(int i = 0; i < n; i++) {
        ll res = 0, pwr = lg, id = i;
        bool h = false;
        while(pwr >= 0) {
            if(nxt[id][pwr] == -1 || nxt[id][pwr] > i+n)
                pwr--;
            else if(nxt[id][pwr] == i+n) {
                res += (1 << pwr);
                h = true;
                break;
            }
            else {
                res += (1 << pwr);
                id = nxt[id][pwr];
                pwr--;
            }
        }
        if(!h) res++;
        ans = min(ans, res);
    }
    cout << ans << "\n";
    return 0;
}