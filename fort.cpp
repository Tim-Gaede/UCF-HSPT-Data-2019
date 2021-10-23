#include<iostream>

using namespace std;

int main() {
   int m;

   // Read in number of months
   cin>>m;

   // Loop over each month
   int j;
   for(j = 1; j <= m; j++) {
      // Output month header
      cout << "Month #" << j << ":" << endl;

      // Read in number of days
      int n;
      cin>>n;

      // Process each day, output that day, and sum
      int i;
      int totW = 0, totB = 0, totM = 0;
      for(i = 1; i <= n; i++) {
         int curW, curB, curM;
         cin >> curW >> curB >> curM;
         cout << "Day #" << i << ": Collected " << curW << " wood, " << curB << " brick, " << "and " << curM << " metal." << endl;
         totW += curW;
         totB += curB;
         totM += curM;
      }

      // Output totals for the month
      cout << "Collected a total of " << totW << " wood, " << totB << " brick, " << "and " << totM << " metal!" << endl << endl;
   }
}
