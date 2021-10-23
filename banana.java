// Ellie Kozlowski
// Solution to banana
// 02/10/19

import java.util.Scanner;

public class banana {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		// read in input
		int n = in.nextInt();
		String[] arr = new String[n];
		
		for(int i=0; i<n; i++) {
			arr[i] = in.next();
		}
		
		// check to see if the monkey is holding a banana
		for(int i=0; i<n; i++) {
			if(arr[i].equals("banana"))
				System.out.println("He's got the banana!");
			else
				System.out.println("Oh, bummer.");
		}
		
	}
}
