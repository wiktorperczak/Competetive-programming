#include <bits/stdc++.h>
using namespace std;

constexpr int C = 8e5;
vector<bool> used(C+1, false);
vector<int> prime;

void sieve() {
    for(int i = 2; i*i <= C; i++) {
        if(!used[i]) {
            for(int j = i*i; j <= C; j += i)
                used[j] = true;
        }
    }
    for(int i = 2; i <= C; i++) {
        if(!used[i]) prime.push_back(i);
    }
}

bool isPrime(int k) {
    for(int i = 0; prime[i]*prime[i] <= k; i++) {
        if(k%prime[i] == 0)
            return false;
    }
    return true;
}

void solve(int k, vector<int> &store) {
    while(k > 0) {
        int v = k, dif = 0;
        while(!isPrime(v) || dif == 1 || dif == 2 || dif == 4 || dif == 6 || dif == 9) {
            v--;
            dif++;
        }
        k -= v;
        store.push_back(v);
    }
}

int main() {
    ios::sync_with_stdio(0);
     cin.tie(0); cout.tie(0);

    sieve();
    int n;
    cin >> n;
    while(n--) {
        int k;
        cin >> k;
        vector<int> res;
        solve(k, res);
        const int s = (int) res.size();
        cout << s << "\n";
        for(int i = s-1; i >= 0; i--)
            cout << res[i] << " ";
        cout << "\n";
    }
    return 0;
}