#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, ans = 0;
    cin >> n;
    vector<char> s(n);
    
    for(auto& c : s) cin >> c;
    vector<vector<int>> occ(26);
    
    for(int i = 0; i < n; i++)
        occ[s[i] - 'a'].push_back(i);

    for(int i = 0; i < 26; i++) {
        if((int) occ[i].size() == 0) continue;

        for(int j = 0; j < 26; j++) {
            if((int) occ[j].size() == 0 || i == j) continue;
            int sum = 0, minSum = 0, mini = INT_MAX;
            int k = 0, l = 0, x;
            int si = occ[i].size(), sj = occ[j].size();
           
            while(k < (int) si || l < (int) sj) {
                if(k >= si)
                    x = 1, l++;
                else if(l >= sj)
                    x = -1, k++;
                else if(occ[i][k] < occ[j][l])
                    x = -1, k++;
                else
                    x = 1, l++;
                
                sum += x;
                if(x == -1) {
                    mini = min(mini, minSum);
                    minSum = sum;
                }
                ans = max(ans, sum - mini);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}