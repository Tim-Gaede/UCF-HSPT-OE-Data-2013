import java.io.File;
import java.io.IOException;
import java.util.*;
public class lava {
	
	public static boolean[][] is_toilet, is_lava, is_wall, has_flushed, visited;
	
	public static void main(String[] Args) throws IOException{
		
		//sc is our scanner that we use to read in data
		Scanner sc = new Scanner(System.in);
		
		//number_of_cases stores the number of cases
		int number_of_cases = sc.nextInt();
		
		//loop through all the cases and check each one
		for(int case_num = 1; case_num <= number_of_cases;case_num++){
			
			//rows and cols stores the number of rows and columns respectively.
			int rows = sc.nextInt();
			int cols = sc.nextInt();
			
			//is_toilet[i][j] will store whether the j element of the i row is a toilet or not (0 indexed).
			is_toilet = new boolean[rows][cols];

			//is_wall[i][j] will store whether the j element of the i row is a wall or not (0 indexed).
			is_wall = new boolean[rows][cols];

			//is_lava[i][j] will store whether the j element of the i row is lava or not (0 indexed).
			is_lava = new boolean[rows][cols];
			
			//has_visisted will be used later the check if we have flushed a square yet.
			has_flushed = new boolean[rows][cols]; 
			
			//Visited will also be used later. It stores if we have visited a certain square.
			visited = new boolean[rows][cols];
			
			//Loop through the entire room and check each square.
			for(int row = 0; row < rows ; row++){
				
				//curr_row store the state of our current row.
				String curr_row = sc.next();
				
				//Loop through each square. 
				for(int square = 0; square < cols; square++){
					
					//Check if the square is a toilet.
					if(curr_row.charAt(square)=='T')
						is_toilet[row][square] = true;
					//Check if the square is a wall.
					else if(curr_row.charAt(square)=='#')
						visited[row][square] = is_wall[row][square] = true;
					else
						is_lava[row][square] = true;
				}
			}

			// Answer stores the number of toilets needed to flush 
			int answer = 0;
			
			// Stores if it is possible to flush every thing.
			boolean possible = true;
			
			// Loop through the entire room flushing when needed.
			for(int row = 0; row < rows; row++){
				for(int col = 0; col < cols; col++){
					
					// Check if we haven't flushed a lava square.
					if(!has_flushed[row][col] && is_lava[row][col]){
						
						// Check if you can flush that room.
						if(itCanFlush(row, col)){
							
							// Flush the room.
							flushIt(row, col);
							
							// Increment the answer by one.
							answer++;
						}
						else
							possible = false;
					}
				}
			}
			
			//If it is possible to flush all the lava, print the number of toilets needed.
			if(possible){
				System.out.printf("Floor #%d: Only need to flush %d toilet(s).%n", case_num, answer);
			}
			//Print call a plumber if not possible.
			else{
				System.out.printf("Floor #%d: Call a plumber!%n",case_num);
			}
		}
	}

	private static void flushIt(int row, int col) {
		
		
		//Flush all the directions.
		
		//Flush above, if we haven't.
		if(!is_wall[row+1][col] && !has_flushed[row+1][col]){
			
			//We have flushed it since it is adjacent, so we mark it.
			has_flushed[row+1][col] = true;
			
			//Flush around it
			flushIt(row+1,col);		
		}
				
		//Flush below.
		if(!is_wall[row-1][col] && !has_flushed[row-1][col]){

			//We have flushed it since it is adjacent, so we mark it.
			has_flushed[row-1][col] = true;

			//Flush around it
			flushIt(row-1,col);
		}

				
		//Flush the right.
		if(!is_wall[row][col+1] && !has_flushed[row][col+1]){

			//We have flushed it since it is adjacent, so we mark it.
			has_flushed[row][col+1] = true;

			//Flush around it
			flushIt(row,col+1);
		}

		
		//Flush below.
		if(!is_wall[row][col-1] && !has_flushed[row][col-1]){

			//We have flushed it since it is adjacent, so we mark it.
			has_flushed[row][col-1] = true;

			//Flush around it
			flushIt(row,col-1);
		}
				
	}

	private static boolean itCanFlush(int row, int col) {
		
		//If this is a toilet, then it can flush.
		if(is_toilet[row][col])
			return true;
		
		//Check all four cardinal. If it is not a wall and not visited, see if it can be flushed.

		//Check above.
		if(!is_wall[row+1][col] && !visited[row+1][col]){
			
			//We have visited this one now, so we mark it.
			visited[row+1][col] = true;
			
			//Check to see if it can flush.
			if(itCanFlush(row+1,col))
				return true;
		}
		
		//Check below.
		if(!is_wall[row-1][col] && !visited[row-1][col]){
			
			//We have visited this one now, so we mark it.
			visited[row-1][col] = true;
			
			//Check to see if it can flush.
			if(itCanFlush(row-1,col))
				return true;
		}

		
		//Check the right.
		if(!is_wall[row][col+1] && !visited[row][col+1]){
			
			//We have visited this one now, so we mark it.
			visited[row][col+1] = true;
			
			//Check to see if it can flush.
			if(itCanFlush(row,col+1))
				return true;
		}

		
		//Check the left.
		if(!is_wall[row][col-1] && !visited[row][col-1]){
			
			//We have visited this one now, so we mark it.
			visited[row][col-1] = true;
			
			//Check to see if it can flush.
			if(itCanFlush(row,col-1))
				return true;
		}
		
		return false;
	}
}
