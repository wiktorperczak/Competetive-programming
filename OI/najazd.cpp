#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

int crossProduct(int x1, int y1, int x2, int y2, int x3, int y3) {
    double res = 0.5 * (x1*y2 - x2*y1 + x2*y3 - x3*y2 + x3*y1 - x1*y3);
    if(res > 0) return 1;
    else if(res == 0) return 0;
    else return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, S = 0;
    cin >> n;
    vector<pair<int, int>> pol(n);
    for(int i = 0; i < n; i++) cin >> pol[i].st >> pol[i].nd;
    cin >> m;
    vector<pair<int, int>> fab(m);
    vector<int> weight(m);
    for(int i = 0; i < m; i++)  {
        cin >> fab[i].st >> fab[i].nd >> weight[i];
        S += weight[i];
    }
    
    vector<vector<int>> tri(n, vector<int> (n, 0));
    for(int i = 0; i < n; i++) {
        vector<int> as(n);
        for(int j = 0; j < n; j++) {
            if(j < i) as[n-(i-j)] = j;
            else as[j-i] = j;
        }
        for(int j = 0; j < m; j++) {
            int l = 1, r = n-2, mid;
            while(l <= r) {
                mid = (l+r) / 2;
                int b1 = crossProduct(pol[i].st, pol[i].nd, pol[as[mid]].st, pol[as[mid]].nd, fab[j].st, fab[j].nd);
                int b2 = crossProduct(pol[i].st, pol[i].nd, pol[as[mid]].st, pol[as[mid]].nd, pol[as[mid+1]].st, pol[as[mid+1]].nd);
                int b3 = crossProduct(pol[i].st, pol[i].nd, pol[as[mid+1]].st, pol[as[mid+1]].nd, fab[j].st, fab[j].nd);
                int b4 = crossProduct(pol[i].st, pol[i].nd, pol[as[mid+1]].st, pol[as[mid+1]].nd, pol[as[mid]].st, pol[as[mid]].nd);
                if(b1 != b2 && b1 != 0) r = mid-1;
                else if(b3 != b4) l = mid+1;
                else {
                    tri[i][as[mid]] += weight[j];
                    break;
                }
            }
        }
    }

    vector<vector<int>> sum(n, vector<int> (n, 0));
    for(int i = 0; i < n; i++) {
        vector<int> as(n);
        for(int j = 0; j < n; j++) {
            if(j < i) as[n-(i-j)] = j;
            else as[j-i] = j;
        }
        int before = 0;
        for(int j = 1; j < n-1; j++) {
            sum[i][as[j]] = before + tri[i][as[j]];
            before += tri[i][as[j]];
        }
    }

    int ans = -INT_MAX;
    for(int i = 0; i < n-2; i++) {
        for(int j = i+1; j < n-1; j++) {
            for(int k = j+1; k < n; k++) {
                int res = S - sum[i][j-1], x = i;
                res -= sum[j][k-1];
                if(i == 0) x = n;
                res -= sum[k][x-1];
                ans = max(ans, res);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}