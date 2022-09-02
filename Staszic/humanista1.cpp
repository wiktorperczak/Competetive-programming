#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll C = (1 << 19);
vector<ll>a, tree(2 * C, 0);

void build(ll i, ll l, ll r) {
    if(l > r) return;
    if(l == r) {
        if(a.size() > l) tree[i] = a[l];
        return;
    }

    ll mid = (l + r) / 2;
    build(i * 2, l, mid);
    build(i * 2 + 1, mid + 1, r);
    tree[i] = (tree[i * 2] ^ tree[i * 2 + 1]);
}

void modify(ll i, ll l, ll r, ll x, ll v) {
    if(l == r) {
        tree[i] = v;
        return;
    }

    ll mid = (l + r) / 2;
    if(x <= mid) modify(i * 2, l, mid, x, v);
    else modify(i * 2 + 1, mid + 1, r, x, v);
    tree[i] = (tree[i * 2] ^ tree[i * 2 + 1]);
}

ll query(ll i, ll a, ll b, ll l, ll r) {
    if(l >= a && r <= b)
        return tree[i];

    ll mid = (l + r) / 2, ans = 0;
    if(a <= mid) ans = (ans ^ query(i * 2, a, b, l, mid));
    if(b > mid) ans = (ans ^ query(i * 2 + 1, a, b, mid + 1, r));
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cout.tie(0); cin.tie(0);

    ll n, q;
    cin >> n >> q;
    a.resize(n + 1);
    for(ll i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, C);
    //for(ll i = 0; i <= 2 * C; i++)
    //    cout << tree[i] << " ";
    //cout << "\n";

    while(q--) {
        string s;
        ll b, c;
        cin >> s >> b >> c;

        if(s == "zamien") {
            modify(1, 1, C, b, a[c]);
            modify(1, 1, C, c, a[b]);
        } else
            cout << query(1, b, c, 1, C) << "\n";
    }

    return 0;
}