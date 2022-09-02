#include <bits/stdc++.h>
using namespace std;

vector<int> parent, len;

struct edge {
    int id, a, b, w;
};

bool comp(edge e, edge f) {
    return e.w < f.w;
}

int Find(int v) {
    if(v == parent[v])
        return v;
    return parent[v] = Find(parent[v]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(len[a] > len[b])
        swap(a, b);
    parent[a] = parent[b];
    len[b] += len[a];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<edge> edg(m);
    parent.resize(m);
    len.resize(m, 0);

    for(int i = 0; i < m; i++) {
        cin >> edg[i].a >> edg[i].b >> edg[i].w;
        edg[i].id = i + 1;
    }

    for(int i = 0; i < n; i++)
        parent[i] = i;

    sort(edg.begin(), edg.end(), comp);

    for(edge e : edg) {
        if(Find(e.a) != Find(e.b)) {
            Union(e.a, e.b);
            cout << e.id << "\n";
        }
    }

    return 0;
}