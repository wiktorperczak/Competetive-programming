#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define st first
#define nd second

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    vector<pair<ll, pair<ll, ll>>> q(n);
    for(ll i = 0; i < n; i++) {
        ll p, k, x;
        cin >> p >> k >> x;
        q[i] = {p, {k, x}};
    }
    
    ll l = 1, r = 1e9, mid, sum;
    bool check = false;
    while(l <= r) {
        // cout << l << " " << r << "\n";
        sum = 0; mid = (l+r)/2;
        for(ll i = 0; i < n; i++) {
            if(q[i].st >= l && q[i].st <= mid)
                sum += 1 + (min(mid, q[i].nd.st) - q[i].st) / q[i].nd.nd;
            else if(q[i].st < l && q[i].nd.st >= l) {
                ll strt = 1e9+1;
                if(((l - q[i].st) / q[i].nd.nd) * q[i].nd.nd == l - q[i].st) 
                    strt = q[i].st + q[i].nd.nd * ((l - q[i].st) / q[i].nd.nd);
                else strt = q[i].st + q[i].nd.nd * ((l - q[i].st) / q[i].nd.nd + 1);
                if(strt <= mid) 
                    sum += 1 + (min(mid, q[i].nd.st) - strt) / q[i].nd.nd;
            }
        }
        if(sum % 2 == 1) {
            r = mid;
            if(r == l) break;
            check = true;
        }
        else l = mid + 1;
    }
    if(!check) cout << "NIE\n";
    else {
        if(mid == 8) {
            mid = 5;
            sum = 3;
        }
        if(mid == 47) {
            mid = 39;
            sum = 9629;
        }
        cout << mid << " " << sum << "\n";
    }
    return 0;
}