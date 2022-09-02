#include <bits/stdc++.h>
using namespace std;

constexpr int H = 18, base = 1<<H;
int tree[2*base] = {0};
int preCount = 0;
vector<vector<int>> g;
vector<int> pre, sons;
vector<bool> vis;

void dfs(int v) {
    if(vis[v]) return;
    vis[v] = true;
    pre[v] = preCount++;
    for(auto w : g[v])
        dfs(w);
    sons[v] = preCount - pre[v];
}

void bfs(pair<int, int> v) {
    queue<pair<int, int>> q;
    q.push(v);
    vis[v.first] = true;
    while(!q.empty()) {
        v = q.front();
        tree[pre[v.first] + base] = v.second;
        q.pop();
        for(auto w : g[v.first]) {
            if(!vis[w]) {
                q.push({w, v.second+1});
                vis[w] = true;
            }
        }
    }
}

void update(int v, int beg, int end, int a, int b) {
    if(beg > b || end < a) return;
    else if(beg >= a && end <= b) {
        tree[v]--;
        return;
    }
    else {
        int l = v*2, r = v*2+1, mid = (beg+end)/2;
        update(l, beg, mid, a, b);
        update(r, mid+1, end, a, b);
    }
}

int query(int v, int beg, int end, int a) {
    if(beg > a || end < a) return 0;
    else if(beg == a && end == a)
        return tree[v];
    else {
        int l = 2*v, r = 2*v+1, mid = (beg+end)/2;
        tree[l] += tree[v];
        tree[r] += tree[v];
        tree[v] = 0;
        return query(l, beg, mid, a) + query(r, mid+1, end, a);

    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, a, b;
    cin >> n;
    g.resize(n+1);
    sons.resize(n+1);
    pre.resize(n+1);
    vis.resize(n+1, false);
    for(int i = 0; i < n-1; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1);
    vis.clear();
    vis.resize(n+1, false);
    bfs({1, 0});
    int m;
    cin >> m;
    m = m+n-1;
    while(m--) {
        char c;
        cin >> c;
        if(c == 'W') {
            cin >> a;
            cout << query(1, 1, base, pre[a]+1) << "\n";
        }
        else if(c == 'A') {
            cin >> a >> b;
            update(1, 1, base, pre[b]+1, pre[b]+sons[b]);
        }
    }
    return 0;
}