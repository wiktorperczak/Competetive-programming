#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while(z--) {
        int n;
        cin >> n;
        vector<int> v0, v1, v2;
        int c2 = 0;
        for(int i = 0; i < n; i++) {
            int a;
            cin >> a;
            if(a == 0) v0.push_back(i);
            else if(a == 1) v1.push_back(i);
            else {
                c2++;
                v2.push_back(i);
            }
        }
        bool h = true;
        int p01 = n/2 - c2, id = v0.size()-1;
        if(id < p01-1) h = false;
        set<int> mySet;

        while(h && p01 > 0) {
            if(v1.empty()) {
                h = false;
                break;
            }
            int x = v1.back();
            while(v0[id] > x) {
                mySet.insert(v0[id]);
                id--;
                if(id < 0) {
                    h = false;
                    break;
                }
            }
            v1.pop_back();
            id--; p01--;
        }
        for(int i = 0; i <= id; i++) mySet.insert(v0[i]);
        for(auto i : v1) mySet.insert(i);
        for(auto i : v2) {
            if(mySet.empty() || *mySet.begin() > i) {
                h = false;
                break;
            }
            mySet.erase(mySet.begin());
        }
        if(!mySet.empty()) h = false;
        cout << (h ? "TAK\n" : "NIE\n");
    }
    return 0;
}