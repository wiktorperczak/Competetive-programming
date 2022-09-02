#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
vector<bool> isPrime;
vector<ll> factors;

void sieve() {
    factors[1] = 1;
    for(ll i = 2; i*i <= n; i++) {
        if(isPrime[i]) {
            factors[i] = i;
            for(ll j = i*i; j <= n; j += i) {
                isPrime[j] = false;
                if(factors[j] < 0) factors[j] = i;
            }
        }
    }
    for(ll i = 2; i <= n; i++) {
        if(isPrime[i])
            factors[i] = i;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    constexpr ll P = 29, M = 1e9 + 7;
    ll q;
    string s;
    cin >> n >> s >> q;
    isPrime.resize(n+1, true);
    factors.resize(n+1, -1);
    sieve();
    
    vector<ll> pref(n+1, 0);
    vector<ll> pPow(n);
    pPow[0] = 1;
    for(ll i = 1; i < n; i++)
        pPow[i] = (pPow[i-1] * P) % M;
    for(ll i = 1; i <= n; i++)
        pref[i] = (pref[i-1] + (s[i-1] - 'a' + 1) * pPow[i-1]) % M;

    ll a, b, hash, hash1, l, m, k;
    while(q--) {
        cin >> a >> b;
        l = 1; 
        m = b-a+1;
        while(l != m) {
            k = factors[m/l];
            hash = (pPow[a+m/k-1] * ((pref[b-m/k] - pref[a-1] + M) % M)) % M;
            hash1 = (pPow[a-1] * ((pref[b] - pref[a+m/k-1] + M) % M)) % M;
            if(hash == hash1) {
                m /= k;
                b = a + (b-a+1)/k - 1;
                continue;
            }
            while((m/l) % k == 0)
                l *= k;
        }
        cout << m << "\n";
    }
    return 0;
}