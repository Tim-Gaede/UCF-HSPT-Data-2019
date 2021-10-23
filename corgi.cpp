
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

bool* visited;
vector<int>* edges;

// A depth-first search (DFS) from given corgi "node".
// Returns the number of corgis connected to and including
// corgi "node" that have not already been visited by another
// DFS. Also updates visited.
int dfs(int node){
    int corgisConnected = 1;
    for(int i=0;i<edges[node].size();i++){
        int nxt = edges[node].at(i);
        if(!visited[nxt]){
            visited[nxt] = true;
            corgisConnected+=dfs(nxt);
        }
    }
    return corgisConnected;
}

int main(void){

    // s, n, and m as defined in the problem
    int s,n,m;

    // Read in the number of corgi pond cases
    cin >> s;

    // Loop through all test cases
    for(int runm=0;runm<s;runm++){

        // Read in the values of n and m
        cin >> n >> m;

        // "visited" will represent which corgis have
            // been visited by a DFS
        visited = new bool[n+1];

        // "edges" will store a vector of adjacent corgis
            // AKA the friends of each corgi
        edges = new vector<int>[n+1];

        int a,b;

        // Read in all the edges
        for(int i=0;i<m;i++){

            cin >> a >> b;

            // Corgi "a" is now friends with corgi "b"
                // and vice-versa
            edges[a].push_back(b);
            edges[b].push_back(a);
        }

        double expectedValue = 0;
        // Loop through all corgis
        for(int i=1;i<=n;i++){
            // If this corgi wasn't friends-of-friends with
                // any of the previous corgis, then it is a new
                // set of mutually-friended corgis
            if(!visited[i]){

                visited[i] = true;
                int numConnected = dfs(i);

                // The logic here is as follows: Expected value
                    // is defined as the sum of P(x) * x for all x;
                    // Here, P(x) is the probability of choosing any corgi in
                    // this set and x is the number of corgis connected. P(x)
                    // is the chance of choosing any of these x corgis randomly,
                    // so P(x) = x/n. The value itself is how many corgis we take
                    // home, which is all connected corgis. Therefore the expected
                    // value is the sum of all x*x/n
                expectedValue+= numConnected*(double)(numConnected)/((double)n);
            }
        }
        // Print the final answer for this case to 3 decimal places
        cout << "Pond #" << (runm+1) << ": " << fixed << setprecision(3) << expectedValue << endl;
    }
    return 0;
}
/**
2
4 2
1 2
3 4
10 6
1 3
3 2
7 5
10 8
4 3
9 10

*/
