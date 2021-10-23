/*
 * HSPT 2019
 * The Invertomancer - Solution
 * Josh Wozniak
 * 
 * The solution to this problem is to greedily invert
 * the world whenever the jump is too far. There is no
 * need to invert early.
 */

import java.util.Scanner;

public class invert
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int w = scan.nextInt();
		for (int testCase = 1; testCase <= w; testCase++)
		{
			// Read input
			int r = scan.nextInt();
			int c = scan.nextInt();
			int k = scan.nextInt();
			char[][] grid = new char[r][c];
			for (int i = 0; i < r; i++)
				grid[i] = scan.next().toCharArray();
			
			// For each column, calculate the normal and inverted height
			// and store them in an array
			int[] normalHeight = new int[c];
			int[] invertedHeight = new int[c];
			for (int i = 0; i < c; i++)
			{
				for (int j = 0; j < r; j++)
				{
					if (grid[j][i] == '#')
					{
						normalHeight[i] = r-j;
						invertedHeight[i] = j;
						break;
					}
				}
			}
			
			int inverts = 0;
			int currentHeight = normalHeight[0]; // Start at the first column
			boolean normal = true;
			for (int i = 1; i < c; i++)
			{
				int nextHeight = normal ? normalHeight[i] : invertedHeight[i];
				int difference = nextHeight - currentHeight;
				if (difference > k) // He needs to invert the world
				{
					inverts++;
					normal = !normal;
				}
				currentHeight = normal ? normalHeight[i] : invertedHeight[i]; // Recalculate the current height
			}
			System.out.printf("World #%d: %d\n", testCase, inverts);
		}
	}
}
