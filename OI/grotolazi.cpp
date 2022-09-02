#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> Graph;

int n;
Graph graph, bi;
vector<bool> vis;
vector<int> match;
vector<vector<bool>> path;

void floydWarshall() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(path[j][i]) {
                for(int k = 1; k <= n; k++)
                    path[j][k] = (path[j][k] || path[i][k]);
            }
        }
    }
}

/* void dfs(int &v, int const &par) {
    for(auto w : graph[v]) {
        if(w == n) {
            bi[par].push_back(n+v);
            bi[n+v].push_back(par);
        }
        else dfs(w, par);
    }
} */

bool augment(int &v) {
    if(vis[v]) return false;
    vis[v] = true;
    for(auto w : bi[v]) {
        if(match[w] == -1 || augment(match[w])) {
            match[v] = w;
            match[w] = v;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m, v, add = 0;
    cin >> n;
    path.resize(n+1, vector<bool> (n+1, false));
    graph.resize(n+1);
    bi.resize(2*n+1);
    vis.resize(n+1, false);
    for(int i = 1; i < n; i++) {
        cin >> m;
        while(m--) {
            cin >> v;
            graph[i].push_back(v);
            if(i == 1 && v == n)
                add = 1;
            if(v == n)
                vis[i] = true;
        }
    }
    for(int i = 1; i <= n; i++) {
        path[i][i] = true;
        for(auto j : graph[i])
            path[i][j] = true;
    }
    floydWarshall();
    for(int i = 1; i <= n; i++)
        path[i][i] = true;

    /* for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)
            cout << path[i][j] << " ";
        cout << "\n";
    } */

    for(auto i : graph[1]) {
        for(int j = 1; j <= n; j++) {
            if(vis[j] && path[i][j]) {
                bi[i].push_back(j+n);
                bi[j+n].push_back(i);
            }
        }
    }
    path.clear();

    /* for(int i = 1; i <= n; i++) {
        cout << i << ": ";
        for(auto j : bi[i])
            cout << j << " ";
        cout << "\n";
    }

    for(auto i : graph[1])
        dfs(i, i); */
    
    graph.clear();
    match.assign(2*n+1, -1);
    bool any;
    while(true) {
        vis.assign(2*n+1, false);
        any = false;
        for(int i = 1; i <= 2*n; i++) {
            if(match[i] == -1 && augment(i)) 
                any = true;
        }
        if(!any) break;
    }
    int ans = 0;
    for(int i = 1; i <= 2*n; i++) {
        if(match[i] != -1) ans++;
    }
    cout << ans/2 + add << "\n";
    return 0;
}