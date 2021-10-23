#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/* Input
21
5
Hair Cuttery
Chick fil a
Longhorn
Starbucks
Subway
*/

/* Output
Event #1:
HAI
CHI
LON
STA
SUB

Event #2:
Not Possible
*/

int main(int argc, char *argv[])
{
   FILE *   in;
   FILE *   out;
   FILE *   ans;
   char     input[256];
   char     output[256];
   char     judge[256];
   char     team[256];
   char *   ch;
   int      numCases;
   char     inputBus[500][256];
   char     outputBus[500][256];
   int      numBusinesses;
   int      i, j, k;
   char *   second;
   char *   third;

   // Verify enough parameters
   if (argc < 4)
   {
      printf("%s <judgein> <teamout> <judgeout>\n", argv[0]);
      exit(-1);
   }

   // Open judge input, team output and judge output
   in = (FILE *) fopen(argv[1], "r");
   out = (FILE *) fopen(argv[2], "r");
   ans = (FILE *) fopen(argv[3], "r");

   // Make sure we opened okay
   if ( (in == NULL) || (out == NULL) || (ans == NULL) )
   {
      printf("Failed to open files!\n");
      exit(-1);
   }

   // Read input (number of cases)
   fgets(input, sizeof(input), in);
   if ( (ch = strchr(input, '\n')) != NULL )
      *ch = '\0';
   numCases = atoi(input);

   for (i = 0; i < numCases; i++)
   {
      // Read number of businesses in input
      fgets(input, sizeof(input), in);
      if ( (ch = strchr(input, '\n')) != NULL )
         *ch = '\0';
      numBusinesses = atoi(input);

      // Read those businesses
      for (j = 0; j < numBusinesses; j++)
      {
         fgets(input, sizeof(input), in);
         if ( (ch = strchr(input, '\n')) != NULL )
            *ch = '\0';

         for (k = 0; k < strlen(input); k++)
            input[k] = toupper(input[k]);
         strcpy(inputBus[j], input);
      }
      
      // Get header from team output
      fgets(output, sizeof(output), out);
      if ( (ch = strchr(output, '\n')) != NULL )
         *ch = '\0';

      // Get header from judge output
      fgets(judge, sizeof(judge), ans);
      if ( (ch = strchr(judge, '\n')) != NULL )
         *ch = '\0';

      // Make sure prefixes match
      if (strcmp(output, judge) != 0)
         printf("%d: Header does not match\n", i+1);

      // Now read first line of judge answer
      fgets(judge, sizeof(judge), ans);
      if ( (ch = strchr(judge, '\n')) != NULL )
         *ch = '\0';

      // See if it's no possible case
      if (strcmp(judge, "Not Possible") == 0)
      {
         // It is, so skip blank after judge and then check team
         fgets(judge, sizeof(judge), ans);

         // Get team output
         fgets(output, sizeof(output), out);
         if ( (ch = strchr(output, '\n')) != NULL )
            *ch = '\0';
   
         if (strcmp(output, "Not Possible") != 0)
         {
            printf("%d: Team found a solution when there isn't one\n", i+1);
         }

         // Skip blank line after output
         fgets(output, sizeof(output), out);
      }
      else
      {
         // Just skip the rest judge answers (we don't need them)
         for (j = 1; j < numBusinesses; j++)
            fgets(judge, sizeof(judge), ans);
         fgets(judge, sizeof(judge), ans);

         // Read team output (answers)
         for (j = 0; j < numBusinesses; j++)
         {
            fgets(output, sizeof(output), out);
            if ( (ch = strchr(output, '\n')) != NULL )
               *ch = '\0';
   
            strcpy(outputBus[j], output);
         }
         fgets(output, sizeof(output), out);
   
         // Now check team's answer to see if valid
         for (j = 0; j < numBusinesses; j++)
         {
            // Sanity checks first
            if (strlen(outputBus[j]) != 3)
               printf("%d: Output not 3 characters\n", i+1);
            if ( (!isupper(outputBus[j][0])) ||
                 (!isupper(outputBus[j][1])) ||
                 (!isupper(outputBus[j][2])) )
            {
               printf("%d: Output has non capital letters\n", i+1);
            }

            // First, first characters must match
            if (toupper(inputBus[j][0]) != outputBus[j][0])
            {
               printf("%d: First characters do not match (%c %c)\n", i+1,
                      inputBus[j][0], outputBus[j][0]);
            }
   
            // Now, let's find the earlier (but not first) second character
            second = strchr(&inputBus[j][1], outputBus[j][1]);
   
            // And the latest third character
            third = strrchr(inputBus[j], outputBus[j][2]);
   
            if ( (second == NULL) || (third == NULL) ||
                 (second >= third) )
            {
               printf("%d: Invalid answer %s\n", i+1, outputBus[j]);
            }
         }
   
         // Then we have to make sure team outputs are unique within the case
         for (j = 0; j < numBusinesses - 1; j++)
         {
            for (k = j + 1; k < numBusinesses; k++)
            {
               if (strcmp(outputBus[j], outputBus[k]) == 0)
                  printf("%d: Lines %d and %d are not unique!\n", i+1, j+1, k+1);
            }
         }
      }
   }

   // Now, let's make sure the team doesn't have extra
   fgets(team, sizeof(team), out);
   if (!feof(out))
   {
      printf("Team has extra output:\n");
      while (!feof(out))
      {
         printf("%s", team);
         fgets(team, sizeof(team), out);
      }
   }

   // Close files
   fclose(in);
   fclose(out);
   fclose(ans);

   // Always return 0 for checkers
   return 0;
}

