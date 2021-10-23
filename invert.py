# Solution to Invertomancer
# by Jacob Magnuson

# Read number of testcases
T = int(input())

for t in range(T):
    # Read rows, columns, max climb height, and grid
    R, C, K = map(int, input().split())
    grid = [input() for i in range(R)]
    # We initialize the heights to 1
    heights = [1] * C
    # Now we will compute the actual height of each column
    for c in range(C):
        while grid[-heights[c] - 1][c] == '#':
            heights[c] += 1

    # Keep track of how many times we invert the world
    flips = 0
    for at in range(C - 1):
        # If the next step is higher than the invertomancer can
        # climb, then we must invert!
        if heights[at + 1] - heights[at] > K:
            # Increment our counter
            flips += 1
            # Invert the world
            heights = [R - x for x in heights]

    # Print the answer
    print("World #%d: %d" % (t + 1, flips))
    
        
        
        
