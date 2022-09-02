#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

void push_queue(deque<pair<int, int>> &q, int &len, int x, int r) {
    while(!q.empty() && x > q.back().st)
        q.pop_back();
    q.push_back({x, r});
    len++;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, l = 1, len = 0, ans = 0;
    cin >> n;
    deque<pair<int, int>> q;
    for(int r = 1; r <= n; r++) {
        int x, y;
        cin >> x >> y;
        while(!q.empty() && y < q.front().st) {
            //cout << "LEN: " << len << " " << q.front().nd << " " << l << "\n";
            len -= (q.front().nd - l + 1);
            l = q.front().nd + 1;
            q.pop_front();
        }
        push_queue(q, len, x, r);
        ans = max(ans, len);
        //cout << ans << "\n";
        //cout << "QUEUE:\n";
        //for(auto v : q)
        //    cout << v.st << " " << v.nd << "\n";
    }
    cout << ans << "\n";
    return 0;
}