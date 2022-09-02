#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define st first
#define nd second

void brute(ll n, ll m, ll q) {
    vector<pair<int, int>> seg(m+1);
    vector<set<int>> a(n+1);
    for(int i = 1; i <= m; i++) cin >> seg[i].first >> seg[i].second;
    while(q--) {
        char c;
        cin >> c;
        int x, l, r;
        if(c == '?') {
            cin >> l >> r;
            bool h = (a[l] == a[r]);
            cout << (h ? "TAK\n" : "NIE\n");
        }
        else if(c == '+') {
            cin >> x;
            for(int i = seg[x].first; i <= seg[x].second; i++) a[i].insert(x);
        }
        else {
            cin >> x;
            for(int i = seg[x].first; i <= seg[x].second; i++) a[i].erase(x);
        }
    }
}

constexpr ll M1 = 1e9 + 7, M2 = 1e9 + 696969, p1 = 11, p2 = 19;
vector<ll> pow1, pow2;
constexpr ll H = 18, base = (1 << H);
vector<pair<ll, ll>> tree(2*base, {0, 0});

void powers(ll m) {
    pow1[0] = 1;
    pow2[0] = 1;
    for(ll i = 1; i <= m; i++) {
        pow1[i] = (p1 * pow1[i-1]) % M1;
        pow2[i] = (p2 * pow2[i-1]) % M2;
    }
}

void update(ll v, ll a, ll b, ll s, ll e, ll x, ll sig, ll tim) {
    if(s > b || e < a) return;
    else if(s >= a && e <= b) {
        tree[v].st = (tree[v].st + sig * pow1[x] + M1) % M1;
        tree[v].nd = (tree[v].nd + sig * pow2[x] + M2) % M2;
    }
    else {
        ll l = v*2, r = v*2+1, mid = (s+e)/2;
        update(l, a, b, s, mid, x, sig, tim);
        update(r, a, b, mid+1, e, x, sig, tim);
    }
}

pair<ll, ll> query(ll v) {
    pair<ll, ll> ans = {0, 0};
    while(v >= 1) {
        ans.st = (ans.st + tree[v].st) % M1;
        ans.nd = (ans.nd + tree[v].nd) % M2;
        v /= 2;
    }
    return ans;
}

void solve(ll n, ll m, ll q) {
    vector<pair<ll, ll>> seg(m+1);
    for(ll i = 1; i <= m; i++) cin >> seg[i].first >> seg[i].second;
    pow1.resize(m+1);
    pow2.resize(m+1);
    powers(m);

    for(ll i = q; i >= 1; i--) {
        char c;
        cin >> c;
        ll x, l, r;
        if(c == '?') {
            cin >> l >> r;
            pair<ll, ll> ans1 = query(base+l-1);
            pair<ll, ll> ans2 = query(base+r-1);
            if(ans1.st == ans2.st && ans1.nd == ans2.nd) cout << "TAK\n";
            else cout << "NIE\n";
        }
        else if(c == '+') {
            cin >> x;
            update(1, seg[x].st, seg[x].nd, 1, base, x, 1, i);
        }
        else if(c == '-') {
            cin >> x;
            update(1, seg[x].st, seg[x].nd, 1, base, x, -1, i);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, m, q;
    cin >> n >> m >> q;
    if(n <= 100 && m <= 100 && q <= 100) brute(n, m, q);
    else solve(n, m, q);
    return 0;
}