/*
yuno.c
written by Nick Buelich
*/
#include <stdio.h>
#include <stdlib.h>
//max line size is 80, plus an extra 5 for safety
#define MAX_LINE_SIZE 85

void uppercase(char* string);

main()
{
	int n=0, i=0;
	//read in N, number of cases
	fscanf(stdin,"%d",&n);
	char line[MAX_LINE_SIZE];
	//junk line after N is read in
	fgets(line,MAX_LINE_SIZE,stdin);
	for(i=0;i<n;i++)
	{	
		//read in first line
		fgets(line,MAX_LINE_SIZE,stdin);
		//convert first line to uppercase
		uppercase(line);
		//print out first line then "..." added to the end
		printf("%s...\n", line);
		//read in second line
		fgets(line,MAX_LINE_SIZE,stdin);
		//convert second line to uppercase
		uppercase(line);
		//prints out "Y U NO " then second line
		printf("Y U NO %s?\n\n", line);
	}
	return 0;
}


//takes next line of input and converts the line to uppercase
//	also removes newline characters
void uppercase(char* string){
	int i =0;
	for(i=0;i<MAX_LINE_SIZE;i++){
		if(string[i]>='a'&&string[i]<='z')
			string[i]+=('A'-'a');
		else if(string[i]=='\n')string[i]=0;
	}
	return;
}

