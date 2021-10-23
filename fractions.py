#John Edwards
#2019-02-13

# O(n**2) version
# handle input and sort array
for t in range(int(input())):
    n = int(input())
    l = list(map(int, input().split()))
    # loop over all pairs and count the number
    # of pairs that are good
    cnt = 0
    for i in range(n):
        for j in range(n):
            if l[i] %l[j] == 0 or l[j] %l[i] == 0:
                cnt += 1
    # if all pairs are good, this array is bae
    if cnt == n**2:
        print("Array #"+str(t+1)+": This array is bae!")
    else:
        print("Array #"+str(t+1)+": Go away!") 