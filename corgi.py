# Solution to Charles and the Corgi Conundrum
# by Jacob Magnuson

import sys
sys.setrecursionlimit(1001) # default is set to 1000 :(

# Read number of testcases
T = int(input())

for t in range(T):
    # Read number of nodes and edges
    n, m = map(int, input().split())
    # Create adjacency list
    adj = [[] for i in range(n)]

    # Read in edges and populate adjacency list
    for i in range(m):
        u, v = map(lambda x: int(x) - 1, input().split())
        adj[u].append(v)
        adj[v].append(u)

    # Array to mark whether we've seen a node before
    vis = [False] * n

    # DFS which returns the size of n's component
    def size(n):
        vis[n] = True
        res = 1
        for y in adj[n]:
            if not vis[y]:
                res += size(y)
        return res

    # Store result
    res = 0

    '''
    Suppose Corgi X is a member of a connected friend network of size k.
    If any of those k Corgis are chosen, then Corgi X will be chosen as well.
    The probability that this Corgi goes home with Charles, then, is k / n.
    
    By linearity of expectation, our answer is equal to the sum of this value
    over all corgis. Since all corgis in the same size-k component have the
    same probability of being chosen, we can sum k * k / n for each component.
    '''

    # For each node, if we've not seen it before, add the answer for the
    # component to which it belongs to our final answer.
    for r in range(n):
        if not vis[r]:
            res += size(r) ** 2 / n

    # Print the answer!
    print("Pond #%d: %.3f" % (t + 1, res))
