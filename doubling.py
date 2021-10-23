# Ellie Kozlowski
# Solution to doubling
# 02/10/19

n = int(input())

# loop thorugh queries
for i in range(n):
    m = int(input())

    # calculate answer
    ans = m - (m * 2)//10
    print("Trade #",(i + 1),": ",ans, sep='')
