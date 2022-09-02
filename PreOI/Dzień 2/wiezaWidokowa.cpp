#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.precision(20);

    int n;
    string s;
    cin >> n >> s;
    double ans = -1e9, mini, y = 0, a, end = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'G') end++;
        else end--;
    }
    for(int x = 1; x <= n; x++) {
        if(s[x-1] == 'G') y++;
        else y--;
        a = y / x;
        mini = a * n - end;
        if(x != n && ceil(mini) == mini) mini = ceil(mini) + 1;
        else mini = ceil(mini);
        ans = max(ans, mini);
    }
    cout << abs(ans) << "\n";
    return 0;
}