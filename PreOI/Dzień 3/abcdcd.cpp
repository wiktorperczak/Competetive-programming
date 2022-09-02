#include <bits/stdc++.h>
using namespace std;

constexpr int M = 1e9 + 7;

void factorial(vector<int> &fact) {
    fact[0] = 1;
    for(int i = 1; i <= 60; i++)
        fact[i] = (fact[i-1] * i) % M;
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);

    string s;
    cin >> s;
    vector<vector<int>> pos(60);
    for(int i = 0; i < (int) s.length(); i++) {
        int id = s[i] - 'A';
        pos[id].push_back(i);
    }

    vector<int> occ(60, 0), fact(60);
    factorial(fact);
    int dif = 0, mult = 1, ans = 0;
    for(int i = 0; i < (int) s.length(); i++) {
        // cout << i << " " << dif << "\n";
        int id = s[i] - 'A', dif1 = dif, mult1 = mult;
        if((dif1 == 2 && occ[id] == 0) || dif1 > 2) {
            dif1 -= min(1, occ[id]);
            mult1 /= max(1, occ[id]);
            for(int j = occ[id]+1; j < (int) pos[id].size(); j++) {
                // cout << pos[id][j] << " TAK\n";
                for(int k = i+1; k < pos[id][j]; k++) {
                    int id2 = s[k] - 'A';
                    if((dif1 == 2 && occ[id2] == 0) || dif1 > 2) {
                        dif1 -= min(1, occ[id2]);
                        mult1 /= max(1, occ[id2]);
                        // cout << k << " " << dif1 << " " << mult1 << "\n";
                        int res = 0, l = 0, r = pos[id2].size() - 1;
                        while(l <= r) {
                            // cout << "NIE " << l << " " << r << "\n";
                            int mid = (l+r)/2;
                            if(pos[id2][mid] > pos[id][j]) {
                                res = mid;
                                r  = mid - 1;
                            }
                            else {
                                l = mid + 1;
                            }
                        }
                        res = pos[id2].size() - res;
                        cout << res << " " << fact[dif1] << " " << fact[dif1-2] << " " << mult1 << "\n";
                        if( res > 0) ans += (fact[dif1] / (2 * fact[dif1-2]) * ((mult1 * res) % M)) % M;
                        cout << ans << "\n";
                    }
                }
            }
        }

        if(occ[id] == 0) dif++;
        else {
            mult /= occ[id];
            mult *= (occ[id] + 1);
        }
        occ[id]++;
    }
    cout << ans << "\n";
    return 0;
}