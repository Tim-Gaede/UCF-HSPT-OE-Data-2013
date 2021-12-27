#include <stdio.h>
int main()
{
    /*
    I plan to take each word in each game, and count how many of each letter is present.
    Then, I will run through and count how many letters have a count of 0 (or which letters
    we can guess wrong). Finally, if the number of wrong guesses we can make is at least the
    number of wrong guesses given, we can troll.
    */
    char str[31];
    int used[26];
    int cases,words,guesses,i,j,k,index,count;
    fscanf(stdin,"%d",&cases);
    for(i=1;i<=cases;i++)
    {
        fscanf(stdin,"%d %d",&words,&guesses);
        for(j=0;j<26;j++)
            used[j]=0;
        for(j=0;j<words;j++)
        {
            for(k=0;k<31;k++)
                str[k]=0;
            fscanf(stdin,"%s",str);
            for(k=0;k<31;k++)
            {
                //We find the index by taking our char and subtracting from the lowest char
                //of that case. So if we are lowercase, we subtract from 'a'.
                //E.g., 'e'-'a'=4, 'T'-'A'=19
                if(str[k]==0)
                    break;
                if(str[k]==' ')
                    continue;
                //If the letter is lowercase, subtract from lowercase a
                if((str[k])>=97)
                    index=(str[k])-('a');
                //otherwise, subtract from uppercase A
                else
                    index=str[k]-'A';
                //Say we have at least one of this letter
                used[index]++;
            }
            count=0;
        }
        for(j=0;j<26;j++)
        {
            if(used[j]==0)//If we can guess this letter and be wrong
                count++;
        }
        if(count>=guesses)
            printf("Game #%d: Trolling succeeded\n\n",i);
        else
            printf("Game #%d: Impossible to lose\n\n",i);
    }
    return 0;
}
