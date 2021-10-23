import java.util.*;

//John Edwards
//2019-02-11

public class corgi
{
    static boolean[] v; //stores which nodes have been visited
    static ArrayList<Integer>[] G; //stores edges as an adjacency list
    
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        int t = 1, T = in.nextInt();
        
        while (t <= T) //for each test case
        {
            int n = in.nextInt(), m = in.nextInt();
            G = new ArrayList[n]; //create the adjacency list
            for (int i = 0; i < n; i++)
                G[i] = new ArrayList<>();
            
            for (int i = 0; i < m; i++) //intialize the adjacency list
            {
                int a = in.nextInt()-1, b = in.nextInt()-1;
                G[a].add(b); G[b].add(a);
            }
            
            double ans = 0; //will store the final expected value (E.V.)
            v = new boolean[n]; //intitialize the visited array
            for (int i = 0; i < n; i++) //bfs from each unvisited node
                if (!v[i])
                {
                    int size = bfs(i, n); //get size of this node's component
                    //each corgi is picked with probability 1/n and will 
                    //bring size corgis with it, contributing size/n to the E.V.
                    //this happens for size corgis in the component
                    ans += (size*size)/(1.0*n); 
                }
                
            System.out.printf("Pond #%d: %.3f%n", t++, ans);
        }
        
        in.close();
    }
    
    //bfs from at and return the size of its connected component
    public static int bfs(int at, int n)
    {
        v[at] = true;
        ArrayDeque<Integer> Q = new ArrayDeque<>();
        Q.add(at);
        
        int cnt = 1;
        while (!Q.isEmpty())
        {
            int cur = Q.poll();
            for (int i : G[cur])
                if (!v[i])
                {
                    v[i] = true;
                    Q.add(i);
                    cnt++;
                }
        }
        
        return cnt;
    }
}