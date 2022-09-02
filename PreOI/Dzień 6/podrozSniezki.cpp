#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define st first
#define nd second

constexpr ll inf = 1e18;
vector<vector<pair<ll, ll>>> graph;

ll dijkstra(ll z, ll d, ll n) {
    vector<ll> dis(2*n+1, inf);
    dis[z] = 0;
    set<pair<ll, ll>> mySet;
    mySet.insert({0, z});

    while(!mySet.empty()) {
        ll v = mySet.begin() -> nd;
        mySet.erase(mySet.begin());

        for(auto w : graph[v]) {
            ll to = w.st, weight = w.nd;
            if(dis[v] + weight < dis[to]) {
                mySet.erase({dis[to], to});
                dis[to] = dis[v] + weight;
                mySet.insert({dis[to], to});
            }
        }
    }
    return dis[d];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, m, z, d;
    cin >> n >> m;
    graph.resize(2*n+1);
    
    for(ll i = 0; i < m; i++) {
        ll a, b, w;
        cin >> a >> b >> w;
        graph[2*a-1].push_back({2*b, w});
        graph[2*a].push_back({2*b-1, w});
        graph[2*b-1].push_back({2*a, w});
        graph[2*b].push_back({2*a-1, w});
    }
    cin >> z >> d;
    
    ll even = dijkstra(2*z-1, 2*d-1, n);
    ll odd = dijkstra(2*z, 2*d-1, n);
    if(even != inf) cout << even << " ";
    else cout << "-1 ";
    if(odd != inf) cout << odd << "\n";
    else cout << "-1\n";
    return 0;
}