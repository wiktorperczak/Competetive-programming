#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	string s, t;
	cin >> s >> t;

	int ss = (int) s.length(), tt = (int) t.length();
	vector<vector<string>> lcs(2, vector<string> (tt + 1));

	for(int i = 0; i <= tt; i++) {
		lcs[0][i] = "";
		lcs[1][i] = "";
	}

    int x;
	for(int i = 1; i <= ss; i++) {
        x = i%2;

		for(int j = 1; j <= tt; j++) {
			if(s[i - 1] == t[j - 1])
				lcs[x][j] = lcs[abs(x - 1)][j - 1] + s[i - 1];
			else if((int) lcs[x][j - 1].length() >= (int) lcs[abs(x - 1)][j].length())
				lcs[x][j] = lcs[x][j - 1];
			else
				lcs[x][j] = lcs[abs(x - 1)][j];
		}
	}

    x = ss%2;
	cout << lcs[x][tt].length() << "\n" << lcs[x][tt] << "\n";
	
	return 0;
}













#include "bits/stdc++.h"

using namespace std;


int q,r,s;
string a, b;
int dp[5002][5002];
char kierunek[5002][5002];
stack<char>literki;

int main(){
  	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0); 
	  
	cin>>a>>b;
	
	for (int i=1; i<=a.length(); i++){
		for (int j=1; j<=b.length(); j++) {
			if (a[i-1]==b[j-1])
				dp[i][j]=dp[i-1][j-1]+1;
			
			else
				dp[i][j]=max(dp[i-1][j], dp[i][j-1]); 	} }
	cout<<dp[a.size()][b.size()]<<endl;
	
	int i=a.size();
	int j=b.size(); 
	
	while (i>0 && j>0) {
		q=dp[i-1][j];
		r=dp[i][j-1];
		s=max(q,r); 
		if (dp[i][j]>s){
			literki.push(a[i-1]);
			i--;
			j--;}
		else if (s==q)
			i--;
		else if (s==r)
			j--;
		 }
	
	while (literki.size()){
		char znak=literki.top();
		literki.pop();
		cout<<znak;}
	
	return 0;
}