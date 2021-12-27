/***********************************
Michael Galletti
04/28/2011
Programming Logo
---
This problem asks whether it is possible for Pete to construct a bridge from one point to another using two different pieces of elbow macaroni.

With a little observation, it becomes apparent that there are really only two ways for Pete to go about doing things, due to the connectivity of macaroni.
From his starting position, Pete may either place a piece with an exit pointing downwards, or he may place a piece with exit pointing left. From here, the
remaining path is static. It will either get him to (0,0) or not. We can easily simulate both choices to arrive at our answer.
***********************************/

import java.util.*;
import java.io.*;

public class ghosts{
	public static void main(String[] args) throws Exception{
		Scanner reader = new Scanner(System.in);
		
		int times = reader.nextInt(); //Number of cases
		
		for(int t = 1; t <= times; t++){
			//Initial x and y coordinates
			int x = reader.nextInt(); 
			int y = reader.nextInt();
			
			System.out.print("Scenario #"+t+": ");
			if(placeDown(x-1, y) || placeLeft(x, y-1)){ //Try both starting options! If either works, we can save Pete!
				System.out.println("Yes, we can save Pete!");
			}else{
				System.out.println("We needz more pasta!");
			}
			System.out.println();
		}
	}
	
/**********************
The Simulation		
---
We'll use this opportunity to explore a recursive solution. An elegant recursive solution can save us quite a bit of time in implementation.
This implementation chooses to break up the simulation into two codependant functions, though it is by all means possible to solve this problem
with just one.
**********************/
	
	//Place a piece of macaroni with the exit pointing down
	public static boolean placeDown(int x, int y){
		//If our x or y coordinate is below the target point, there is no point in continuing (We can only move down and to the left!).
		if(x < 0 || y < 0)
			return false;
			
		//If we've found our target point, we're good to go!
		if(x == 0 && y == 0)
			return true;
		
		//Otherwise, we only have on option from this point, and that's to place the opposing type of macaroni.
		return placeLeft(x - 1, y - 2);
	}
	
	//Place a piece of macaroni with the exit pointing left
	public static boolean placeLeft(int x, int y){
		if(x < 0 || y < 0)
			return false;
			
		if(x == 0 && y == 0)
			return true;
			
		return placeDown(x - 2, y - 1);
	}
}
