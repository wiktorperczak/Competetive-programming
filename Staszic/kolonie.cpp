#include <bits/stdc++.h>
using namespace std;

struct bact {
    int id, mini, maxi, w;
};

vector<bact> b;
vector<int> parent, len;

int Find(bact v) {
    if(v.id == parent[v.id])
        return v.id;
    return parent[v.id] = Find(b[parent[v.id]]);
}

void Union(bact x, bact y) {
    x = b[Find(x)];
    y = b[Find(y)];
    if(len[x.id] > len[y.id])
        swap(x, y);
    
    len[y.id] += len[x.id];
    y.mini = min(x.mini, y.mini);
    y.maxi = max(x.maxi, y.maxi);
    y.w += x.w;
    parent[x.id] = parent[y.id];
    b[y.id] = y;
    b[x.id] = x;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, x, y;
    string com;
    cin >> n;

    b.resize(n + 1);
    parent.resize(n + 1);
    len.resize(n + 1, 0);

    for(int i = 1; i <= n; i++) {
        b[i].id = i;
        cin >> b[i].w >> b[i].mini;
        b[i].maxi = b[i].mini;
        parent[i] = i;
    }

    while(cin >> com) {
        if(com == "JOIN") {
            cin >> x >> y;
            Union(b[x], b[y]);
        }
        else if(com == "IQ_MIN") {
            cin >> x;
            cout << b[Find(b[x])].mini << "\n";
        }
        else if(com == "IQ_MAX") {
            cin >> x;
            cout << b[Find(b[x])].maxi << "\n";
        }
        else {
            cin >> x;
            cout << b[Find(b[x])].w << "\n";
        }
    }

    return 0;
}