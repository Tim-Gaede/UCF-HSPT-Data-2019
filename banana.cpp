// Solution to He's Got the Banana!
// by Jacob Magnuson

#include<bits/stdc++.h>
using namespace std;

int main(){
    string item;
    int T, t;
    cin >> T;
    for(t = 0; t < T; t++) {
        cin >> item;
		if(item == "banana")
			cout << "He's got the banana!" << endl;
		else
			cout << "Oh, bummer." << endl;
    }
    return 0;
}
