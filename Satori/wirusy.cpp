#include <bits/stdc++.h>
using namespace std;

struct Node {
    int suf, next[2];
    bool state;
    
    Node() {
        next[0] = -1;
        next[1] = -1;
        suf = 0;
        state = false;
    }
};

void addString(string const& pat, vector<Node>& T) {
    int v = 1;
    for(auto c : pat) {
        int t = c - '0';
        if(T[v].next[t] == -1) {
            T[v].next[t] = T.size();
            T.emplace_back();
        }
        v = T[v].next[t];
    }
    T[v].state = true;
}

void bfs(vector<Node>& T) {
    queue<int> q;
    q.push(1);

    while(!q.empty()) {
        int u = q.front();  
        q.pop();
        int f = T[u].suf;

        for(int i = 0; i < 2; i++) {
            int& v = T[u].next[i];
            if(v >= 0) {
                q.push(v);
                T[v].suf = T[f].next[i];
                if(T[T[f].next[i]].state) {
                    T[v].state = true;
                }
            } 
            else
                v = T[f].next[i];
        }
    }
}

bool dfs(vector<Node>& T, vector<int>& vis, int& start, int& x) {
    vis[x] = 1;
    for(int i = 0; i < 2; i++) {
        int y = T[x].next[i];
        if(vis[y] == 0 && !T[y].state) {
            if(dfs(T, vis, start, y))
                return true;
        }
        else if(vis[y] == 1) {
            start = x;
            return true;
        }
    }
    vis[x] = 2;
    return false;
}

void findCycle(vector<Node>& T) {
    int len = (int) T.size(), start = -1;
    vector<int> vis(len, 0);

    for (int i = 1; i < len; i++) {
        if(T[i].state == 0  && vis[i] == 0 && dfs(T, vis, start, i))
            break;
    }
    if(start == -1) cout << "NIE\n";
    else cout << "TAK\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while(z--) {
        int n;
        cin >> n;
        vector<string> pat(n);
        for(int i = 0; i < n; i++)
            cin >> pat[i];
        
        vector<Node> T(2);
        T[0].next[0] = 1; T[0].next[1] = 1;
        for(auto t : pat)
            addString(t, T);
        bfs(T);
        findCycle(T);
    }
    return 0;
}