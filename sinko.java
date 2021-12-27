import java.io.File;
import java.io.IOException;
import java.util.Scanner;


public class sinko {
	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(System.in);
		int cases = in.nextInt();
		for(int c = 1; c <= cases; c++) {
			int width = in.nextInt();
			//front
			int front = in.nextInt();
			//back
			int back = in.nextInt();
			
			if(front+back<=width) {
				System.out.printf("Ship #%d: Ali is sunk!\n",c);
				continue;
			}
			
			//heron's to get height
			double semi = (front+back+width)/2.0;
			if(semi < front || semi < back || semi < width) {
				System.out.printf("Ship #%d: Ali is sunk!\n",c);
				continue;
			}
			double area = Math.sqrt(semi*(semi-width)*(semi-front)*(semi-back));
			double h = ((2*area) / width);
			
			
			//solve for x1 and x2
			double x1 = Math.sqrt(front*front-h*h);
			double x2 = Math.sqrt(back*back-h*h);
			
			if(x1 < 0 || x1 > width || x2 < 0 || x2 > width) {
				System.out.printf("Ship #%d: Ali is sunk!\n",c);
				continue;
			}
			
			System.out.printf("Ship #%d: %.2f %.2f %.2f\n",c,h,x1,x2);
		}
	}
}
