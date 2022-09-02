#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> Graph;

void dfs(Graph const &g, stack<int> &st, vector<bool> &vis, int i) {
    if(vis[i]) return;
    vis[i] = true;
    for(auto v : g[i])
        dfs(g, st, vis, v);
    st.push(i);
}

void rdfs(Graph const &rg, vector<int> &scc, int c, int i) {
    if(scc[i] != -1) return;
    scc[i] = c;
    for(auto v : rg[i])
        rdfs(rg, scc, c, v);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, a, b;
    cin >> n >> m;
    Graph g(2*n+1), rg(2*n+1);
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        if(b%2 == 0) {
            g[a].push_back(b-1);
            rg[b-1].push_back(a);
        } else {
            g[a].push_back(b+1);
            rg[b+1].push_back(a);
        }
        if(a%2 == 0) {
            g[b].push_back(a-1);
            rg[a-1].push_back(b);
        } else {
            g[b].push_back(a+1);
            rg[a+1].push_back(b);
        }
    }

    stack<int> st;
    vector<bool> vis(2*n+1, 0);
    for(int i = 1; i <= 2*n; i++)
        dfs(g, st, vis, i);
    
    int count = 0, v;
    vector<int> scc(2*n+1, -1);
    while(!st.empty()) {
        v = st.top();
        st.pop();
        rdfs(rg, scc, count++, v);
    }

    for(int i = 1; i <= 2*n; i+=2) {
        if(scc[i] == scc[i+1]) {
            cout << "NIE\n";
            return 0; 
        }
    }
    for(int i = 1; i <= 2*n; i+=2)
        cout << (scc[i] > scc[i+1] ? i : i+1) << "\n";
    return 0;
}