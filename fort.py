m = int(input())
for j in range(m):
   print('Month #'+str(j+1)+':')
   n = int(input())

   totalw = 0;
   totalb = 0;
   totalm = 0;

   for i in range(n):
      inp = input().split(" ")
      w = int(inp[0])
      b = int(inp[1])
      m = int(inp[2])
      
      totalw += w
      totalb += b
      totalm += m
      
      print('Day #'+str(i+1)+': Collected '+str(w)+' wood, '+str(b)+' brick, and '+str(m)+' metal.')

   print('Collected a total of '+str(totalw)+' wood, '+str(totalb)+' brick, and '+str(totalm)+' metal!')
   print()
