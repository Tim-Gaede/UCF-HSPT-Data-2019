# Solution for k-Diverse from 2019 HSPT contest @ UCF
# By Dylan Lyon

# This converts our digit array to a string representation
def tostr():
	out = ""
	flag = True
	for x in range(19,-1,-1):
		if digits[x] is not 0 or not flag:
			out = out+str(digits[x])
			flag = False
	return out


# This is a way to increment our digit array in base 10
def increment(index):
        # if digits[index] is 9 we need to carry the 1
	if digits[index] is 9:
		increment(index+1)
		return
	# Increase this index, set all trailing digits to 0
        #   to ensure our answer is minimal
	digits[index] = digits[index]+1
	for x in range(0,index):
		digits[x] = 0

# This recursive function is our solver
# Param index : Digit we're interested in
# Param leadingZero : Whether we haven't hit the first
#   significant digit yet (so we're not overcounting zeroes)
def backtracker(index, leadingZero):
        # WE FOUND THE SOLUTION
	if index<0:
		return
	# The current number is too large to be a solution
            # for n <= 10^18
	if digits[19]>0:
		return

        # This is a significant digit        
	if not leadingZero or digits[index] is not 0:
                # We now have one more digit
		countDigits[digits[index]] += 1

		# If this is true, we have too many of current digit
		if(countDigits[digits[index]]>k):
                        # increase the number
			increment(index)
			# set all trailing digits to zero,
                        #   ensuring that our final answer is minimal
			for x in range(0,10):
				countDigits[x] = 0
			# start completely over again
			backtracker(19,True)
                # The soln is fine so far, continue
		else:
			backtracker(index-1,False)
        # This is just a leading zero, keep going
	else:
		backtracker(index-1,True)

# The number of test cases
t = int(input())
# This variable will store each n
n = 0
# This variable will store each k
k = 0
for testNum in range(0,t):
    # read input
    vals = input().split()
    n = int(vals[0])
    k = int(vals[1])

    # The digits of our final answer, one digit per index
    digits = [0]*20
    # A count of the number of appearances of the digits
    countDigits = [0]*10

    # Account for the infinite / impossible case; This would
    #   cause your program to TLE and is a great insight to solving
    #   this problem
    if n>9876543210 and k is 1:
            digits[19] = 1
    else:
            # Transfer the digits of n into the digits array
            place = 0
            while n>0:
                    digits[place] = n%10
                    place+=1
                    n = n//10
            # Now use the backtracker to solve for a k-diverse number
            #   greater than or equal to n
            backtracker(19,True)

    # Our answer was invalid
    if digits[19]>0:
            print("Find a different k")
    # Our answer was valid
    else:
            print(tostr())
