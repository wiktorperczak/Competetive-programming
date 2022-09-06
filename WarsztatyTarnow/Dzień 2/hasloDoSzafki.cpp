#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        int n, ans = 0;
        cin >> n;
        int len = pow(10, n);
        vector<int> num;
        for(int i = 1; i < len; i++) {
            num.assign(n, 0);
            int x = i, id = 0;
            while(x > 0) {
                num[id] = x % 10;
                x /= 10;
                id++;
            }
            int sum = 0, product = 1;
            for(int j = 0; j < id; j++) {
                sum += num[j];
                product *= num[j];
            }
            if(sum == product) ans++;
        }
    }
    return 0;
}