#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while(t--) {
        int n, odd = 0; cin >> n;
        for(int i = 0; i < n; i++) {
            int a; cin >> a;
            if(abs(a)%2 == 1) odd++;
        }

        bool ans = true;
        if(n%2 == 0) {
            if(odd%2 == 0 && odd%4 != 0) ans = false;
        }
        else {
            if(odd%2 == 0 && odd%4 != 0) ans = false;
            else if((odd-1)%4 == 0) ans = false;
        }
        cout << (ans ? "Alice\n" : "Bob\n");
    }
    return 0;
}