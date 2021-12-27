
// Solution to "lava" from the 2013 UCF Online Contest
//    written by: Matt in the Hat
//
//    The basic idea for my solution is to use the so called
// union find approach. What is problem is asking is for the
// number of groups of lava that exist on the floor. The 
// other condition is that each group of lava can reach a 
// toilet. So what we do for this is imagine each "cell" of
// floor as a unique lava location. What we can imagine doing
// is take each location that neighbors each other and join
// them. At the end we have several pools of lava and we can
// just make sure that each pool contains a toilet. If that
// is true we can simply count the number of large pools.

#include <stdio.h>

int r, c;
int * parent;

// Create some prototypes
int createID(int j, int i);
void unionLava(int a, int b);
int find(int a);

// Makes an id using the current row and column
// its easier to deal with having the one number
int createID(int j, int i)
{
   // Make a unique id 
   return j*c+i;
}

// Unions lava pit a with lava pit b, how does this
// work you ask? Basically we say that lava pit a
// now belongs to b. We point to it using our array
// when we call the find operation on a or b they will
// return the same value making it easy to identify as
// one bigger pool of lava. Try printing out the parent
// array after preforming unions, you will see a pattern
void unionLava(int a, int b)
{
   parent[find(a)] = find(b);
}

// The find operation is the main machine to this approach.
// What we do is trace up the path of parents until we reach
// something that is its own parent. When that happens we have
// reached what is called the representative of the lava pool.
// That is what gets returned. Everything that belongs to the
// same lava pool will return the same representative making
// it easy to determine if the lava belongs to the same pool.
int find(int a)
{
   if (parent[a] == a)
      return a;
   return find(parent[a]);
}

int main()
{
   // I will make too big of a buffer for io
   char buffer[2048];
  
   // First read in the number of test cases
   int t = 0;
   fgets(buffer,2047,stdin);
   sscanf(buffer,"%d",&t);

   // Loop through each of the floors we must process
   for (int tc=1; tc<=t; tc++)
   {
      // Read in the dimensions of the floor
      fgets(buffer,2047,stdin);
      sscanf(buffer, "%d %d", &r, &c);

      // Now that we have our floor layout lets make memory!
      bool ** hasWall = new bool*[r];
      for (int j=0; j<r; j++)
         hasWall[j] = new bool[c];

      bool ** isLava = new bool*[r];
      for (int j=0; j<r; j++)
         isLava[j] = new bool[c];

      // Now lets run through all the floors and examine the lava
      int * toilets = new int[r*c];
      int numToilets = 0;
      //printf("%d %d\n", r, c);
      for (int j=0; j<r; j++)
      {
         // Read in each line and allow extra buffer for end lines
         fgets(buffer,c+5,stdin);
         //printf("%d: %s", j, buffer);
         for (int i=0; i<c; i++)
         {
            hasWall[j][i] = (buffer[i] == '#');
            isLava[j][i] = (buffer[i] == '~');

            // We also save that a toilet was at this location
            if (buffer[i] == 'T')
               toilets[numToilets++] = createID(j,i);
         }
      }

      // Create the parent array making the unioning simple
      parent = new int[r*c];
      for (int i=0; i<r*c; i++)
         parent[i] = i;

      // Now for the actual algorithm
      for (int j=1; j<r-1; j++)
      {
         for (int i=1; i<c-1; i++)
         {
            if (!hasWall[j][i])
            {
               // We only have to look at two of the walls
               // since the other two will be taken care of
               // when we get to that pit of lava
               int curId = createID(j,i);
               if (!hasWall[j-1][i])
                  unionLava(curId, createID(j-1,i));
               if (!hasWall[j][i-1])
                  unionLava(curId, createID(j,i-1));
            }
         }
      }

      // Go through all the toilets and mark the pools that have them
      bool * hasToilet = new bool[r*c];
      for (int i=0; i<r*c; i++)
         hasToilet[i] = false;
      for (int i=0; i<numToilets; i++)
         hasToilet[find(toilets[i])] = true;
      
      //for (int i=0; i<numToilets; i++)
      //   printf("Toilet %d: links %d\n", toilets[i], find(toilets[i]));

      // Now go through each location that is lava and make sure it
      // has a toilet, we start off assuming everything is a-ok!
      bool passed = true;
      for (int j=0; j<r; j++)
         for (int i=0; i<c; i++)
            if (isLava[j][i]&&!hasToilet[find(createID(j,i))])
               passed = false;

      // Print the header and if we can't solve the problem call Mario.
      printf("Floor #%d: ", tc);
      if (!passed)
         printf("Call a plumber!\n");
      else
      {
         // Cool the problem is solveable! Now we just need to count the
         // number of pools of lava we have. That's easy! we just count
         // the number of representative pools! First we mark the reps!
         bool * isRep = new bool[r*c];
         for (int i=0; i<r*c; i++)
            isRep[i] = false;
         for (int j=0; j<r; j++)
            for (int i=0; i<c; i++)
               if (isLava[j][i])
                  isRep[find(createID(j,i))] = true;
         
         // Now counts the reps!
         int res = 0;
         for (int i=0; i<r*c; i++)
            if (isRep[i])
               res++;
         
         // Now print the answer
         printf("Only need to flush %d toilet(s).\n", res);
         
         // Clean up memory
         delete[] isRep;
      }

      // We have finished this test case let us clear the memory!
      delete[] hasToilet;
      delete[] parent;
      delete[] toilets;
      for (int j=0; j<r; j++)
         delete[] hasWall[j];
      delete[] hasWall;
      for (int j=0; j<r; j++)
         delete[] isLava[j];
      delete[] isLava;

   }

   return 0;
}
