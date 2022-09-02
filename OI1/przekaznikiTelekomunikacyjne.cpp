#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

constexpr int H = 19;
constexpr int base = 1<<H;
double tree[2*base];
pair<double, double> add[2*base];

void insert(int i, int beg, int end, int a, int b, int x, double s, double d) {
    int len = 1 << (int)(H - (int) log2(i));
    if(beg > b || end < a) return;
    else if(beg >= a && end <= b) {
        double solution = ((s - d*(abs(x-beg)) + s - d*(abs(x-end)))/2) * (end-beg+1);
        tree[i] += solution;
        add[i].st += solution;
        if(abs(x-beg) < abs(x-end)) 
            add[i].nd -= d;
        else 
            add[i].nd += d;
    }
    else {
        int l = i*2, r = i*2+1, mid = (beg+end)/2;
        double Val, v;
        if(add[i].nd > 0) {
            v = (add[i].st - add[i].nd * len * (len-1)/2)/2;
            Val = v + add[i].nd/2 * len/2 * (len/2-1);
            tree[l] += Val;
            tree[r] += add[i].st - Val;
            add[l].st += Val;
            add[r].st += add[i].st - Val;
        }
        else {
            v = (add[i].st + add[i].nd * len * (len-1)/2)/2;
            Val = v - add[i].nd/2 * len/2 * (len/2-1);
            tree[r] += Val;
            tree[l] += add[i].st - Val;
            add[r].st += Val;
            add[l].st += add[i].st - Val;
        }
        add[l].nd += add[i].nd;
        add[r].nd += add[i].nd;
        add[i].st = 0; add[i].nd = 0;
        
        insert(i*2, beg, mid, a, b, x, s, d);
        insert(i*2+1, mid+1, end, a, b, x, s, d);
        tree[i] = tree[l] + tree[r];
    }
}

double query(int i, int beg, int end, int a, int b) {
    int len = 1 << (int)(H - (int) log2(i));
    if(beg > b || end < a) return 0;
    else if(beg >= a && end <= b) return tree[i];
    else {
        int l = i*2, r = i*2+1, mid = (beg+end)/2;
        double Val, v;
        if(add[i].nd > 0) {
            v = (add[i].st - add[i].nd * len * (len-1)/2)/2;
            Val = v + add[i].nd/2 * len/2 * (len/2-1);
            tree[l] += Val;
            tree[r] += add[i].st - Val;
            add[l].st += Val;
            add[r].st += add[i].st - Val;
        }
        else {
            v = (add[i].st + add[i].nd * len * (len-1)/2)/2;           
            Val = v - add[i].nd/2 * len/2 * (len/2-1);
            tree[r] += Val;
            tree[l] += add[i].st - Val;
            add[r].st += Val;
            add[l].st += add[i].st - Val;
        }
        add[l].nd += add[i].nd;
        add[r].nd += add[i].nd;
        add[i].st = 0; add[i].nd = 0;

        return query(i*2, beg, mid, a, b) + query(i*2+1, mid+1, end, a, b);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.precision(19);

    int n, m;
    cin >> n >> m;
    pair<double, double> queries[n+1] = {{0, 0}};
    while(m--) {
        char c;
        cin >> c;
        double x, x1, s, a;
        if(c == 'P') {
            cin >> x >> s >> a;
            queries[(int) x] = {s, a};
            insert(1, 1, base, max((double) 1, x - floor((s-1)/a)), x, x, s, a);
            if(x != n) insert(1, 1, base, x+1, min((double) n, x + floor((s-1)/a)), x, s, a);
        }
        else if(c == 'U') {
            cin >> x;
            s = queries[(int) x].st;
            a = queries[(int) x].nd;
            insert(1, 1, base, max((double) 1, x - floor((s-1)/a)), x, x, -s, -a);
            if(x != n) insert(1, 1, base, x+1, min((double) n, x + floor((s-1)/a)), x, -s, -a);
        }
        else if(c == 'Z') {
            cin >> x >> x1;
            cout << floor(query(1, 1, base, x, x1) / (x1-x+1)) << "\n";
        }
    }
    return 0;
}