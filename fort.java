import java.util.Scanner;

/*
Solution to Fort by David Harmeyer

Samples:
3
15 10 2
0 200 10
250 100 15
 */
public class fort {
   public static void main(String[] args) {
      Scanner fs=new Scanner(System.in);

      // Loop over months
      int months=fs.nextInt(), i;
      for (i=1; i<=months; i++) {
         // Output header for month
         System.out.printf("Month #%d:%n", i);

         // Loop over collection days within this month
         int days=fs.nextInt(), w=0, b=0, m=0, d;
         for (d=1; d<=days; d++) {
            // Read stats collected and sum
            int ww=fs.nextInt(), bb=fs.nextInt(), mm=fs.nextInt();
            System.out.printf("Day #%d: Collected %d wood, %d brick, and %d metal.%n", d, ww, bb, mm);
            w+=ww;
            b+=bb;
            m+=mm;
         }

         // Output total for month
         System.out.printf("Collected a total of %d wood, %d brick, and %d metal!%n%n", w, b, m);
      }
   }
}
