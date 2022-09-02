#include <bits/stdc++.h>
using namespace std;

vector<int> parent, length;

int Find(int v) {
    if(v == parent[v])
        return v;
    return parent[v] = Find(parent[v]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(length[a] > length[b])
        swap(a, b);
    parent[a] = parent[b];
    length[b] += length[a];
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& e) {
        return weight < e.weight;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m), backup(m);
    parent.resize(n + 1);
    length.resize(n + 1, 0);
    
    for(int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v;
        cin >> edges[i].weight;
        backup[i] = edges[i];
    }

    sort(edges.begin(), edges.end());
    int prev = edges[0].weight;
    vector<Edge> store;
    set<pair<pair<int, int>, int>> ANS;

    for(int i = 1; i <= n; i++)
        parent[i] = i;

    for(Edge e : edges) {
        if(e.weight != prev) {
            int i = (int) store.size();
            while(i != 0) {
                Union(store[i - 1].u, store[i - 1].v);
                store.pop_back();
                i--;
            }
            prev = e.weight;
        }

        if(Find(e.u) != Find(e.v)) {
            ANS.insert({{e.u, e.v}, e.weight});
            // ans.insert(e);
            store.push_back(e);
        }
    }

    for(int i = 0; i < m; i++) {
        int p = backup[i].u, k = backup[i].v, w = backup[i].weight;
        if(ANS.find({{p, k}, w}) != ANS.end())
            cout << "TAK\n";
        else cout << "NIE\n";
    }

    return 0;
}