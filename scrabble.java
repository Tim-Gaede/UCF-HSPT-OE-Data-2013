import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;


public class scrabble {
	//This array is for each letter, 'A' is at index 0, 'B' is at index 1, etc.
	static int[] scores=new int[]{1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
	public static void main(String[] args)throws IOException
	{
		Scanner br=new Scanner(System.in);
		Word[] dictionary=new Word[br.nextInt()];
		for(int i=0;i<dictionary.length;i++)
			dictionary[i]=new Word(br.next());
		//Sort the dictionary by score, then alphabetically
		//Then you can run through the dictionary, the first one you find is your answer
		Arrays.sort(dictionary);
		int cases=br.nextInt();
		for(int c=1;c<=cases;c++)
		{
			String str=br.next();
			for(int i=0;i<dictionary.length;i++)
			{
				if(canMake(str,dictionary[i].word))
				{
					System.out.printf("Tile Rack #%d: Playing %s earns %d points, the max possible.\n\n",c,dictionary[i].word,dictionary[i].points);
					break;
				}
			}
		}
	}
	/*
	 The concept of this method is to take the array for each String,
	 sort them, and for each letter in the word you are trying to make,
	 find the next letter in your letters that matches. Keep a running
	 pointer (index) so you never revisit a letter you have already used.
	 If you ever can't find a match, then you can't make it. Otherwise, you can.
	 
	 */
	public static boolean canMake(String one,String two)
	{
		char[] a=Arrays.copyOf(one.toCharArray(),one.length());
		char[] b=Arrays.copyOf(two.toCharArray(),two.length());
		Arrays.sort(a);
		Arrays.sort(b);
		int index=0;
		outHere://Label this for loop so we can continue when we feel like it
		for(int i=0;i<b.length;i++)
		{
			for(;index<a.length;index++)
			{
				if(a[index]==b[i])
				{
					index++;
					continue outHere;//We found our match, stop searching in here and continue out there
				}
			}
			return false;
		}
		return true;
	}
	public static class Word implements Comparable<Word>
	{
		int points;
		String word;
		public Word(String s)
		{
			word=s;
			points=0;
			for(int i=0;i<s.length();i++)
				points+=scores[s.charAt(i)-'A'];//Index can be accessed by converting chars to ints, then subtracting 'A' from that int.
		}
		//This method is for every class that implements Comparable. It returns a negative
		//number if this object comes before the other, a positive number if it comes after,
		//or zero if they are exactly the same
		public int compareTo(Word o)
		{
			//We check points first, and if they are equal we order alphabetically
			if(points==o.points)
			{
				return word.compareTo(o.word);
			}
			//Otherwise, we take the difference of their points and ours.
			//Order is important: if we are higher, we want to come first, and we will return
			//a negative number in that case.
			return o.points-points;
		}
	}
}
