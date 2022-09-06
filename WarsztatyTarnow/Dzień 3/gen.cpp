#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char *argv[]) {
    srand(atoi(argv[1]));

    int n = rand(1, 8), q = rand(1, 6);
    cout << n << " " << q << "\n";
    while(q--) {
        int t = rand(0, 1), l = rand(1, n), r = rand(l, n);
        int x = rand(0, 1);
        char c;
        if(x == 0) c = 'W';
        else c = 'B';
        cout << t << " " << l << " " << r << " " << c << "\n";
    }
    return 0;
}