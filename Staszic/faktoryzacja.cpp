#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    const int C = 1e6;
    vector<int> prime;
    vector<int> sieve(C + 1, 0);

    for(ll i = 2; i*i <= C; i++) {
        if(!sieve[i]) {
            for(ll k = i*i; k <= C; k += i)
                if(!sieve[k]) sieve[k] = i;
        }
    }

    int t, x;
    cin >> t;

    while(t--) {
        cin >> x;

        if(x == 1) {
            cout << "\n";
            continue;
        }

        while(sieve[x] > 0) {
            cout << sieve[x] << " ";
            x /= sieve[x];
        }
        cout << x << " " << "\n";
    }

    return 0;
}