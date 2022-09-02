#include <bits/stdc++.h>
using namespace std;

vector<int> par, len;

int Find(int v) {
    if(v == par[v]) return v;
    return par[v] = Find(par[v]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return;
    if(len[a] > len[b]) swap(a, b);
    len[b] += len[a];
    par[a] = par[b];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    set<pair<int, int>> walls;
    vector<pair<int, int>> queries(k);
    for(int i = 0; i < k; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int v1 = n * (b-1) + a, v2 = n * (d-1) + c;
        queries[i] = {v1, v2};
        if(v1 > v2) swap(v1, v2);
        walls.insert({v1, v2});
    }
    len.assign(n*m+1, 1);
    par.resize(n*m+1);
    for(int i = 1; i <= n*m; i++) par[i] = i;
    for(int i = 1; i <= n*m; i++) {
        if(i > n && walls.find({i-n, i}) == walls.end()) Union(i-n, i);
        if(i % n != 1 && walls.find({i-1, i}) == walls.end()) Union(i-1, i);
        if(i % n != 0 && walls.find({i, i+1}) == walls.end()) Union(i, i+1);
        if(i <= n*m-n && walls.find({i, i+n}) == walls.end()) Union(i, i+n);
    }
    vector<bool> ans(k, false);
    reverse(queries.begin(), queries.end());
    for(int i = 0; i < k; i++) {
        int a = Find(queries[i].first), b = Find(queries[i].second);
        if(a == b) ans[i] = true;
        else Union(a, b);
    }
    for(int i = k-1; i >= 0; i--) cout << (ans[i] ? "TAK\n" : "NIE\n");
    return 0;
}