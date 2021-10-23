# Ellie Kozlowski
# Solution to sentence
# 02/10/19

n = int(input())

# loop through queries
for i in range(n):
    m = int(input())
    sentence = input()

    # loops through sentence and counts number of upper and lower case letters
    numUpper = sum(1 for c in sentence if c.isupper())
    numLower = sum(1 for c in sentence if c.islower())

    # checks to see if sentence is balanced
    if numUpper == numLower:
        print("Sentence #",(i + 1),": Yes", sep='')
    else:
        print("Sentence #",(i + 1),": No", sep='')
    
    
