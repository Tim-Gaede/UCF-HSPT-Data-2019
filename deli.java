//Author: Atharva Nagarkar
//Solution to David and the Deli

import java.io.*;
import java.util.*;

public class deli {
	
	final int log = 31;
	
	public void solve(FS in, PrintWriter out) {
		//read in number of cases
		int cases = in.nextInt();
		
		//process each case
		for(int t = 1; t <= cases; ++t) {
			//header for each case
			out.printf("Scenario #%d:%n", t);
			
			//read in number of elements and number of queries
			int n = in.nextInt();
			int m = in.nextInt();
			
			//make an array for the cost of each item
			long[] a = new long[n];
			
			//keep 2 arrays of Binary Indexed Trees
			//each Tree will keep an answer for it's respective
			//bit and and all bits under it
			
			//sums[i].sum(L, R) will keep the sum of costs from 
			//index L to R of items whose cost is less than or 
			//equal to 2^i
			BIT[] sums = new BIT[log];
			
			//cnts[i].sum(L, R) will keep the number of items
			//from index L to R whose cost is less than or equal
			//to 2^i
			BIT[] cnts = new BIT[log];
			
			//initialize our binary indexed trees
			for(int i = 0; i < log; ++i) {
				sums[i] = new BIT(n);
				cnts[i] = new BIT(n);
			}
			
			//read in the costs for the items
			for(int i = 0; i < n; ++i) {
				a[i] = in.nextLong(); //cost for item i
				//update the corresponding trees
				for(int j = 0; j < log; ++j) {
					long pow = 1L << j;
					if(a[i] > pow) continue; //if 2^j is too small, then continue
					sums[j].update(i, a[i]); //add the value of a[i] to the i'th index of the j'th tree
					cnts[j].update(i, 1); //add 1 to the i'th index of the j'th tree
				}
			}
			
			//let's process queries
			while(m-->0) {
				int type = in.nextInt(); //what type of query
				if(type == 1) { //give max number of items that can be chosen
					long budget = in.nextLong(); //see what his budget is for the query
					int idx = 0; //keep track of the item he is currently viewing to buy, but has not bought yet
					int ans = 0; //out answer to the query, the number of things he can buy
					for(int bit = log - 1; idx < n && bit >= 0; --bit) { //loop through all bits in the binary representation of the budget
						long pow = 1L << bit;
						if(pow > budget) continue; //if this amount is too big for the budget, we can't buy anything with this cost
						int upto = sums[bit].lift(budget, idx); //see how far right we can go given our current budget, starting at idx (our current index)
						ans += cnts[bit].sum(idx, upto - 1); //add the number of valid items in this range for the current bit to our answer
						budget -= sums[bit].sum(idx, upto - 1); //take out the sum of costs for taking the items
						idx = upto; //update current index to the new thing we are looking at
					}
					out.printf("David can get %d toppings%n", ans); //output the answer
				} 
				else { //update query
					int ind = in.nextInt() - 1; //see which index we are updating
					long x = in.nextLong(); //our new value
					long prev = a[ind]; //our current value
					
					//first lets take out all the contributions of the previous value
					for(int bit = 0; bit < log; ++bit) {
						long pow = 1L << bit;
						if(pow < prev) continue;
						sums[bit].update(ind, -prev); //update the sum contribution
						cnts[bit].update(ind, -1); //also the count contribution
					}
					
					//now lets update all things that the new value will contribute to
					for(int bit = 0; bit < log; ++bit) {
						long pow = 1L << bit;
						if(pow < x) continue;
						sums[bit].update(ind, x); //update the sum contribution
						cnts[bit].update(ind, 1); //also the count contribution
					}
					
					a[ind] = x; //update our value in the array to the new one
				}
			}
			out.println(); //blank line after each scenario
		}
	}
	
	public static void main(String[] args) {
		FS in = new FS();
		PrintWriter out = new PrintWriter(System.out);
		new deli().solve(in, out);
		out.close();
	}
	
	//a standard binary indexed tree for log(n) range sum and log(n) updates
	class BIT {
		int n;
		long[] tree;
		
		public BIT(int nn) {
			n = nn + 10;
			tree = new long[n + 1];
		}
		
		//binary search the tree for the first index i such that the sum from
		//l to i is strictly greater than v
		int lift(long v, int l) {
			v += sum(0, l - 1);
			long sum = 0;
			int pos = 0;
			for(int i = log; i >= 0; --i) {
				if(pos + (1L << i) >= n) continue;
				if(sum + tree[pos + (1 << i)] > v) continue;
				sum += tree[pos + (1 << i)];
				pos += (1 << i);
			}
			return 1 + pos - 5;
		}
		
		long read(int i) {
			i += 5;
			long sum = 0;
			while (i > 0) {
				sum += tree[i];
				i -= i & -i;
			}
			return sum;
		}
		
		long sum(int l, int r) {
			if(r < l) return 0;
			return read(r) - read(l - 1);
		}
		
		void update(int i, long val) {
			i += 5;
			while (i <= n) {
				tree[i] += val;
				i += i & -i;
			}
		}
	}
	
	static class FS {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer("");
		String next() {
			try {
				while(!st.hasMoreElements()) {
					st = new StringTokenizer(br.readLine());
				}
			} catch(Exception e) {}
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
		long nextLong() {
			return Long.parseLong(next());
		}
	}
}
