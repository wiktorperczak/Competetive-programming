#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

vector<vector<pair<int, pair<bool, bool>>>> graph;
vector<vector<int>> cond;
vector<int> low, tin, root;
vector<bool> vis;
int timer, n, m, len, node;

void binSearch(int to, int v) {
    int l = 0, r = graph[to].size()-1, mid;
    while(l <= r) {
        mid = (l+r) / 2;
        if(graph[to][mid].st == v) {
            graph[to][mid].nd.nd = true;
            return;
        }
        else if(graph[to][mid].st > v) r = mid-1;
        else l = mid+1;
    }
}

void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    for(auto to : graph[v]) {
        if(to.st == p) continue;
        if(vis[to.st]) low[v] = min(low[v], tin[to.st]);
        else {
            dfs(to.st, v);
            low[v] = min(low[v], low[to.st]);
            if(low[to.st] > tin[v] && !to.nd.st) {
                binSearch(to.st, v);
                binSearch(v, to.st);
            }
        }
    }
}

void searchBridges() {
    timer = 0;
    vis.assign(n+1, false);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    for(int i = 1; i <= n; i++) {
        if(!vis[i])
            dfs(i);
    }
}

void dfs1(int v, int id) {
    if(vis[v]) return;
    vis[v] = true;
    root[v] = id;
    for(auto w : graph[v]) {
        if(w.nd.nd) continue;
        dfs1(w.st, id);
    }
}

void diameter(int v, int l, vector<bool> &visi) {
    if(l > len) {
        len = l;
        node = v;
    }
    visi[v] = true;
    for(auto w : cond[v]) {
        if(!visi[w])
            diameter(w, l+1, visi);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    graph.resize(n+1);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back({b, {false, false}});
        graph[b].push_back({a, {false, false}});
    }
    for(int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end());
        for(int j = 1; j < (int) graph[i].size(); j++) {
            if(graph[i][j].st == graph[i][j-1].st) {
                graph[i][j].nd.st = true;
                graph[i][j-1].nd.st = true;
            }
        }
    }
    searchBridges();

    int id = 0;
    vis.assign(n+1, false);
    root.assign(n+1, -1);
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            dfs1(i, id);
            id++;
        }
    }
    cond.resize(id);
    for(int i = 1; i <= n; i++) {
        for(auto j : graph[i]) {
            if(j.nd.nd)
                cond[root[i]].push_back(root[j.st]);
        }
    }

    int ans1, ans2, nodeStore, nodeStore1;
    int ans = 0, node1;
    vector<bool> visi(id, false), visi1(id, false);
    for(int i = 0; i < id; i++) {
        if(!visi[i]) {
            diameter(i, 0, visi);
            node1 = node;
            len = 0;
            diameter(node, 0, visi1);
            if(len > ans) {
                ans = len;
                nodeStore = node1;
                nodeStore1 = node;
            }
            len = 0;
        }
    }
    
    bool h1 = false, h2 = false;
    if(ans == 0) {
        for(int i = 1; i <= n; i++) {
            for(auto j : graph[i]) {
                cout << ans << " " << i << " " << j.st << "\n";
                return 0;
            }
        }   
    }
    else {
        for(int i = 1; i <= n; i++) {
            if(root[i] == nodeStore1) {
                ans1 = i;
                h1 = true;
            }
            if(root[i] == nodeStore) {
                ans2 = i;
                h2 = true;
            }
            if(h1 && h2) break;
        }
        cout << ans << " " << ans1 << " " << ans2 << "\n";
    }
    return 0;
}