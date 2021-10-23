
import java.util.*;
/*
 * @author Andy Phan
 */
public class song {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        
        int stanzas = in.nextInt(); //read in number of stanzas
        
        for(int i = 1; i <= stanzas; i++) {
            int repeat = in.nextInt(); //gets number of times to reapeat
            System.out.printf("Stanza #%d:\n", i);
            
            for(int j = 0; j < repeat; j++) //prints each lyric
                System.out.println("This song's gonna get stuck inside yo'");
            
            System.out.println("head"); //finishes stanza
            System.out.println("");
        }
    }
}
