#John Edwards
#2019-02-22

def dist(x1, y1, x2, y2):
    x = x1 - x2
    y = y1 - y2
    return ((x ** 2) + (y ** 2)) ** (1.0 / 2)

def go1(y, w1, w2):
    return dist(1.0*w1*w2/y, w1, w2, y)

def go2(y, w2, w3):
    return dist(-w2, y, 1.0*w2*w3/y, -w3)

for t in range(int(input())):
    l = list(map(int, input().split()))
    
    min1 = 1e18
    lo = -l[3]
    hi = 0
    for i in range(200):
        delta = (hi - lo)/3
        mid1 = lo + delta
        mid2 = hi - delta
        d1 = go1(mid1, l[0], l[1])
        d2 = go1(mid2, l[0], l[1])
        if (d1 < d2):
            hi = mid2
        else:
            lo = mid1
    min1 = go1(lo, l[0], l[1])
    
    min2 = 1e18
    lo = 0
    hi = l[3]
    for i in range(200):
        delta = (hi - lo)/3
        mid1 = lo + delta
        mid2 = hi - delta
        d1 = go2(mid1, l[1], l[2])
        d2 = go2(mid2, l[1], l[2])
        if (d1 < d2):
            hi = mid2
        else:
            lo = mid1
    min2 = go2(lo, l[1], l[2])
    print('Track Blueprint #'+str(t+1)+': {0:.7f}'.format(min(min1, min2)))