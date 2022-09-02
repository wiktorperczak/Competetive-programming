#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void computePower(ll l, ll P, ll M, vector<ll> &power) {
    power[0] = 1;
    for(ll i = 1; i < l; i++)
        power[i] = (power[i-1] * P) % M;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    constexpr ll P = 29, P1 = 31, M = 1e9 + 7, M1 = 1e9 + 696969;
    ll n, l;
    cin >> n >> l;
    vector<ll> power(l), power1(l);
    computePower(l, P, M, power);
    computePower(l, P1, M1, power1);
    vector<string> s(n);
    vector<ll> hash(n, 0), hash1(n, 0);
    for(ll i = 0; i < n; i++) cin >> s[i];

    vector<deque<ll>> pos(n);
    for(ll i = 0; i < n-1; i++) {
        for(ll j = 0; j < l; j++) {
            if(s[i][j] != s[i+1][j]) pos[i].push_back(j);
        }
    }

    ll st = 0, end = 0;
    pair<ll, ll> ans = {0, l-1};
    while(end < l) {
        bool check = false;
        for(ll i = 0; i < n; i++) {
            hash[i] = (hash[i] + (s[i][end] - 'a' + 1) * power[end]) % M;
            hash1[i] = (hash1[i] + (s[i][end] - 'a' + 1) * power1[end]) % M1;
            if(i > 0 && hash[i] == hash[i-1] && hash1[i] == hash1[i-1]) check = true;
        }
        bool check3 = false;
        for(ll i = 0; i < n; i++) {
            if(!pos[i].empty() && pos[i].front() < st) pos[i].pop_front();
            if(i > 0 && !pos[i-1].empty()) {
                if(s[i-1][pos[i-1].front()] > s[i][pos[i-1].front()]) {
                    check3 = true;
                }
            }
        }
        if(check && !check3) end++;
        else {
            if(!check3 && end - st < ans.second - ans.first) ans = {st, end};
            bool check1 = true;
            while(check1 && st <= end) {
                check1 = false;
                for(ll i = 0; i < n; i++) {
                    if(!pos[i].empty() && pos[i].front() <= st) pos[i].pop_front();
                    if(i > 0 && !pos[i-1].empty()) {
                        if(s[i-1][pos[i-1].front()] > s[i][pos[i-1].front()]) check1 = true;
                    }
                }
                bool check2 = false;
                for(ll i = 0; i < n; i++) {
                    hash[i] = (hash[i] - (s[i][st] - 'a' + 1) * power[st] + M) % M;
                    hash1[i] = (hash1[i] - (s[i][st] - 'a' + 1) * power1[st] + M1) % M1;
                    if(i > 0 && hash[i] == hash[i-1] && hash1[i] == hash1[i-1]) check2 = true;
                }
                st++;
                if(!check1 && !check2) {
                    check1 = true;
                    if(end - st < ans.second - ans.first) ans = {st, end};
                }
                else if(!check1) end++;
            }
            if(st > end) end++;
        }
    }
    cout << ans.first+1 << " " << ans.second+1 << "\n";
    return 0;
}