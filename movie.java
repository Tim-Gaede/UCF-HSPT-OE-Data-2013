/*
 * For each test case:
 * 	1) Read in a list of "Titles".
 * 	2) Sort this list based on:
 * 		- Case insensitive.
 * 		- The word "the" at the beginning of a title should be disregarded.
 * 		- Any titles identical except for an ending number (word or numeral)
 * 			should be sorted among themselves numerically.
 *  3) Output test case header "Movie Collection #i:".
 * 	4) Output the sorted list using each respective original title.
 *  5) Output blank line to separate test case from next.
 */

import java.util.*;
import java.io.*;

public class movie {
	
	//This is the true main function, but I just use it to call the constructor
	// and initialize the scanner. This keeps things more organized and in a
	// non-static context.
	public static void main(String[] args) throws Exception {
		new movie(new Scanner(System.in));
	}
	
	//This is my main function.
	movie(Scanner in) {
	
		//Input the number of collections to process and loop over that number.
		int T = in.nextInt();
		for (int t=0; t<T; t++) {
		
			//Input the number of lines of movies to read in.
			int N = in.nextInt();
			//Make sure to clear out the rest of this line from the buffer.
			in.nextLine();
			
			//Initialize an array of Titles
			Title[] list = new Title[N];
			
			//Read in the movie titles, created as the object type Title (which we created)
			for (int i=0; i<N; i++)
				list[i] = new Title(in.nextLine());
			
			//Sort the array (based on the comparator we created for this class)
			Arrays.sort(list);
			
			//Print out the output header for this collection.
			System.out.printf("Movie Collection #%d:\n",t+1);
			
			//Loop over every title, and output each on a new line.
			for (int i=0; i<N; i++)
				System.out.println(list[i]);
				
			//Don't forget the line break to separate each collection.
			System.out.println();
			
		}
	}
	
	//Decare these values in an array, so that they are easy to search for. 
	// The value of each index in number is the value in numberValue at that index.
	static final String[] number = new String[]{"1","2","3","4","5","6","7","8","9","10",
												"one","two","three","four","five","six","seven","eight","nine","ten"};
	static final int[] numberValue = new int[]{1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};
	
	//Create a class that will allow easy comparisons of titles.
	class Title implements Comparable<Title> {
	
		//Store the unmodified title, which we need to output at the end.
		String actualTitle;
		
		//Store a modified title that consists of removing all extraneous data
		// (such as leading "the" and trailing numbers.
		String sortTitle;
		
		//Store the sequel number (assume 1 if none is found, as this is convention).
		int sequelNumber = 1;
		
		//Initializer for this class, taking in the input title.
		Title(String t) {
		
			//Save the input title as the unmodified one.
			actualTitle = t;
			
			//The first modification to the sorted title is to lower case it, as
			// we want to ignore case when sorting.
			sortTitle = actualTitle.toLowerCase();
			
			//Now we are going to split the title up by spaces, so that we can check
			// the leading and trailing words for certain conditions.
			String[] tmp = sortTitle.split(" ");
			
			//Check to see if the first word is "the" (and make sure its not the only word).
			if (tmp.length > 1 && tmp[0].equals("the")) {
				//If it is, we need to remove it from the String
				sortTitle = sortTitle.substring(4);
				tmp = sortTitle.split(" ");
			}
			
			//Check to see if there is more than one word in the string, meaning that it
			// might be ending with a number.			
			if (tmp.length > 1) {
			
				//Loop over all of the possible numbers (declared in arrays at the top for simplicity)
				for (int i=0; i<number.length; i++) {
					//If the number as a string matches the last word of this string, we have found the
					//sequel number, so store this value, remove the number from the sorting string.
					if (tmp[tmp.length-1].equals(number[i])) {
						sequelNumber = numberValue[i];
						sortTitle = sortTitle.substring(0,sortTitle.length()-number[i].length()-1);
						break;
					}
				}
			}
			
		}
		
		//Implement a comparator, since this class needs to be comparable in order to be sorted.
		public int compareTo(Title t) {
			int cmp = sortTitle.compareTo(t.sortTitle);
			if (cmp != 0)
				return cmp; //If the sort titles are not the same, return the comparison between them.
			else
				return sequelNumber - t.sequelNumber; //Otherwise, return the comparison of the sequel numbers.
		}
		
		//The toString() function is an easy shortcut to cause this class to output as the correct string without
		// referencing a class variable from the outside.
		public String toString() {
			return actualTitle;
		}
	}
}
