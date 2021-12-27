import java.util.*;
import java.io.*;
public class yuno{
	public static void main(String[] args)throws IOException{
		Scanner br = new Scanner(System.in);
		int n = br.nextInt();
		br.nextLine();
		for(int i = 0;i<n;i++){
			String line1 = br.nextLine();
			String line2 = br.nextLine();
			System.out.println(line1.toUpperCase()+"...");
			System.out.println("Y U NO "+line2.toUpperCase()+"?");
			System.out.println();
		}
	}
}
