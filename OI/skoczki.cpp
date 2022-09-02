#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<pair<int, int>>> vec2pairs;
typedef vector<vector<bool>> vec2b;

void add(vector<vec2pairs> &graph, vec2b const &del, int i, int j, int x, int y, int n) {
    if(x > 0 && x <= n && y > 0 && y <= n) {
        if(!del[x][y])
            graph[i][j].push_back({x, y});
    }
}

bool augment(vector<vec2pairs> const &graph, vec2pairs &match, vec2b &vis, pair<int, int> v) {
    if(vis[v.first][v.second]) return false;
    vis[v.first][v.second] = true;
    for(auto u : graph[v.first][v.second]) {
        cout << v.first << "," << v.second << " | " << u.first << "," << u.second << "\n";
        if(match[u.first][u.second].first == -1 || augment(graph, match, vis, match[u.first][u.second])) {
            match[u.first][u.second] = v;
            match[v.first][v.second] = u;
            cout << "MATCH: " << u.first << " " << u.second << "\n";
            return true;
        } 
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vec2b deleted(n+1, vector<bool> (n+1, 0));
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        deleted[a][b] = true;
    }

    vector<vec2pairs> graph(n+1, vec2pairs (n+1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(deleted[i][j]) continue;
            int x = i-1, y = j+2;
            add(graph, deleted, i, j, x, y, n);
            x = i+1;
            add(graph, deleted, i, j, x, y, n);
            x = i+2; y = j+1;
            add(graph, deleted, i, j, x, y, n);
            y = j-1;
            add(graph, deleted, i, j, x, y, n);
            x = i+1; y = j-2;
            add(graph, deleted, i, j, x, y, n);
            x = i-1;
            add(graph, deleted, i, j, x, y, n);
            x = i-2; y = j-1;
            add(graph, deleted, i, j, x, y, n);
            y = j+1;
            add(graph, deleted, i, j, x, y, n);
        }
    }

    /* for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << "Vertex: " << i << " " << j << "\n";
            for(auto k : graph[i][j])
                cout << k.first << " " << k.second << "\n";
        }
    } */

    vec2b vis;
    vec2pairs match(n+1, vector<pair<int, int>> (n+1, {-1, -1}));
    while(true) {
        vis.assign(n+1, vector<bool> (n+1, 0));
        bool any = false;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++)
                if(match[i][j].first == -1 && augment(graph, match, vis, {i, j})) any = true;
        }        
        if(!any) break;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)
            cout << i << "," << j << ": " << match[i][j].first << " " << match[i][j].second << "\n";
    }

    int maxMatching = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(match[i][j].first != -1)
                maxMatching++;
        }
    }
    maxMatching /= 2;
    int V = n*n - m;
    cout << V - maxMatching << "\n";

    return 0;
}