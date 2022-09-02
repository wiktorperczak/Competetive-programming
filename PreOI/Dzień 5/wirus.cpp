#include <bits/stdc++.h>
using namespace std;

vector<set<int>> tree;
vector<int> val, par;
vector<bool> vis;

void dfs(int v) {
    if(vis[v]) return;
    vis[v] = true;
    val[v] = 1;
    for(auto w : tree[v]) {
        if(!vis[w]) {
            dfs(w);
            par[w] = v;
            val[v] += val[w];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, x;
    cin >> n >> x;
    tree.resize(n+1);
    vis.assign(n+1, false);
    val.assign(n+1, 1);
    par.assign(n+1, -1);
    vector<int> g(n-1);
    for(int i = 0; i < n-2; i++) cin >> g[i];
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].insert(b);
        tree[b].insert(a);
    }
    dfs(1);
    for(int i = 0; i < n-1; i++) {
        cout << val[x] << "\n";
        tree[x].erase(par[x]);
        tree[par[x]].erase(x);
        par[x] = -1;
        vis.assign(n+1, false);
        dfs(1);
        if(i < n-2) {
            int l = (val[x] + g[i]) % (n-i-2) + 1;
            for(int j = 1; j <= n; j++) {
                if(par[j] != -1) l--;
                if(l == 0) {
                    x = j;
                    break;
                }
            }
        }
    }
    return 0;
}