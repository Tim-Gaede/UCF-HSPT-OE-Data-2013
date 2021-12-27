// Solution to problem Umbrella
// Antony Stabile

// Solution Outline:
// If there are n rods, then the area of the triangle formed from two adjacent
// rods (length A and B) is A*B*sin(2*pi/n) / 2
// NOTE: This works for the degenerate cases as well (n==1 or n==2)
//
// Since the sin(2*pi/n) / 2 is constant, that may be factored out and multiplied
// at the end.
//
// The problem is thus: find a permutation of the lengths such that sum of the
// products of each adjacent pair (including the ends) is maximized
//
// There are up to 8 rods, so we may try all permutations

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926535897930
#define TRUE 1
#define FALSE 0
#define MAX 8

long long int tryPerms(int values[], int order[], int used[], int n, int k);

int main() 
{
	int numCases, numRods, i, t;
	int rods[MAX], used[MAX], order[MAX];
	double ans;

	scanf("%d", &numCases);
	
	for(t=1; t<=numCases; t++) {
		scanf("%d", &numRods);
		for(i=0; i<numRods; i++) {
			used[i] = FALSE;
			scanf("%d", &rods[i]);
		}
		ans = tryPerms(rods, order, used, numRods, 0) * sin(2*PI/numRods) / 2;
		printf("Umbrella #%d: %.3lf\n", t, ans+1e-9);
	}
}

long long int tryPerms(int values[], int order[], int used[], int n, int k)
{
	long long int ans = 0,tmp,i;
	if(k==n) {
		// find the product of all adjacent pairs for this permutation
		for(i=0; i<n; i++)
			ans += values[order[i]]*(long long int)values[order[(i+1)%n]];
		return ans;
	}
	// try all possible values for the k'th element
	for(i=0; i<n; i++) {
		if(!used[i]) {
			used[i] = TRUE;
			
			order[k] = i;
			tmp = tryPerms(values, order, used, n, k+1);
			
			// if that was a better choice, use it
			if(tmp > ans)
				ans = tmp;
			
			used[i] = FALSE;
		}
	}
	return ans;
}
