#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, dis = 0;
    cin >> n;
    vector<ll> p(n+1), b(n+1), ans(n+1);
    for(int i = 1; i <= n; i++) cin >> p[i];
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        dis += abs(p[i] - b[i]);
    }
    stack<ll> st;
    ll time = 1, id = 1;
    while(id <= n) {
        if(p[id] > b[id]) {
            while(!st.empty() && abs(b[st.top()] - p[st.top()]) <= abs(b[st.top()] - p[id])) {
                ans[st.top()] = time;
                time++;
                st.pop();
            }
            // cout << id << " " << time << "\n";
            ans[id] = time;
            time++;
        }
        else st.push(id);
        id++;
    }
    while(!st.empty()) {
        ans[st.top()] = time;
        time++;
        // cout << st.top() << " ";
        st.pop();
    }
    // cout << "\n";
    cout << dis << "\n";
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
    return 0;
}