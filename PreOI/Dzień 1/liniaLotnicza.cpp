#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    if(n == 2 || n == 3 || n == 6 || n == 7 || n == 10) cout << "NIE\n";
    else if(n == 1) cout << "TAK\n" << "1 1\n";
    else if(n == 4) cout << "TAK\n" << "4 2 3 2 4 3 1 1\n"; 
    else if(n == 5) cout << "TAK\n" << "5 1 1 3 4 5 3 2 4 2\n";
    else if(n == 8) cout << "TAK\n" << "8 4 7 3 6 4 3 5 8 7 6 2 5 2 1 1\n";
    else if(n == 9) cout << "TAK\n" << "9 4 8 3 7 4 3 5 6 9 8 7 5 2 6 2 1 1\n";
    return 0;
}