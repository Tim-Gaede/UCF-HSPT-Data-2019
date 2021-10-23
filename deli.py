# Python implementation of Binary Indexed Tree - Courtesy of Geeksforgeeks

# https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
  
# Returns sum of arr[0..index]. This function assumes 
# that the array is preprocessed and partial sums of 
# array elements are stored in BITree[]. 

log = 31

# This is unique to this problem
# Binary search the tree for the first index i such that the sum from 0 to i-1 is strictly greater than v
def lift(BITTree, n, i, v):
	v += sum(BITTree, 0, i-1)
	tot = 0
	pos = 0
	for i in reversed(range(log+1)):
		if(pos + (1 << i) > n):
			continue
		if(tot + BITTree[pos + (1 << i)] > v):
			continue
		tot += BITTree[pos+(1 << i)]
		pos += (1 << i)
	return pos;

def sum(BITTree, l, r):
	if(r < l):
		return 0
	return getsum(BITTree, r)-getsum(BITTree, l-1)

def getsum(BITTree,i): 
    s = 0 #initialize result 
  
    # index in BITree[] is 1 more than the index in arr[] 
    i = i+1
  
    # Traverse ancestors of BITree[index] 
    while i > 0: 
  
        # Add current element of BITree to sum 
        s += BITTree[i] 
  
        # Move index to parent node in getSum View 
        i -= i & (-i) 
    return s 
  
# Updates a node in Binary Index Tree (BITree) at given index 
# in BITree. The given value 'val' is added to BITree[i] and 
# all of its ancestors in tree. 
def updatebit(BITTree , n , i ,v): 
  
    # index in BITree[] is 1 more than the index in arr[] 
    i += 1
  
    # Traverse all ancestors and add 'val' 
    while i <= n: 
  
        # Add 'val' to current node of BI Tree 
        BITTree[i] += v 
  
        # Update index to that of parent in update View 
        i += i & (-i)
  
  
# Constructs and returns a Binary Indexed Tree for given 
# array of size n. 
def construct(arr, n): 
  
    # Create and initialize BITree[] as 0 
    BITTree = [0]*(n+1) 
  
    # Store the actual values in BITree[] using update() 
    for i in range(n): 
        updatebit(BITTree, n, i, arr[i]) 
  
    return BITTree 


cases = int(input())
for q in range(cases):
	print('Scenario #'+str(q+1)+':')
	inp = input().split(" ")
	n = int(inp[0])
	m = int(inp[1])
	empty = [0]*n
	a = [0]*n
	
	sums = [construct(empty, n) for i in range(log)]
	cnts = [construct(empty, n) for i in range(log)]
	
	inp = input().split(" ")
	for i in range(n):
		a[i] = int(inp[i])
		
		for j in range(log):
			pow = 1 << j
			if(a[i] > pow):
				continue
			updatebit(sums[j], n, i, a[i])
			updatebit(cnts[j], n, i, 1)
			
	for query in range(m):
		inp = input().split(" ")
		type = int(inp[0])
		if(type == 1):
			budget = int(inp[1])
			idx = 0
			ans = 0
			bit = 30
			while(bit >= 0 and idx < n and budget > 0):
				pow = (1 << bit) 
				if(pow > budget):
					bit = bit-1
					continue
				upto = lift(sums[bit], n, idx, budget)
				ans += sum(cnts[bit], idx, upto-1)
				budget -= sum(sums[bit], idx, upto-1)
				idx = upto
				bit = bit - 1
			print('David can get '+str(ans)+' toppings')
		else:
			idx = int(inp[1])-1
			x = int(inp[2])
			prev = a[idx]
			
			for i in range(log):
				pow = (1 << i)
				if(pow < prev):
					continue
				updatebit(sums[i], n, idx, -prev)
				updatebit(cnts[i], n, idx, -1)
			
			for i in range(log):
				pow = (1 << i)
				if(pow < x):
					continue
				updatebit(sums[i], n, idx, x)
				updatebit(cnts[i], n, idx, 1)
			
			a[idx] = x
	print()
