#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll C = (1 << 19);
vector<ll> a(2 * C, 0), tree(2 * C, 0);

void build(ll i, ll l, ll r) {
    if(l > r)
        return;
    if(l == r) {
        tree[i] = a[l];
        return;
    }

    ll mid = (l + r) / 2;
    build(i * 2, l, mid);
    build(i * 2 + 1, mid + 1, r);

    tree[i] = (tree[i * 2] ^ tree[i * 2 + 1]);
}

void modify(ll i, ll l, ll r, ll v, ll x) {
    if(l == r) {
        tree[i] = v;
        return;
    }

    ll mid = (l + r) / 2;
    if(x <= mid) modify(i * 2, l, mid, v, x);
    else modify(i * 2 + 1, mid + 1, r, v, x);

    tree[i] = (tree[i * 2] ^ tree[i * 2 + 1]);
}

ll query(ll i, ll l, ll r, ll a, ll b) {
    if(l >= a && r <= b)
        return tree[i];

    ll mid = (l + r) / 2, ans = 0;
    if(a <= mid) ans = (ans ^ query(i * 2, l, mid, a, b));
    if(b > mid) ans = (ans ^ query(i * 2 + 1, mid + 1, r, a, b));

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, q;
    cin >> n >> q;
    for(ll i = 0; i < n; i++)
        cin >> a[i];

    build(1, 0, C - 1);
    string s;
    ll x, y;

    while(q--) {
        cin >> s >> x >> y;
        if(s == "czytaj") {
            cout << query(1, 1, C, x, y) << "\n";
            //for(ll i = 0; i < 2 * C; i++)
            //    cout << tree[i] << " ";
        }
        else {
            modify(1, 1, C, a[y - 1], x);
            modify(1, 1, C, a[x - 1], y);
        }
    }

    return 0;
}