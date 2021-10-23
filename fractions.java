import java.util.Arrays;
import java.util.Scanner;

/*
Solution to Fractions by David Harmeyer

Observation: assume you have three numbers a, b, and c, where 0 < a < b < c.
If c is divisible by b and b is divisible by a, then c is divisible by a.
The proof of this left to the reader, but pretty intuitive if you think about it.

Personally, I felt that this problem would have been way more interesting if we set n to
10^5, because with n=1000 you can literally just check all n*(n-1)/2 pairs.

 */
public class fractions {

	public static void main(String[] args) {
		Scanner fs=new Scanner(System.in);
		//read in input
		int T=fs.nextInt();
		for (int t=1; t<=T; t++) {
			int n=fs.nextInt();
			int[] a=new int[n];
			for (int i=0; i<n; i++)
				a[i]=fs.nextInt();
			
			//make sure each pair of adjacent elements in the sorted array works
			Arrays.sort(a);
			boolean works=true;
			for (int i=1; i<n; i++)
				works&=a[i]%a[i-1]==0;
			
			System.out.println("Array #"+t+": "+(works?"This array is bae!":"Go away!"));
		}
	}

}
