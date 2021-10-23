#include <bits/stdc++.h>

using namespace std;

int main() {
	int t;
	cin >> t;
	
	// loop through each test case
	for(int tt = 1 ; tt <= t ; tt++) {
		int m;
		cin >> m;
		
		// You can just divide m by 5 is because
		// the first thing needed is to double the number,
		// so 2m is the current total, then to delete the
		// last digit of this total, you can just divide by 10.
		// Because you of how integers divide, it automatically
		// rounds down, which just deletes the last digit. Since
		// 2m and 10 have a common factor of 2, it cancels out,
		// so 2m / 10 = m / 5
		int answer = m - (m / 5);
		cout << "Trade #" << tt << ": " << answer << endl;
	}
	
	return 0;
}