
import java.util.Arrays;
import java.util.Scanner;
import java.util.TreeSet;

/** 
 * @author Andy Phan
 */
public class life implements Runnable {
    static TreeSet<Edge>[] pos;
    static TreeSet<Edge>[] neg;
    static TreeSet<Edge>[] cur;
    static int[] dp;
    static boolean[] done;
    static Edge[] edges;
    
    public static void main(String[] args) {
        new Thread(null, new life(), "Stack-trick", 1L<<30).start(); //using stack-trick to prevent stack-overflow
    }
    
    public void run() {
        Scanner in = new Scanner(System.in);
        int s = in.nextInt();
        for(int s1 = 1; s1 <= s; s1++) {
            int n = in.nextInt();
            int m = in.nextInt();
            pos = new TreeSet[n];
            neg = new TreeSet[n];
            cur = new TreeSet[n];
            for(int i = 0; i < n; i++) { //initialize treesets
                pos[i] = new TreeSet<>();
                neg[i] = new TreeSet<>();
                cur[i] = new TreeSet<>();
            }
            dp = new int[m];
            done = new boolean[m];
            edges = new Edge[m];
            for(int i = 0; i < m; i++) edges[i] = new Edge(in.nextInt()-1, in.nextInt()-1, in.nextInt(), i); //read in edges
            Arrays.sort(edges);
            for(int i = 0; i < m; i++) { //assign edges to correct treesets
                edges[i].id = i;
                if(edges[i].weight < 0) {
                    neg[edges[i].start].add(edges[i]);
                } else {
                    pos[edges[i].start].add(edges[i]);
                }
                cur[edges[i].start].add(edges[i]);
            }
            System.out.printf("Scenario #%d: %d\n", s1, Math.max(!neg[0].isEmpty() ? dp(neg[0].first().id)+1 : 0, !pos[0].isEmpty() ? dp(pos[0].first().id)+1 : 0));
        }
    }
    
    static int dp(int id) {
        if(done[id]) return dp[id]; //this means that we have already calculated the answer for this edge
        done[id] = true;
        Edge edge = edges[id];
        int max = 0;
        Edge up = new Edge(0, 0, Math.abs(edge.weight)+1, 0); //starting from this edge, the next edge that we travel across has to have weight at least weight+1
        Edge next = neg[edge.end].ceiling(up); //so use TreeSet.ceiling(), which returns the smallest one greater than or equal to the input in the TreeSet
        if(next != null) max = dp(next.id)+1;
        if(edge.weight >= 0) { //we can only go to a positive edge if the current edge is also positive
            next = pos[edge.end].ceiling(up);
            if(next != null) max = Math.max(max, dp(next.id)+1);
        }
        up = new Edge(0, 0, edge.weight, id+1); //we can also try to use the next edge leading away from the source of this one
        next = neg[edge.start].ceiling(up);
        if(next != null) max = Math.max(max, dp(next.id));
        if(edge.weight > 0) {
            next = pos[edge.start].ceiling(up);
            if(next != null) max = Math.max(max, dp(next.id));
        }
        return dp[id] = max;
    }
    
    static class Edge implements Comparable<Edge> { //custom edge class
        int start, end, weight, id;

        public Edge(int start1, int end1, int weight1) {
            start = start1;
            end = end1;
            weight = weight1;
        }
        
        public Edge(int start1, int end1, int weight1, int id1) {
            this(start1, end1, weight1);
            id = id1;
        }
        
        @Override
        public int compareTo(Edge o) {
            if(Math.abs(weight) == Math.abs(o.weight)) return id - o.id;
            return Math.abs(weight)-Math.abs(o.weight);
        }
        
    }
}
