#include <bits/stdc++.h>
using namespace std;

int occ[18][131072] = {0}, power[18];

int check(int L) {
    for(int i = 1; i <= L; i++) {
        for(int j = 0; j < power[i]; j++) {
            if(occ[i][j] == 0)
                return i;
        }
    }
    return L;
}

void changeOcc(char x, int sub, int pos, int a, int i) {
    if(x == '0') {
            sub += power[pos];
            occ[i][sub]++;
            sub -= power[pos];
    }
    else {
        sub -= power[pos];
        occ[i][sub]++;
        sub += power[pos];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    char *tab = new char[n];
    cin >> tab;
    int L = (int) log2(n) + 1, mask = 1, sub;
    //vector<int> power(L+1);
    power[0] = 1;
    for(int i = 1; i <= L; i++)
        power[i] = power[i-1]*2;
    //vector<vector<int>> occ(L+1, vector<int> (power[L], 0));

    
    for(int i = 1; i <= L; i++) {
        sub = 0;
        mask = power[i]-1;
        for(int j = 0; j < i; j++) {
            sub <<= 1;
            sub += tab[j] - '0';
        }
        occ[i][sub]++;
        for(int j = i; j < n; j++) {
            sub <<= 1;
            sub += tab[j] - '0';
            sub &= mask;
            occ[i][sub]++;
        }
    }
    cout << check(L) << "\n";

    while(m--) {
        int a;
        cin >> a;
        for(int i = 1; i <= L; i++) {
            sub = 0; mask = power[i]-1;
            for(int j = max(a-i, 0); j < max(a-i, 0)+i; j++) {
                sub <<= 1;
                sub += tab[j] - '0';
            }
            occ[i][sub]--;
            int pos;
            if(a-i >= 0)
                pos = 0;
            else
                pos = i-a;
            changeOcc(tab[a-1], sub, pos, a, i);           
            for(int j = max(a-i, 0)+i; j < min(n, a+i-1); j++) {
                pos++;
                sub <<= 1;
                sub += tab[j] - '0';
                sub &= mask;
                occ[i][sub]--;
                changeOcc(tab[a-1], sub, pos, a, i);
            }
        }
        if(tab[a-1] == '0') tab[a-1] = '1';
        else tab[a-1] = '0';
        cout << check(L) << "\n";
    }
    delete[] tab;
    return 0;
}