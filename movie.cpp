#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// ************************************************
// HSPT Online - Ali's Movie Collection - movie.cpp
// ************************************************

// Write a custom comparator to sort the Movie Titles
bool movieCompare(string s1, string s2)
{
	string temp1;
	string temp2;
	for (int i = 0; i < s1.length(); ++i)
		temp1.push_back(toupper(s1[i]));
	for (int i = 0; i < s2.length(); ++i)
		temp2.push_back(toupper(s2[i]));
		
	//cout << "ORIGINAL | " << temp1 << " : " << temp2 << endl;

	// Remove any beginning 'THE's
	if (temp1.length() >= 4 && temp1.substr(0,4).compare("THE ") == 0) temp1 = temp1.substr(4);
	if (temp2.length() >= 4 && temp2.substr(0,4).compare("THE ") == 0) temp2 = temp2.substr(4);

	// Replace each word version of a number at the end of a movie title with the arabic numeral version
	if (temp1.length() >= 4 && temp1.substr(temp1.length()-4).compare(" ONE") == 0) { temp1 = temp1.substr(0, temp1.length()-3); temp1.push_back('1'); }
	else if (temp1.length() >= 4 && temp1.substr(temp1.length()-4).compare(" TWO") == 0) { temp1 = temp1.substr(0, temp1.length()-3); temp1.push_back('2'); }
	else if (temp1.length() >= 6 && temp1.substr(temp1.length()-6).compare(" THREE") == 0) { temp1 = temp1.substr(0, temp1.length()-5); temp1.push_back('3'); }
	else if (temp1.length() >= 5 && temp1.substr(temp1.length()-5).compare(" FOUR") == 0) { temp1 = temp1.substr(0, temp1.length()-4); temp1.push_back('4'); }
	else if (temp1.length() >= 5 && temp1.substr(temp1.length()-5).compare(" FIVE") == 0) { temp1 = temp1.substr(0, temp1.length()-4); temp1.push_back('5'); }
	else if (temp1.length() >= 4 && temp1.substr(temp1.length()-4).compare(" SIX") == 0) { temp1 = temp1.substr(0, temp1.length()-3); temp1.push_back('6'); }
	else if (temp1.length() >= 6 && temp1.substr(temp1.length()-6).compare(" SEVEN") == 0) { temp1 = temp1.substr(0, temp1.length()-5); temp1.push_back('7'); }
	else if (temp1.length() >= 6 && temp1.substr(temp1.length()-6).compare(" EIGHT") == 0) { temp1 = temp1.substr(0, temp1.length()-5); temp1.push_back('8'); }
	else if (temp1.length() >= 5 && temp1.substr(temp1.length()-5).compare(" NINE") == 0) { temp1 = temp1.substr(0, temp1.length()-4); temp1.push_back('9'); }
	else if (temp1.length() >= 4 && temp1.substr(temp1.length()-4).compare(" TEN") == 0) { temp1 = temp1.substr(0, temp1.length()-3); temp1.push_back(':'); }
	else if (temp1.length() >= 3 && temp1.substr(temp1.length()-3).compare(" 10") == 0) { temp1 = temp1.substr(0, temp1.length()-2); temp1.push_back(':'); }
	else if (	temp1.length() <= 2 || (temp1.substr(temp1.length()-2).compare(" 1") != 0 && 
				temp1.substr(temp1.length()-2).compare(" 2") != 0 && 
				temp1.substr(temp1.length()-2).compare(" 3") != 0 && 
				temp1.substr(temp1.length()-2).compare(" 4") != 0 && 
				temp1.substr(temp1.length()-2).compare(" 5") != 0 && 
				temp1.substr(temp1.length()-2).compare(" 6") != 0 && 
				temp1.substr(temp1.length()-2).compare(" 7") != 0 && 
				temp1.substr(temp1.length()-2).compare(" 8") != 0 && 
				temp1.substr(temp1.length()-2).compare(" 9") != 0)) temp1.append(" 1");
	
	if (temp2.length() >= 4 && temp2.substr(temp2.length()-4).compare(" ONE") == 0) { temp2 = temp2.substr(0, temp2.length()-3); temp2.push_back('1'); }
	else if (temp2.length() >= 4 && temp2.substr(temp2.length()-4).compare(" TWO") == 0) { temp2 = temp2.substr(0, temp2.length()-3); temp2.push_back('2'); }
	else if (temp2.length() >= 6 && temp2.substr(temp2.length()-6).compare(" THREE") == 0) { temp2 = temp2.substr(0, temp2.length()-5); temp2.push_back('3'); }
	else if (temp2.length() >= 5 && temp2.substr(temp2.length()-5).compare(" FOUR") == 0) { temp2 = temp2.substr(0, temp2.length()-4); temp2.push_back('4'); }
	else if (temp2.length() >= 5 && temp2.substr(temp2.length()-5).compare(" FIVE") == 0) { temp2 = temp2.substr(0, temp2.length()-4); temp2.push_back('5'); }
	else if (temp2.length() >= 4 && temp2.substr(temp2.length()-4).compare(" SIX") == 0) { temp2 = temp2.substr(0, temp2.length()-3); temp2.push_back('6'); }
	else if (temp2.length() >= 6 && temp2.substr(temp2.length()-6).compare(" SEVEN") == 0) { temp2 = temp2.substr(0, temp2.length()-5); temp2.push_back('7'); }
	else if (temp2.length() >= 6 && temp2.substr(temp2.length()-6).compare(" EIGHT") == 0) { temp2 = temp2.substr(0, temp2.length()-5); temp2.push_back('8'); }
	else if (temp2.length() >= 5 && temp2.substr(temp2.length()-5).compare(" NINE") == 0) { temp2 = temp2.substr(0, temp2.length()-4); temp2.push_back('9'); }
	else if (temp2.length() >= 4 && temp2.substr(temp2.length()-4).compare(" TEN") == 0) { temp2 = temp2.substr(0, temp2.length()-3); temp2.push_back(':'); }
	else if (temp2.length() >= 3 && temp2.substr(temp2.length()-3).compare(" 10") == 0) { temp2 = temp2.substr(0, temp2.length()-2); temp2.push_back(':'); }
	else if (	temp2.length() <= 2 || (temp2.substr(temp2.length()-2).compare(" 1") != 0 && 
				temp2.substr(temp2.length()-2).compare(" 2") != 0 && 
				temp2.substr(temp2.length()-2).compare(" 3") != 0 && 
				temp2.substr(temp2.length()-2).compare(" 4") != 0 && 
				temp2.substr(temp2.length()-2).compare(" 5") != 0 && 
				temp2.substr(temp2.length()-2).compare(" 6") != 0 && 
				temp2.substr(temp2.length()-2).compare(" 7") != 0 && 
				temp2.substr(temp2.length()-2).compare(" 8") != 0 && 
				temp2.substr(temp2.length()-2).compare(" 9") != 0)) temp2.append(" 1");

	//cout << "SORTING | " << temp1 << " : " << temp2 << endl;
	
	return lexicographical_compare(temp1.begin(), temp1.end(), temp2.begin(), temp2.end());
}

// Main Function
int main()
{
	// Read in the number of trials we have to go
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t)
	{
		// Read in the number of movies we have to sort
		int N;
		scanf("%d", &N);
		string temp;
		getline(cin, temp);
	
		// Read in each line of the input
		string movies[N];
		for (int n = 0; n < N; ++n)
			getline(cin, movies[n]);
	
		sort(movies, movies+N, movieCompare);

		// Output the sorted list
		printf("Movie Collection #%d:\n", t);
		for (int n = 0; n < N; ++n)
			cout << movies[n] << endl;
		printf("\n");
	}

	return 0;
}
