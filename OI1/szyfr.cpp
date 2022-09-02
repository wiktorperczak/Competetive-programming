#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

void sum(int m, vector<int> const &S, vector<pair<int, int>> &res) {
    for(int i = 0; i < (1 << m); i++) {
        res[i].nd = i;
        for(int j = 0; j < m; j++) {
            if(i & (1 << j))
                res[i].st += S[j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, s;
    cin >> n;
    vector<pair<int, int>> res1((1 << n/2), {0, 0}), res2((1 << (n+1)/2), {0, 0});
    vector<int> set1(n/2), set2((n+1)/2);
    for(int i = 0; i < n/2; i++) cin >> set1[i];
    for(int i = 0; i < (n+1)/2; i++) cin >> set2[i];
    cin >> s;

    sum(n/2, set1, res1);
    sum((n+1)/2, set2, res2);
    sort(res2.begin(), res2.end());
    pair<int, int> ans;
    for(int i = 0; i < (1 << (n/2)); i++) {
        int x = s - res1[i].st, id = -1;
        int l = 0, r = (1 << (n+1)/2) - 1, mid;
        while(l <= r) {
            mid = (l+r)/2;
            if(res2[mid].st == x) {
                id = mid;
                break;
            }
            else if(res2[mid].st > x) r = mid - 1;
            else l = mid + 1;
        }
        if(id != -1) {
            ans = {i, res2[id].nd};
            break;
        }
    }
    
    for(int i = 0; i < n/2; i++) {
        cout << ans.st % 2;
        ans.st /= 2;
    }
    for(int i = 0; i < (n+1)/2; i++) {
        cout << ans.nd % 2;
        ans.nd /= 2;
    }
    cout << "\n";
    return 0;
}