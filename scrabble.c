#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//define a boolean type for convenience
#define BOOL int
#define TRUE 1
#define FALSE 0

//list the tile scores
int scores[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

int pointVal(char* word) {
	//advance the word pointer, adding up the tile values along the way
	int total = 0;
	while(*word != '\0') {
		total += scores[*word-'A'];
		word++;
	}
	return total;
}

BOOL canMake(char* myWord, char* targetWord) {
	int i,freq[26] = {0}; //initialize a frequency array
	//for each char in myWord, increase the freq by one
	//remember that in c, strings are null terminated, so we can
	//keep looking until we reach null
	while(*myWord != '\0') {
		freq[*myWord-'A']++;
		myWord++;
	}
	//for each char in targetWord, decrease the freq by one
	while(*targetWord != '\0') {
		freq[*targetWord-'A']--;
		targetWord++;
	}
	//if any frequencies are negative, we cannot make the word
	for(i=0; i<26; i++)
		if(freq[i] < 0)
			return FALSE;

	return TRUE;
}

int main() {
	int n,r,i,j,bestPoints,testPoints;
	char myLetters[8], best[8];

	//read in the words
	scanf("%d", &n);
	char wordBank[n][8];
	for(i=0; i<n; i++)
		scanf("%s", wordBank[i]);

	//run through the test words
	scanf("%d", &r);
	for(i=1; i<=r; i++) {
		scanf("%s", myLetters);
		bestPoints = 0; //reset the best word

		//check each word
		for(j=0; j<n; j++) {
			//skip this word if we cannot make it
			if(!canMake(myLetters,wordBank[j])) continue;

			testPoints = pointVal(wordBank[j]);

			//if this is the new best
			if(testPoints > bestPoints || //default condition
				(testPoints == bestPoints && strcmp(wordBank[j],best) < 0)) { //tiebreaker condition
				bestPoints = testPoints;
				strcpy(best,wordBank[j]);
			}
		}

		//display the output
		printf("Tile Rack #%d: Playing %s earns %d points, the max possible.\n\n", i,best,bestPoints);
	}

	fclose(stdin);
	return 0;
}
