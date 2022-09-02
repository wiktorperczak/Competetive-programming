#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> graph;
typedef vector<int> vi;
typedef vector<bool> vb;

void dfs(graph const &g, vi &st, vb &vis, int i) {
    vis[i] = true;
    for(auto w :  g[i]) {
        if(!vis[w])
            dfs(g, st, vis, w);
    }
    st.push_back(i);
}

void rdfs(graph const &rg, vi &st, vb &vis, vi &com, int i) {
    vis[i] = true;
    com.push_back(i);
    for(auto w : rg[i]) {
        if(!vis[w])
            rdfs(rg, st, vis, com, w);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z, n, m, a, b, k, u, v;
    cin >> z;

    while(z--) {
        cin >> n >> m;
        graph g(n+1), rg(n+1);
        vb vis(n+1, 0);
        vi st, com, root(n+1, 0);

        for(int i = 0; i < m; i++) {
            cin >> a >> b;
            g[a].push_back(b);
            rg[b].push_back(a);
        }

        for(int i = 1; i <= n; i++) {
            if(!vis[i])
                dfs(g, st, vis, i);
        }

        vis.assign(n+1, 0);
        reverse(st.begin(), st.end());

        for(auto w : st) {
            if(!vis[w])
                rdfs(rg, st, vis, com, w);
            for(auto w1 :  com) root[w1] = com.front();
            com.clear();
        }

        cin >> k;
        while(k--) {
            cin >> u >> v;
            if(root[u] == root[v]) cout << "TAK\n";
            else cout << "NIE\n";
        }

    }
    return 0;
}