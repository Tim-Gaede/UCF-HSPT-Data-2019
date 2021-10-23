
import java.util.Scanner;

/*
 * @author Andy Phan
 */
public class diverse {
    static int[] perm;
    static int[] number;
    static int[] numDigits;
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for(int i = 0; i < n; i++) {
            long num = in.nextLong();
            int k = in.nextInt();
            perm = new int[19];
            number = new int[19];
            for(int j = 0; j < 18; j++) {
                number[18-j] = (int)(num%10); //read in digits
                num /= 10;
            }
            int j = 0;
            for(; number[j] == 0 && j < number.length; j++) {} //find first digit
            numDigits = new int[10];
            
            if(!permute(j-1, k, true, true)) { //call recursive function
                System.out.println("Find a different k");
            } else {
                j = 0;
                for(; perm[j] == 0; j++) {} //find first digit
                for(; j < 19; j++) System.out.print(perm[j]); //print out all the digits
                System.out.println();
            }
        }
    }
    
    static boolean permute(int pos, int max, boolean bounded, boolean first) {
        if(pos == number.length) return true; //reached end of number while still being valid, so return
        int i = number[pos]; //get current digit
        if(!bounded) i = 0; //if the current digit does not have to be greater than the original digit
                            //i.e at least one digit before it in the current number is different from the original number, let it be whatever
        for(; i <= 9; i++) { //try all posible digits
            if(numDigits[i] == max) continue; //if the limit on the digit we are trying is reached, continue
            //else, set perm array and increment the number of times the current digit has appeared
            perm[pos] = i;
            if(!(first && i == 0)) numDigits[i]++;
            if(permute(pos+1, max, bounded && i == number[pos], false)) return true; //if the current permutation works, return true
            if(!(first && i == 0)) numDigits[i]--; //reset number of times the digit has appeared
        }
        return false; //nothing works, so return
    }
}
