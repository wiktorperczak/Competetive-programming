#include <bits/stdc++.h>
using namespace std;

constexpr int H = 17;
pair<int, int> tree[2*(1<<H)] = {{0, 0}};

void modify(int v) {
    if(!v) return;
    tree[v].second = tree[2*v].second + tree[2*v+1].second;
    tree[v].first = max(tree[2*v].first, tree[2*v].second + tree[2*v+1].first);
    modify(v/2);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int s, w, n;
    cin >> s >> w >> n;
    vector<tuple<int, int, int>> points(2*n);
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points[i*2] = make_tuple(x, -1, y);
        points[i*2+1] = make_tuple(x+s, 1, y);
    }
    sort(points.begin(), points.end());
    int ans = 0;

    for(auto i : points) {
        int value = -get<1>(i);
        int cor = (1<<H) + get<2>(i) + 3e4;
        tree[cor].first += value;
        tree[cor].second += value;
        modify(cor/2);
        cor += w+1;
        tree[cor].first -= value;
        tree[cor].second -= value;
        modify(cor/2);
        ans = max(ans, tree[1].first);
    }
    cout << ans << "\n";
    return 0;
}