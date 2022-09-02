#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string s;
    cin >> s;
    int n = s.length(), ans = n;

    vector<int> prefs;
    vector<int> pi1(n, 0);
    for(int i = 1; i < n; i++) {
        int j = pi1[i-1];
        while(j > 0 && s[i] != s[j]) j = pi1[j-1];
        if(s[i] == s[j]) j++;
        pi1[i] = j;
    }
    int x = pi1[n-1];
    prefs.push_back(x);
    x = pi1[x-1];
    while(x > 0) {
        int len = prefs.size()-1;
        if(x >= (prefs[len] + 1)/2) prefs[len] = x;
        else prefs.push_back(x);
        x = pi1[x-1];
    }
    reverse(prefs.begin(), prefs.end());
    /* for(auto i : prefs) cout << i << " ";
    cout << "\n"; */

    for(auto i : prefs) {
        vector<int> pi(n, 0);
        int k, last = i-1;
        bool correct = true;
        for(int j = 1; j < n; j++) {
            k = pi[j-1];
            while(k > 0 && s[j] != s[k]) k = pi[k-1];
            if(s[j] == s[k]) k++;
            if(k == i) {
                last = j;
                k = pi[k-1];
            }
            pi[j] = k;
            if(j - last >= i) {
                correct = false;
                break;
            }
        }
        if(correct && last == n-1) {
            ans = i;
            break;
        }
    }
    cout << ans << "\n";
    return 0;
}