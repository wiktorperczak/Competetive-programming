#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char *argv[]) {
    srand(atoi(argv[1]));

    int n = rand(1, 2e5), m = rand(1, 2e5), q = rand(1, 2e5);
    cout << n << " " << m << " " << q << "\n";
    for(int i = 0; i < m; i++) {
        int l = rand(1, n), r = rand(l, n);
        cout << l << " " << r << "\n";
    }
    set<int> plus;
    while(q--) {
        int los = rand(1, 3);
        if(los == 1) {
            int l = rand(1, n), r = rand(l, n);
            cout << "? " << l << " " << r << "\n";
        }
        else if(los == 2) {
            int x = rand(1, m);
            if(plus.find(x) == plus.end()) {
                cout << "+ " << x << "\n";
                plus.insert(x);
            }
            else {
                cout << "- " << x << "\n";
                plus.erase(x);
            }
        }
        else if(los == 3) {
            int x = rand(1, m);
            if(plus.find(x) != plus.end()) {
                cout << "- " << x << "\n";
                plus.erase(x);
            }
            else  {
                cout << "+ " << x << "\n";
                plus.insert(x);
            }
        }
    }
    return 0;
}