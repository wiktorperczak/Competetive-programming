#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> graph;
typedef vector<int> vi;
typedef vector<bool> vb;

void dfs(graph const &g,  stack<int> &st, vb &vis, int i) {
    if(vis[i]) return; 
    vis[i] = true;

    for(auto w :  g[i])
        dfs(g, st, vis, w);
    st.push(i);
}

void rdfs(graph const &rg, stack<int> &st, vi &scc, vector<pair<int, int>> &order, int i, int c) {
    if(scc[i] != -1) return;
    order[c].first++;
    scc[i] = c;

    for(auto w : rg[i])
        rdfs(rg, st, scc, order, w, c);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z, n, c, d;
    cin >> z;

    while(z--) {
        cin >> n;
        graph g(n+1), rg(n+1);
        stack<int> st;
        vb vis(n+1, 0);
        vi scc(n+1, -1);
        vector<pair<int, int>> order;

        for(int j = 1; j <= n; j++) {
            cin >> c;
            for(int i = 0; i < c; i++) {
                cin >> d;
                g[j].push_back(d);
                rg[d].push_back(j);
            }
        }

        for(int i = 1; i <= n; i++)
                dfs(g, st, vis, i);

        int count = 0, t;
        while(!st.empty()) {
            //cout << st.top() << " ";
            t = st.top();
            st.pop();

            if(scc[t] == -1) {
                order.push_back({0, count});
                rdfs(rg, st, scc, order, t, count++);
            }
        }

        cout << "SCC: ";
        for(int i = 1; i <= n; i++)
            cout << scc[i] << " ";
        cout << "\n";

        vb check(order.size(), 0);
        for(int i = 1; i <= n; i++) {
            for(auto w : g[i]) {
                if(scc[i] != scc[w]) 
                    check[scc[i]] = true;
            }
        }

        int ans = INT_MAX, num;
        for(int i = 0; i < (int) order.size(); i++) {
            if(!check[order[i].second] && ans > order[i].first) {
                ans = order[i].first;
                num = order[i].second;
            }
        }

        cout << ans << "\n";
        for(int i = 1; i <= n; i++) {
            if(scc[i] == num)
                cout << i << " ";
        }
        cout << "\n";
    }
    return 0;
}