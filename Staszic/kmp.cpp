#include <bits/stdc++.h>
using namespace std;

vector<char> w, t;
vector<int> pi;

void prefixSufix(int n) {
    for(int i = 1; i < n; i++) {
        int j = pi[i-1];
        while(j > 0 && w[i] != w[j])
            j = pi[j-1];
        if(w[i] == w[j]) j++;
        pi[i] = j;
    }
}

void KMP(int n, int m) {
    int j = 0;
    for(int i = 0; i < m; i++) {
        while(j > 0 && t[i] != w[j]) {
            j = pi[j-1];
        }
        if(w[j] == t[i]) j++;
        if(j == n) {
            cout << i-n+2 << "\n";
            j = pi[j-1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    w.resize(n);
    for(auto& c : w) cin >> c;
    t.resize(m);
    for(auto& c : t) cin >> c;
    pi.resize(n, 0);
    prefixSufix(n);
    KMP(n, m);
    return 0;
}