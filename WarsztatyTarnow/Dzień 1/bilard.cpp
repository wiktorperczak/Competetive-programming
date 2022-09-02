#include <bits/stdc++.h>
using namespace std;

double bx, by, cx, cy;

bool check(double x, double y) {
    double a = abs(x - bx) / abs(y - by);
    double b = abs(x - cx) / abs(y - cy);
    if(a == b || (a != b && bx == cx) || a == 0 || b == 0)
        return true;
    else return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    double l, w, n;
    cin >> l >> w >> n;
    cin >> bx >> by >> cx >> cy;
    int ans = 3;
    if(by == cy) ans--;
    if(!check(l / 2, 0)) ans++;
    if(!check(l / 2, w)) ans++;
    cout << ans << "\n";
    return 0;
}