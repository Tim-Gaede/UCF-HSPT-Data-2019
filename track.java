//Author: Atharva Nagarkar
//Solution to Huge Super Perfect Track

import java.io.PrintWriter;
import java.util.Scanner;

public class track {
	
/*

Let's refer to this diagram for the explanation of the solution.


                          w2
                          |
                          v

                ------------A
                            |     <-- w1
                -------B    |	    
                       |    |	    
                       |    |	  <-- L
                       |    |       
                       |    |	    
                       |    D----------
          w3 -->       |
                       C---------------


We can observe that there are 2 turns: the top one (turning right) and the bottom one (turning left).
Let's look at the top turn. Suppose we have our vehicle turn left, but not touch point B.
Our vehicle (a line segment) would have two end-points on the top segment and the segment A->D.
Seeing this, we can see that if we were to make our vehicle touch point B, then the distance between
the left end-point and right end-point will always increase. Thus we can conclude that the optimal turn
for the top will have the vehicle always touching point B. A similar argument can be made for the bottom turn
in which the vehicle always touches point D when turning.

Now that we know this, we can see that our maximum vehicle length will be the minimum of the limiting lengths
that the two turns will allow. So let's see how to find the answer for a particular turn...

For turning across point B (the top, right turn), let us define our vehicle to be the segment that passes through
point B and some other point P on the segment A->D. Since we want to fix P to be on the segment A-D, we know that
the x-coordinate of P will be B.x + w2. This leaves for us to determine the y-coordinate for the point.
The y-coordinate has to be between B.y and D.y (going any further up or down wouldn't really be possible).
If one were to draw some pictures of segments passing through point B and multiple points P on A->D, it can be seen
that the lengths of the segments are unimodal (decreasing from top to some point P, then increasing from P to bottom).
We would like to find this P in which the length of the segment is minimal. This can be achieved with a ternary search.
The same logic applies to the other turn, so our solution is to do 2 ternary searches and take the minimum answer.

*/
	//give 2 points, returns their Euclidean distance
	double dist(double[] a, double[] b) {
		double x = a[0] - b[0];
		double y = a[1] - b[1];
		return Math.sqrt(x*x + y*y);
	}
	
	
	//this function, given our queried y-value, gives the distance of the segment that passes through point B and
	//the point (B.x+w2, y) which also touches the top segment
	//assumes that point B is the origin (makes calculations easier)
	double go1(double y, double w1, double w2) {
		double[] right = { w2, y }; //get the right point P
		double m = right[1] / right[0]; //get the slope of the line between B and P
		double[] left = { w1 / m, w1 }; //get the left point with some math
		double dist = dist(left, right); //this is our distance of the segment
		return dist; //return it!
	}
	
	//this function, given our queried y-value, gives the distance of the segment that passes through point D and
	//the point (D.x-w2, y) which also touches the segment B->C
	//assumes that point D is the origin (makes calculations easier)
	double go2(double y, double w2, double w3) {
		double[] left = { -w2, y }; //get the left point P
		double slope = left[1] / left[0]; //get the slope of the line between D and P
		double[] right = { -w3 / slope, -w3 }; //get the right point with some math
		double dist = dist(left, right); //this is out distance of the segment
		return dist; //return it!
	}
	
	//solver function
	public void solve(Scanner in, PrintWriter out) {
		int t = in.nextInt(); //test cases
		for(int tt = 1; tt <= t; ++tt) {
			
			//read in the values
			double w1 = in.nextInt();
			double w2 = in.nextInt();
			double w3 = in.nextInt();
			double l = in.nextInt();
			
			//set up our two minimum values
			double min1 = Double.POSITIVE_INFINITY;
			double min2 = Double.POSITIVE_INFINITY;
			
			//let's try the left side first
			//assume that the vertex we are passing through is the origin
			{
				//ternary search for the best y-value
				double lo = -l;
				double hi = 0;
				for(int loop = 0; loop < 200; ++loop) {
					double delta = (hi - lo) / 3;
					double m1 = lo + delta;
					double m2 = hi - delta;
					double dist1 = go1(m1, w1, w2);
					double dist2 = go1(m2, w1, w2);
					if(dist1 < dist2) hi = m2;
					else lo = m1;
				}
				min1 = go1(lo, w1, w2); //set the first minimum value
			}
			
			//let's try the right side next
			//assume that the vertex we are passing through is the origin
			{
				//ternary search for the best y-value
				double lo = 0;
				double hi = l;
				for(int loop = 0; loop < 200; ++loop) {
					double delta = (hi - lo) / 3;
					double m1 = lo + delta;
					double m2 = hi - delta;
					double dist1 = go2(m1, w2, w3);
					double dist2 = go2(m2, w2, w3);
					if(dist1 < dist2) hi = m2;
					else lo = m1;
				}
				min2 = go2(lo, w2, w3); //set the other minimum value
			}
			
			//output our answer!
			out.printf("Track Blueprint #%d: %.7f%n", tt, Math.min(min1, min2));
		}
	}
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		PrintWriter out = new PrintWriter(System.out);
		new track().solve(in, out);
		in.close();
		out.close();
	}
}
