// Christopher
// doubling.java

import java.io.FileNotFoundException;
import java.util.Scanner;

public class doubling {

	public static void main(String[] args) throws FileNotFoundException {
		
		Scanner in = new Scanner(System.in);
		
		// input number of cases
		int cases = in.nextInt();
		
		// loop through each case
		for (int q = 0; q < cases; q++) {
			
			// input money and save a copy
			int money = in.nextInt();
			int savemoney = money;
			
			// double money
			money *= 2;
			
			// forget last digit
			money /= 10;
			
			// output
			System.out.printf("Trade #%d: %d%n", q + 1, savemoney - money);
		}
		
		in.close();
	}
}
