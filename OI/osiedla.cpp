#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<pair<int, pair<int, bool>>>> Graph;
typedef vector<int> vi;
typedef vector<bool> vb;

void findingBridges(Graph &g, vb &vis, vi &tin, vi &low, int &t, int p, int i) {
    vis[i] = true;
    tin[i] = low[i] = t++;
    for(int k = 0; k < (int) g[i].size(); k++) {
        pair<int, pair<int, bool>> to = g[i][k];
        if(to.first == p) continue;
        if(vis[to.first])
            low[i] = min(low[i], tin[to.first]);
        else {
            findingBridges(g, vis, tin, low, t, i, to.first);
            low[i] = min(low[i], low[to.first]);
            if(low[to.first] > tin[i] && to.second.second != 1) {
                int start = 0, end = g[to.first].size()-1, mid;
                while(true) {
                    mid = (start + end)/2;
                    if(g[to.first][mid].first == i)
                        break;
                    else if(g[to.first][mid].first > i)
                        end = mid-1;
                    else 
                        start = mid+1;
                }
                g[to.first][mid].second.first = 2;
                g[i][k].second.first = 2;
            }
        }
    }
}

void scc(Graph &g, vb &vis, int i) {
    if(vis[i]) return;
    vis[i] = true;
    for(auto v : g[i]) {
        if(v.second.first == 0) {
            int start = 0, end = g[v.first].size()-1, mid;
            while(true) {
                mid = (start + end)/2;
                if(g[v.first][mid].first == i)
                    break;
                else if(g[v.first][mid].first > i)
                    end = mid-1;
                else 
                    start = mid+1;
            }
            g[v.first][mid].second.first = 1;
            scc(g, vis, v.first);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, a, b;
    cin >> n >> m;
    Graph g(n+1);
    vector<pair<int, int>> input(m);
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        input[i] = {a, b};
        g[a].push_back({b, {0, 0}});
        g[b].push_back({a, {0, 0}});
    }

    for(int i = 1; i <= n; i++) {
        int last = -1;
        sort(g[i].begin(), g[i].end());
        for(int k = 0; k < (int) g[i].size(); k++) {
            pair<int, pair<int, bool>> j = g[i][k];
            if(j.first == last) {
                g[i][k].second.second = 1;
                g[i][k-1].second.second = 1;
            }
            last = j.first;
        }
    }

    int timer = 0;
    vb vis(n+1, 0);
    vi tin(n+1, -1), low(n+1, -1);
    for(int i = 1; i <= n; i++) {
        if(!vis[i])
            findingBridges(g, vis, tin, low, timer, -1, i);
    }

    vis.assign(n+1, 0);
    int num_ans = 0;
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            scc(g, vis, i);
            num_ans++;
        }
    }
    
    cout << num_ans << "\n";
    for(int i = 0; i < m; i++) {
        int in1 = input[i].first;
        int in2 = input[i].second;
        int start = 0, end = g[in1].size()-1, mid;
        while(true) {
            mid = (start + end)/2;
            if(g[in1][mid].first == in2)
                break;
            else if(g[in1][mid].first > in2)
                end = mid-1;
            else 
                start = mid+1;
        }
        if(g[in1][mid].second.first == 2)
            cout << ">";
        else if(g[in1][mid].second.first == 0)
            cout << ">";
        else 
            cout << "<";

        if(g[in1][mid].second.second == 1) {
            if(g[in1][mid].second.first == 0) g[in1][mid].second.first = 1;
            else g[in1][mid].second.first = 0;
        }
    }
    cout << "\n";
    return 0;
}