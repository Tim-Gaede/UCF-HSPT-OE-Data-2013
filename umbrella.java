
/*

Solution to Umbrella
--------------------

How do we solve this problem.

First we make the following observation!
n <= 8

This means we can try lots of possibilities!

But what different types of possibilities are there?

We can try every ordering of the rods and pick the best result.

Brilliant! How many ways are there to do this.

Answer 8! or 8*7*6*5*4*3*2*1 = 40320. We can do around 10^8 basic operations
per second. (Roughly) So we have plenty of time. It is possible to calculate
the area as we go to save runtime but my solution will just run through the
ordering of the rods at the end and increase the runtime by a factor of N.
With the bounds of this problem this will be fine! For a problem with a 
similar idea of trying every ordering observe the problem "vacation"
from the 2012 HSPT. 

Now that we have all orderings, how do we determine the area? I feel that the
simplest way to do this is to think of the area between rods as triangles.
How do we find the areas of the triangles? 

First we need to find the angle between each of the rods. Notice the sum of rod
angles is a full revolution, 2*PI or 360 degree. Notice that there are N regions
with internal angles. Since they are equal angles we must divide the 2*PI region
into N equal regions or 2*PI/N.

Now we are required to find the area of the triangle.


    /
L2 /
  /
 /
/ 2*PI/N
-----------
   L1

or 

      /\
     /  \
    /    \
L1 / ang. \  L2
  /        \
 /          \
/            \
--------------

where L1 != L2 possibly.
How do we solve this?

We are given two sides and their included angle.
what is the area of the triangle?


     /|
L2  / |  height
   /  |_
  /A  | |  <--- right angle
  ------------------------
           L1

I will denote the given angle as the constant A.

height = L2 * sin(A)

Using trigonometry!

We know the area of the whole triangle is:

area = base * height / 2

So we can construct a formula from our two equations:

area = L1 * L2 * sin(A) / 2

tada!

Using this equation throughout our calculations will give us our answer!

*/

import java.util.*;

public class umbrella
{
   public static void main(String[] args)
   {
      // I work out of the constructor to get me out of static land quickly and
      // without wasting a useful function name. I don't like static land,
      // everything is too clingy.
      new umbrella(new Scanner(System.in));
   }

   // Important class variables.
   double result;               // Holds final answer
   int numRods;                 // Number of rods
   int[] rodLen;                // Each rod length
   int[] permutation;           // The permutation
   boolean[] used;              // Each item used in the permutation

   // This is our fancy permuations function that will try all orderings.
   void permute(int currentLocation)
   {
      // If we have exhausted all our locations then we have our permutation.
      // From here we can just solve the problem for this instance. =D
      if (currentLocation == numRods)
      {
         // Loop through the permutation and find the solution
         double totalArea = 0;
         for (int i=0; i<numRods; i++)
         {
            // We want the next rod to "wrap" so we can take the modulus 
            // of the value. Its a cool trick to wrap the rods.
            int j = (i+1)%numRods;
            
            // Get the lengths and angle in the form of our equation above.
            double L1 = rodLen[permutation[i]];
            double L2 = rodLen[permutation[j]];
            double A = Math.PI*2.0/numRods;

            // Calculate the area of this sub triangle.
            double area = L1 * L2 * Math.sin(A) / 2.0;
            
            // Add this triangle's area to our total solution.
            totalArea += area;
         }
         
         // Determine if this is the best solution and update it accordingly
         if (totalArea > result)
            result = totalArea;

         // This is a base case so just return
         return;
      }

      // Try every possible next rod we can
      for (int i=0; i<numRods; i++)
      {
         // If this rod is unused then try it!
         if (!used[i])
         {
            // We are currently using this rod now
            used[i] = true;

            // Try a solution with rod i at position currentLocation
            permutation[currentLocation] = i;

            // Progress in the recursion
            permute(currentLocation+1);

            // We have finished using this rod
            used[i] = false;
         }
      }
   }

   public umbrella(Scanner in)
   {
      int numUmbrellas = in.nextInt();
      for (int umbrellaID=1; umbrellaID<=numUmbrellas; umbrellaID++)
      {
         // Reset our best result we have found
         result = 0;

         // Read in the number of rods
         numRods = in.nextInt();
         
         // Create a new array of size numRods to hold the rod lengths
         rodLen = new int[numRods];

         // Read in each rod length
         for (int i=0; i<numRods; i++)
            rodLen[i] = in.nextInt();

         // We keep an array used to keep track of if we have used
         // this number rod in the permutation yet. Remember each
         // permutation uses a rod exactly once? This array makes
         // sure that this occurs throughout the algorithm!
         used = new boolean[numRods];

         // We also need an array to keep track of the order of the rods.
         // The i-th element contains the id of the rod in position i of
         // the ordering.
         permutation = new int[numRods];

         // Call the permute method that will loop through the solutions!
         permute(0);

         // Print the result
         System.out.printf("Umbrella #%d: %.3f%n", umbrellaID, result);
      }
   }
}
