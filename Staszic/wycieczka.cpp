#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<ll> x(n - 1);
    for(int i = 0; i < n - 1; i++)
        cin >> x[i];

    ll l = 1, r = 1e11, mid;
    ll ans = r, ile, sum;
    while(l <= r) {
        mid = (l + r) / 2;
        ile = n - k; sum = 0;

        for(int i = 0; i < n - 1; i++) {
            if(x[i] > mid) {
                ile = 1;
                break;
            } else if(ile > 0 && sum + x[i] <= mid)
                ile--, sum += x[i];
            else if(ile > 0)
                sum = x[i];
        }

        if(ile == 0) {
            ans = mid;
            r = mid - 1;
        } else
            l = mid + 1;
    }
    cout << ans;

    return 0;
}