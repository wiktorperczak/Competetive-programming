#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> Graph;

Graph G;
vector<int> tin, low, res;
vector<bool> vis;
int cnt;
bool ans;

void dfs(int v, int p = -1) {
    tin[v] = low[v] = cnt++;
    int sons = 0;
    for(auto w : G[v]) {
        if (w == p) continue;
        if (tin[w] != -1) {
            low[v] = min(low[v], tin[w]);
        } else {
            dfs(w, v);
            low[v] = min(low[v], low[w]);
            if (low[w] >= tin[v] && p!=-1)
                ans = false;
            sons++;
        }
    }
    if(sons > 1 && p == -1) ans = false;
}

void dfs2(int v, int p) {
    vis[v] = true;
    for(int i = 1; i <= 3; i++) {
        res[v] = i;
        if(low[v] == v && res[p] != i) 
            break;
        else if(res[p] != i && res[low[v]] != i)
            break;
    }
    for(auto w : G[v]) {
        if(vis[w] != true)
            dfs2(w, v);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z, n, m, a, b;
    cin >> z;
    while(z--) {
        cin >> n >> m;
        G.resize(n+1);
        tin.resize(n+1, -1);
        low.resize(n+1, -1);
        res.resize(n+1, -1);
        for(int i = 0; i < m; i++) {
            cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        cnt = 1; ans = true;
        dfs(1);
        for(int i = 1; i <= n; i++) {
            if(tin[i] == -1)
                ans = false;
        }

        /* cout << "vector:\n";
        for(int i = 1; i <= n; i++)
            cout << i << " " << tin[i] << " " << low[i] << "\n"; */

        if(!ans) cout << "NIE\n";
        else {
            vis.resize(n+1, 0);
            dfs2(1, 0);
            cout << "TAK ";
            for(int i = 1; i <= n; i++)
                cout << res[i] << " ";
            cout <<"\n";
        }
    }
    return 0;
}