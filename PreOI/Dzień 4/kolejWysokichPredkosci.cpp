#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

int L, n;
vector<vector<pair<int, int>>> tree;
vector<vector<int>> anc;
vector<int> par, len, depth, cost;

int Find(int v) {
    if(v == par[v]) return v;
    return par[v] = Find(par[v]);
}

void dfs(int v, int p, int c) {
    anc[0][v] = p;
    for(int i = 1; i <= L; i++)
        anc[i][v] = anc[i-1][anc[i-1][v]];    
    cost[v] = cost[p] + c;
    depth[v] = depth[p] + 1;

    for(auto i : tree[v]) {
        if(i.st != p)
            dfs(i.st, v, i.nd);
    }
}

void build(int x, int y, int m) {    
    tree[x].push_back({y, m});
    tree[y].push_back({x, m});

    int X = Find(x), Y = Find(y);
    if(len[X] > len[Y]) swap(x, y);
    par[X] = Y;
    len[Y] += len[X];
    dfs(x, y, m);
}

int path(int x, int y) {
    int cost1 = cost[y], cost2 = cost[x];
    if(depth[y] < depth[x]) swap(x, y);
    for(int i = L; i >= 0; i--) {
        if(depth[anc[i][y]] >= depth[x])
            y = anc[i][y];
    }
    if(x == y) return cost1 + cost2 - 2 * cost[x];

    for(int i = L; i >= 0; i--) {
        if(anc[i][x] != anc[i][y]) {
            x = anc[i][x];
            y = anc[i][y];
        }
    }
    return cost1 + cost2 - 2 * cost[anc[0][y]];
}

void init(int N, int s) {
    n = N;
    L = log2(n);
    anc.resize(L+1, vector<int> (n+1));
    tree.resize(n+1);
    depth.resize(n+1, 0);
    cost.resize(n+1, 0);
    len.resize(n+1, 1);
    par.resize(n+1);
    for(int i = 1; i <= n; i++) par[i] = i;
}