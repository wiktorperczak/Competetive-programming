#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> v(n);
    map<int, int> a;
    map<int, int>::iterator it, it1; 
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x;
        v[i] = x;
        it = a.find(x);
        if(it != a.end()) {
            y = it -> second;
            a.erase(it);
            a[x] = y+1;
        }
        else a[x] = 1;
    }
    int ans = 0;
    sort(v.begin(), v.end());
    for(int i = n-1; i >= 0; i--) {
        it = a.find(v[i]);
        if(it != a.end()) {
            int x = 1, y;
            while(x <= v[i]) x *= 2;
            it1 = a.find(x - v[i]);
            if(it1 != a.end() && (x - v[i] != v[i] || (it1 -> second) > 1)) {
                ans++;
                y = (it1 -> second) - 1;
                a.erase(x - v[i]);
                if(y > 0) a[x - v[i]] = y;
                it = a.find(v[i]);
                y = (it -> second) - 1;
                a.erase(it);
                if(y > 0) a[v[i]] = y;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}