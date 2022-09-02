#include <bits/stdc++.h>
using namespace std;

struct triple {
    int w = 0, b = 0, g = 0;
};

constexpr int H = 3, base = (1 << H);
vector<triple> tree(2*base);
vector<int> timer(2*base, -1);

void update(int v, int a, int b, int st, int end, int wh, int bl, int tim) {
    if(st > b || end < a) return;
    else if(st >= a && end <= b) {
        // cout << st << " " << end << "\n";
        // cout << "W2: " << tree[v].w << " " << tree[v].b << " " << tree[v].g << "\n";
        int range = end - st + 1;
        
        if(wh == 1) tree[v].w = range;
        else if(wh == 0) tree[v].w = 0;
        if(bl == 1) tree[v].b = range;
        else if(bl == 0) tree[v].b = 0;
        // tree[v].w = max(tree[v].w, wh * range);
        // tree[v].b = max(tree[v].b, bl * range);
        tree[v].g = min(tree[v].w, tree[v].b);
        // if(tree[v].g == 1) cout << "YYY\n";
        timer[v] = tim;
        
        // cout << "W: " << tree[v].w << " " << tree[v].b << " " << tree[v].g << "\n";
    }
    else {
        int l = 2*v, r = 2*v+1, mid = (st+end)/2;

        if(timer[v] > timer[l]) {
            // cout << "L: " << v << " " << l << "\n";
            tree[l].w = tree[v].w / 2;
            tree[l].b = tree[v].b / 2;
            tree[l].g = min(tree[l].w, tree[l].b);
            // cout << "L: " << l << " " << tree[l].w << " " << tree[l].b << " " << tree[l].g << "\n";
            // if(tree[l].g == 1) cout << "TAK\n";
            timer[l] = timer[v];
            // cout << tree[l].w << " " << tree[l].b << " " << tree[l].g << "\n";
        }

        if(timer[v] > timer[r]) {
            // cout << "R: " << v << " " << r << "\n";
            tree[r].w = tree[v].w / 2;
            tree[r].b = tree[v].b / 2;
            tree[r].g = min(tree[r].w, tree[r].b);
            // cout << "R: " << r << " " << tree[r].g << "\n";
            // if(tree[r].g == 1) cout << "NIE\n";
            timer[r] = timer[v];
            // cout << tree[r].w << " " << tree[r].b << " " << tree[r].g << "\n";
        }
        
        // cout << v << " " << tree[l].g << " " << tree[r].g << "\n";
        update(l, a, b, st, mid, wh, bl, tim);
        update(r, a, b, mid+1, end, wh, bl, tim);
        tree[v].w = tree[l].w + tree[r].w;
        tree[v].b = tree[l].b + tree[r].b;
        tree[v].g = tree[l].g + tree[r].g;
        // if(tree[v].g == 1) cout << l << " " << r << " XXX\n";
        // timer[v] = max(timer[l], timer[r]);
        // cout << "X: " << st << " " << end << " " << tree[v].w << " " << tree[v].b << " " << tree[v].g << "\n";
        for(int i = 1; i < 2*base; i++) cout << tree[i].w << "," << tree[i].b << "," << tree[i].g << "," << timer[i] << " | ";
        cout << "\n" << "\n";
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= q; i++) {
        int t, l, r;
        char c;
        cin >> t >> l >> r >> c;
        if(c == 'W') {
            if(t == 0) update(1, l, r, 1, base, 0, -1, i);
            else update(1, l, r, 1, base, 1, -1, i);
        }
        else if(c == 'B') {
            if(t == 0) update(1, l, r, 1, base, -1, 0, i);
            else update(1, l, r, 1, base, -1, 1, i);
        }
        cout << tree[1].g << "\n";
    }
    return 0;
}