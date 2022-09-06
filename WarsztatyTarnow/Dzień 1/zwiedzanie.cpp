#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> parent, len;
ll ans = 0;
vector<vector<pair<ll, ll>>> minTree;

ll Find(ll v) {
    if(parent[v] == v)
        return v;
    return parent[v] = Find(parent[v]);
}

void Union(ll a, ll b, ll weight) {
    a = Find(a);
    b = Find(b);
    if(a == b) return;
    ans += 2 * len[a] * len[b] * weight;
    if(len[a] > len[b]) swap(a, b);
    parent[a] = parent[b];
    len[b] += len[a];
}

struct Edge {
    ll a, b, w;
    bool operator<(Edge const& e) {
        return w < e.w;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    parent.resize(n+1);
    len.resize(n+1, 1);
    minTree.resize(n+1);
    
    for(ll i = 0; i < m; i++)
        cin >> edges[i].a >> edges[i].b >> edges[i].w;
    for(ll i = 0; i <= n; i++) parent[i] = i;
    sort(edges.begin(), edges.end());

    for(Edge e : edges) {
        if(Find(e.a) != Find(e.b)) {
            Union(e.a, e.b, e.w);
            minTree[e.a].push_back({e.b, e.w});
            minTree[e.b].push_back({e.a, e.w});
        }
    }
    cout << ans << "\n";
    return 0;
}