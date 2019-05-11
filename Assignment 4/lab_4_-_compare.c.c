/* 
	Thomas Belloli
	CS231 lab 4
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_LEN 100

char *lowerWord(char *word) 
{
/*  
	lowerWord returnes word but lowercse. it does this by useing the 
	tolower function on each char in word.
    
data table
NAME         DESCRIPTION
word         parameter - the word to make into lowercase
length       length of word
pong         the lowercase word that will be returned
*/
    int length = strlen(word);
    char *pong = malloc(length);
    for (int letter = 0; letter < length; letter++)
        pong[letter] = (char)tolower(word[letter]);
    return pong;
}

void compWords(FILE *dictionary) 
{
/*  
	compWords takes a line from standard in, and compares it to every 
	word in the provided dictionary file until a match is found or i run
	out of words to check. the words are then printed out with 
	information or weather or not they are correct
    
data table
NAME            DESCRIPTION
dictionary 		parameter - pointer to the dictionary file
realWord        a word from the dictionary file
fakeWord        a word from stdin
realWordB       boolean for tracking whether a word was spelled 
					correctly or not
*/
    char realWord[MAX_LEN];
    char fakeWord[MAX_LEN];
    while(fgets(fakeWord, MAX_LEN, stdin) != NULL) 
    {
        int realWordB = 0;
        while(fgets(realWord, MAX_LEN, dictionary)) 
        {
            if (!strcmp(lowerWord(fakeWord), lowerWord(realWord))) 
            {
                realWordB = 1;
                break;
            }
        }
        rewind(dictionary);
        if (realWordB)
            printf("Correct: %s", fakeWord);
        else
            printf("Incorrect: %s", fakeWord);
    }
}

int main(int argc, char *argv[]) 
{
/*  
	main takes the name of a dictonary file as an argument, makes sure 
	that the file exists, then has compWords check if the words from 
	stdin are correct.
    
data table
NAME    DESCRIPTION
argc    parameter - the number of commandline arguments
argv    parameter - the commandline arguments
file	pointer to the file name at argv[1]
*/
    if (argc < 2) 
        fprintf(stderr, "compare: No file supplied\n");
    if (argc > 2) 
        fprintf(stderr, "compare: More than one file supplied\n");
    if (argc != 2)
		exit(1);
    FILE *file = fopen(argv[1], "r"); 
    if (file == NULL) //check file existance
    {
       fprintf(stderr, "compare: No such file for directory: %s\n", argv[1]);
       exit(1);
    }
    compWords(file);
    fclose(file);
    return 0;
}