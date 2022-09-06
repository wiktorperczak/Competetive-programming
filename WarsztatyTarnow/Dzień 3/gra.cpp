#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<bool> state(n+1);
    state[0] = false;
    for(int i = 1; i <= m; i++) state[i] = true;
    int lose = 0;
    for(int i = m+1; i <= n; i++) {
       if(i != n && (__builtin_popcount(i)) % 2 == 1) state[i] = true;
       else {
           if(lose > 0) state[i] = true;
           else state[i] = false;
       }
       if(!state[i-m]) lose--;
       if(!state[i]) lose++;
    }
    cout << (state[n] ? "Stawiasz\n" : "Darmowe ciasteczka!\n");
    return 0;
}