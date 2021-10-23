# Solution to Life Decisions
#
# Main idea:
#   Process the edges in order of absolute value - this way the order of edges in any valid path
#   corresponds to the order they were processed.  Then, keep track for each node of the longest
#   path that has been found which ends there, as well as the longest path which hasn't "gone bad".
#   When considering an edge from a to b, try appending it to the longest paths ending at a to
#   update the longest paths ending at b.  All edges with the same absolute value are processed
#   together, and the updates to saved path lengths are not performed until all such edges have been
#   looked at.

T = int(input())

for t in range(1, T+1):

    # Get size of life graph
    n, m = map(int, input().split())
    edges = []
    
    # Read in edges
    for i in range(0, m):
        a, b, h = map(int, input().split())
        edges.append((a-1, b-1, h))
        
    # Sort the edges by absolute value
    edges = sorted(edges, key = lambda x: abs(x[2]))
    
    # lp is the longest path ending at each node - tuple of (path length, last weight)
    lp = [-1 for i in range(0, n)]
    lp[0] = 0
    
    # lpp is longest positive path ending at each node - tuple of (path length, last weight)
    # No negative edges can be used in these paths
    lpp = [-1 for i in range(0, n)]
    lpp[0] = 0
    
    # Iterate over all edges
    first = 0
    while first < m:
    
        # [first, last) will contain all edges with the same absolute value
        last = first+1
        while last < m and abs(edges[last][2]) == abs(edges[first][2]):
            last += 1
            
        # Process a batch of all edges with the same absolute value, and save all updates to be done at once
        # This prevents paths containing multiple edges with the same absolute value from being produced
        updateLp = {}
        updateLpp = {}
        for i in range(first, last):
            a, b, h = edges[i]
                
            # If h positive, update longest positive path ending at b to max(lpp[b], 1 + lpp[a])
            if h > 0 and lpp[a] != -1:
            
                # Add this edge to the longest positive path which ended at a
                if 1 + lpp[a] > lpp[b] and (b not in updateLpp or updateLpp[b] < 1 + lpp[a]):
                    updateLpp[b] = 1 + lpp[a]
            
            # If the longest positive path was updated, try updating the longest overall path to same value
            if b in updateLpp and updateLpp[b] > lp[b]:
                updateLp[b] = updateLpp[b]
                
            # If h negative, update longest path ending at b to max(lp[b], 1 + lp[a])
            if h < 0 and lp[a] != -1:
            
                # Add this edge to the longest path which ended at a
                if lp[a] + 1 > lp[b] and (b not in updateLp or updateLp[b] < 1 + lp[a]):
                    updateLp[b] = 1 + lp[a]
                    
        first = last
        
        # Now perform all saved updates
        for x in updateLp:
            lp[x] = updateLp[x]
        for x in updateLpp:
            lpp[x] = updateLpp[x]
    
    res = max(lp)
    print('Scenario #' + str(t) + ': ' + str(res))
        
    
        

