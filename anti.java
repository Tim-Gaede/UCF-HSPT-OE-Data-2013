import java.util.*;
import java.io.*;
public class anti {
	public static void main(String args[]) throws IOException {
		Scanner in = new Scanner(System.in);
		int T = in.nextInt(); //Number of test cases
		for(int t = 1; t <= T; t++) {
			int N = in.nextInt(); //Eat variable, not necessary
			int G = in.nextInt(); //Guesses allowed
			in.nextLine(); //Eat new line
			String line = in.nextLine().toLowerCase(); //set string to lowercase
			boolean[] occur = new boolean[26]; //keep track of letters in the string
			
			for(int i = 0; i < line.length(); i++) {
				//Ignore spaces
				if(line.charAt(i) == ' ')
					continue;
				occur[line.charAt(i)-'a'] = true;
			}
			
			int count = 26; //Count the number of distinct letters he can guess incorrectly
			for(int i = 0; i < 26; i++) {
				if(occur[i])
					count--;
			}
			
			if(count >= G)
				System.out.printf("Game #%d: Trolling succeeded\n\n", t);
			else
				System.out.printf("Game #%d: Impossible to lose\n\n", t);
		}
	}
}
