#include <stdlib.h>
#include <stdio.h>

//define a boolean type for convenience
#define BOOL int
#define TRUE 1
#define FALSE 0

int main() {
	int i,n,x,y;
	BOOL ok;

	scanf("%d", &n);
	for(i=1; i<=n; i++) {
		scanf("%d %d", &x, &y);

		ok = FALSE;
		//there are two choices for the starting macaroni piece,
		//and two possibilities for the ending piece, 
		//yielding a total of 4 possibilities

		//it is helpful to draw some cases to see the pattern
		//they will be drawn below, where X's denote possible end locations
		//for a given pattern

		//option one: start with ## end with ##
		//                       #           #
		//   ##X
		//   #
		//   #
		//##X#
		//#
		//S
		if(x==y && x%3==2)
			ok = TRUE;

		//option two: start with  # end with  #
		//                       ##          ##
		//     X
		//     #
		//  ####
		//  X
		//  #
		//S##
		//(this yields the same equation as option one)
		if(x==y && x%3==2)
			ok = TRUE;

		//option three: start with ## end with  #
		//                         #           ##
		//      X
		//      #
		//   ####
		//   X
		//   #
		//####
		//X
		//S
		if(y==x+1 && y%3==1)
			ok = TRUE;

		//option four: start with  # end with ##
		//                        ##          #
		//     #X
		//     #
		//     #
		//  ##X#
		//  #
		//  #
		//SX#
		//(this is the opposite of option three)
		if(x==y+1 && x%3==1)
			ok = TRUE;

		//display the output
		printf("Scenario #%d: ", i);
		if(ok)
			printf("Yes, we can save Pete!\n\n");
		else
			printf("We needz more pasta!\n\n");
	}

	return 0;
}
