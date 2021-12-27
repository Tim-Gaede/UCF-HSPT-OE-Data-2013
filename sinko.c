/***********************************
Michael Galletti
04/28/2011
Sink All the Mayo
---
In this problem, we're asked to find the altitude of a triangle. This is equivalent to finding the common side of two adjacent right triangles.
In this solution, we'll take advantage of two things:

First, by using the Pythagorean Theorem (the lengths of the sides of a right triangle conform to the equation a^2 + b^2 = c^2, where c is the hypotenuse),
we can solve for any side of a right triangle as long as we know the two others.

Second, there is exactly one position at which the mast may stand (if it can at all!). If we pick an arbitrary point on the deck of the boat, we can assume that
one of the ropes will be tied to a mast erected at the point. We can then easily solve for the height of the imaginary mast using the Pythagorean Theorem. Once
we have the height that a mast at this point must be to satisfy one of the ropes, we can then try to tie the other rope to the mast. One of three cases will follow:
   
   1. The height of the mast makes it so the rope is too short compared to what is expected
   2. The height of the mast makes it so the rope is of perfect length to form a right triangle
   3. The height of the mast makes it so the rope is too long compared to what is expected

If we sweep from left to right along the deck, we can observe that everything to the left of the point that meets condition 2 will meet condition 1, and everything to
the right of the point will meet condition 3. This behavior lends itself perfectly to a binary search solution.
***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int checkTriangle(double a, double b, double c);
int min(int x, int y);

int main(){
   int times, t;
   fscanf(stdin, "%d", &times); //Read in the number of test cases
   
   for(t = 1; t <= times; t++){
      double width, bow, stern;
      fscanf(stdin, "%lf %lf %lf", &width, &bow, &stern); //Read in our ship information
      
      //Binary search over the mast's distance from the bow
      //We'll first mark our low and high endpoints for the interval we'd like to search over. We choose low = 0 to represent the leftmost point of the deck,
      //and high = min(bow, width) to represent the furthest point we can stretch the bow rope to while still being on the ship.
      double MIN = -.1;
      double MAX = min(bow,width) + .5;
      double low = MIN;
      double high = MAX;
      double mid = (high+low)/2;
      while(fabs(high-low) > 1e-12){ //We'll continue searching until our interval is small enough
         mid = (high + low)/2;
         
         //The point we've now picked is mid distance from the bow anchor point. We can now solve for the height using the Pythagorean Theorem.
         //We know that the bow rope length, and that it is the hypotenuse. We'll say that one of the legs is of length mid, leaving
         //bow^2 = mid^2 + height^2
         //bow^2 - mid^2 = height^2
         //sqrt(bow^2 - mid^2) = height
         double height = sqrt(bow*bow - mid*mid);
         
         //Now that we have the mast height, we can calculate what we'd expect the stern rope length to be based on the height.
         //We'll still use the Pythagorean Theorem, only this time we're solve for the hypotenuse.
         double expectedStern = sqrt(height*height + (width-mid)*(width-mid));
         
         //If the expected stern length is less than the actual stern length, we've met condition 1 and should move our interval further to the right
         if(expectedStern > stern){
            low = mid;
         }else{ //Otherwise we've met condition 2 or 3. Either way, let's move the interval left!
            high = mid;
         }
      }
      
      double mastHeight = sqrt(bow*bow - mid*mid + 1e-9);
      
      //If our search turned up a 0 or initial high value, we know that the fabled point must exist somewhere outside of the bow rope's reachable range.
      if(!checkTriangle(bow,stern,width) || fabs(MIN-mid) < 1e-9 || fabs(MAX-mid) < 1e-9){
         //We're sunk!
         printf("Ship #%d: Ali is sunk!\n", t);  
      }else{
         //Not today!
         printf("Ship #%d: %.2lf %.2lf %.2lf\n", t, mastHeight, mid+1e-9, width-mid+1e-9); 
      }
   }
   
   return 0;
}

//Helper functions

int checkTriangle(double a, double b, double c){
   return (a+b) > c && (b+c) > a && (c+a) > b;
}

//Minimum of two values
int min(int x, int y){
   if(x < y)
      return x;
   return y;
}
