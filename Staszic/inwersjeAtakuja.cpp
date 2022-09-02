#include<bits/stdc++.h>
using namespace std;
typedef long long  ll;

const int C = (1 << 16);
vector<int> a, tree( 2 * C, 0);

void add(int i, int l, int r, int x) {
    if(l == r) {
        tree[i]++;
        return;
    }

    int mid = (l + r) / 2;
    if(mid >= x) add(i * 2, l, mid, x);
    else add(i * 2 + 1, mid + 1, r, x);
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

int query(int i, int l, int r, int a, int b) {
    if(l >= a && r <= b)
        return tree[i];

    int mid = (l + r) / 2, ans = 0;
    if(mid >= a) ans += query(i * 2, l, mid, a, b);
    if(mid < b) ans += query(i * 2 + 1, mid + 1, r, a, b);
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> b(n);
    a.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i - 1] = a[i];
    }

    sort(b.begin(), b.end());
    int k = 0;
    for(int i = 1; i < n; i++) {
        if(b[i - k] == b[i - 1 - k]) {
            b.erase(b.begin()+(i - 1 - k));
            k++;
        }
    }

    int res = 0;
    for(int i = 1; i <= n; i++) {
        int num, l = 0, r = (int)b.size()-1, mid;
        while(l <= r) {
            mid = (l + r) / 2;
            if(b[mid] < a[i])
                l = mid + 1;
            else if(b[mid] > a[i])
                r = mid - 1;
            else {
                num = mid;
                break;
            }
        }

        res += query(1, 1, C, num + 2, (int) b.size());
        add(1, 1, C, num + 1);
    }
    cout << res;

    return 0;
}