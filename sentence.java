import java.util.Scanner;

public class sentence {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int t = scan.nextInt();
		
		// loop through each test case
		for(int tt = 1 ; tt <= t ; tt++) {
			int n = scan.nextInt();

			// These will be used to count the upper and
			// lower case letters in the current sentence
			int upper = 0;
			int lower = 0;
			
			// loop through each word
			for(int i = 0 ; i < n ; i++) {
				
				// scan in the next word
				String word = scan.next();
				
				// for each word, loop through the characters of it
				for(int j = 0 ; j < word.length() ; j++) {
					
					// Check whether the current character is upper case
					if(Character.isUpperCase(word.charAt(j))) {
						
						// if this character is upper case, add to the counter
						// for upper case letters
						upper++;
					}
					
					// Check whether the current character is lower case
					if(Character.isLowerCase(word.charAt(j))) {
						
						// if this character is lower case, add to the counter
						// for lower case letters
						lower++;
					}
				}
			}
			
			// if the number of upper case letters is equal
			// to the number of lower case letters, this sentence is balanced
			// otherwise, it is not balanced
			if(upper == lower) {
				System.out.println("Sentence #" + tt + ": Yes");
			} else {
				System.out.println("Sentence #" + tt + ": No");
			}
		}
	}
}
