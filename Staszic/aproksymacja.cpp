#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<double> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];

    double l = 0, r = 1e6, mid, ans = 0, last;
    bool cor = true;

    while(l <= r) {
        mid = (floor(l+r))/2;
        last = -1e6;

        for(int i = 0; i < n; i++) {
            if(last - mid <= a[i])
                last = max(last, a[i] - mid);
            else {
                cor = false;
                break;
            }
        }

        if(cor == true) {
            r = mid - 0.5;
            ans = mid;
        }
        else {
            l = mid + 0.5;
            cor = true;
        }
    }
    cout << fixed << setprecision(3) << ans << "\n";
    last = -1e6;
    for(int i = 0; i < n; i++) {
        last = max(a[i] - ans, last);
        cout << last << "\n";
    }
    return 0;
}