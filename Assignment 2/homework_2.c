/*  Thomas Belloli
    CS 231
    Assignemnt 2
*/
/*  This program will be read a line at a time from the keyboard. fgets 
    is used to read lines from the keyboard. This will perform input for
    100 lines, then enter control-D to stop input. The input lines will 
    be stored in an array of strings. This program will then reverse
    words, count letters, and count words. This program uses small 
    functions. Each function easily fits on a screen and has a specific 
    purpose.
    
    The program algorithm is:
    
    Print out the author information
    Create all the nessesary varables, including the array of strings, 
		the alphabet, and the variables to count letters and words
	make each string in the array of strings completely full of the '\0' 
		char
		
	read input tp a temp string, then put it into the array fo strings
	for every string in teh array:
		Remove every newline char
		reverse and count the worsd in the sring
		Count the number of letters in the string
		countLetters(tmp, letterCount, letterCountTmp);
		print the string with the reversed words, the number of words,
			and the number of each alphabetical char in teh string
		make the total number of words for the line 0   
		add the number of words in teh line to the total number of words
			for the whole input  
			     
	print the total number of each alphabetical character for the entire
		set of input
	print the total number of words for the entire set of input
*/
#include <stdio.h>
#include <string.h>

void reverse(char* begin, char* end); 

void first_Hundred(char *tmp, char *target)
{
/*
	first_Hundred is used to put the first 100 chars from tmp in target
	
make_all_null data table
NAME			DESCRIPTION
*tmp			This is the array that needs to have its first 100 chars
				returned
*target			This is the array that the first 100 go to
*/
	for (int index = 0; index < 100; index++)
	{
		*(target + index) = *(tmp + index);
	}
	*(target + 100) = '\0';
}

void countLetters(char *string, int *count, int *tmpCount)
/*
	CountLetters is used to count the number of each alphabetical letter
	in string, ignoring case.
	
countLetters Data Table
NAME		DESCRIPTION
*string		This is the string that is to be counted
*count		THis is the total count of each alphabetical letter
*tmpCount	This is the count of each alphabetical letter in this string
loAZ		This is a char array of the lowercase alphabet
hiAZ		This si a char array of the uppercase alphabet
 */
{
	char loAZ[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char hiAZ[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	for (int index = 0; string[index] != '\0'; index++)
	{
		for (int letter = 0; letter < 26; letter++)
		{
			if (string[index] == loAZ[letter] || 
				string[index] == hiAZ[letter])
			{
				count[letter]++;
				tmpCount[letter]++;
			}
		}
	}
}

void make_all_null(char *tmp, int size)
{
/*
	make_null is used to clear the temp array between uses
	
make_all_null data table
NAME			DESCRIPTION
tmp				This is the array that needs to be nulled out
size			This is passed to the method to get the length of the
				string
*/
	for(int index = 0; index < size; index++)
		*(tmp + index) = '\0';
}

void empty(int *tmp, int size)
{
/*
	empty is used to clear the temp array between uses
	
empty data table
NAME			DESCRIPTION
tmp				This is the array that needs to be nulled out
size			This is passed to the method to get the length of the
				string
*/
	for(int index = 0; index < size; index++)
		*(tmp + index) = 0;
}

int reverseWords(char* s) 
{ 
/*
	reverseWords is used to reverse the order of the words in a string
	
reverseWords Data Table
NAME			DESCRIPTION
*wordBegin		Used to store the location of the beggining of a word
				when it is found
*temp			used as a catch all pointer to help the method run by
				holding referances to characters in the string to help
				detect words
*wordCount		Count the number of words in the string, returned
*/
    char* wordBegin = s; 
    char* temp = s;
    int wordCount = 1;
    while (*temp) 
    { 
        temp++; 
        if (*temp == '\0') 
        { 
            reverse(wordBegin, temp - 1); 
        } 
        else if (*temp == ' ') 
        { 
            reverse(wordBegin, temp - 1); 
            wordBegin = temp + 1; 
            wordCount++;
        }
    }
    return wordCount;
}

void removeNL(char *string)
{
/*
	removeNL is used to remove the '\n' from strings, this is a step
	because newlines were messing up my word reversal algorithm
	
removeNL Data Table
NAME		DESCRIPTION
*string		This is the string that is passed to the method that needs
			its new line chars removed
*/
	for (int index = 0; index < 100; index++)
	{
		if (string[index] == '\n')
		{
			*(string + index) = '\0';
		}
	}
}

void reverse(char* begin, char* end) 
{
/*
	reverse is used to reverse the chars in a word, this was pulled out
	of reverseWord because the same algorithm was used mutiple times

reverse data table
NAME		DESCRIPTION
*begin		Used to pass the begining of the word
*end		Used to pass the end of the word
tmp			Use to hold chars for shorterm storage, help with reversal
*/
    char tmp; 
    while (begin < end) 
    { 
        tmp = *begin; 
        *begin++ = *end; 
        *end-- = tmp; 
    } 
}

int main(void)
{
/*  
    main is the function that runs the program. It takes input, count
    letters and numbers, reverses the words, then print the input back
    out with reversed words and the letters and word counts.
    
main data table
NAME                DESCRIPTION
str					100 strings, 101 chars each, the last one being 
					reserved for \0. Holds the input
tmp					a 100 char string used to hold input before it is
					placed in the string array
pos					the position number in the array of strings str
firstL				holds the first line to fix an input error
*rdflag				holds the result of reading the lines if input
					initaly points to any char so it is not null
letterCount			counts the alpabetical letters: 
					index of 0 is 'a' , 1 is 'b' ...
letterCountTmp		counts the total number of alphabetical letters
					index of 0 is 'a' , 1 is 'b' ...
wrdCntTotal			holds total word count
wrdCnt 				holds the word count for the string, is wiped after
					each string
loAZ				This is a char array of the lowercase alphabet
*/
	printf("Thomas Belloli\n\nAssingment 2 - Mutating input data\n");
	char loAZ[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char str[100][101];
	char tmp[100];
	char firstL[100];
	int pos=0;
	int letterCount[26];
	int letterCountTmp[26];
	int wrdCntTotal = 0;
	char* rdflag = &tmp[0];
	for (int index = 0; index < 100; index++)
		make_all_null(str[index], 101);
	while (rdflag != NULL){
		if (pos >= 100)	/**/	break;
		rdflag = fgets(tmp, 101, stdin);
		first_Hundred(tmp, str[pos]);
		if (pos == 0) /**/	first_Hundred(tmp, firstL);
		if (rdflag != NULL) /**/	pos++;
		else /**/	rdflag = NULL;
	}
	first_Hundred(firstL, str[0]);
	for (int index = 0; index < pos; index++) {
		first_Hundred(str[index],tmp);
		removeNL(tmp);
		int wrdCnt = reverseWords(tmp);
		countLetters(tmp, letterCount, letterCountTmp);
		printf("\nLine %02d: '%s'", index + 1, tmp);  
		if (tmp[0] == '\0')/**/	printf("\n\tWord Count: %02d",--wrdCnt); 
		else /**/	printf("\n\tWord Count: %02d",wrdCnt); 
		printf("\n\tNumber of letters:");
		for (int letter = 0; letter < 26; letter++)
			printf(" %c:%02d",loAZ[letter],letterCountTmp[letter]);
		empty(letterCountTmp, 26);    
		wrdCntTotal += wrdCnt;        
	}
	printf("\n\nTotal Number of letters:");
		for (int letter = 0; letter < 26; letter++)
			printf(" %c:%02d",loAZ[letter],letterCount[letter]);
	printf("\nTotal Word Count: %02d\n",wrdCntTotal); 
}