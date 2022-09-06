#include <bits/stdc++.h>
using namespace std;

struct triple {
    bool w = false, b = false, g = false;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q, ans = 0;
    cin >> n >> q;
    vector<triple> v(n+1);
    while(q--) {
        int t, l, r;
        char c;
        cin >> t >> l >> r >> c;
        if(c == 'W') {
            for(int i = l; i <= r; i++) {
                if(t == 0) {
                    v[i].w = false;
                    if(v[i].g) {
                        v[i].g = false;
                        ans--;
                    }
                }
                else {
                    v[i].w = true;
                    if(!v[i].g && v[i].b) {
                        v[i].g = true;
                        ans++;
                    }
                }
            }
        }
        else if(c == 'B') {
            for(int i = l; i <= r; i++) {
                if(t == 0) {
                    v[i].b = false;
                    if(v[i].g) {
                        v[i].g = false;
                        ans--;
                    }
                }
                else {
                    v[i].b = true;
                    if(!v[i].g && v[i].w) {
                        v[i].g = true;
                        ans++;
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}