
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 20
//pick some number larger than expected size of line
//any line larger than this, throw away rest of input line
//I am using a small line size for demonstration purposes
//   (I do not want to type and count over 100 characters in a line)

void clearLine(FILE * file)
{
 
  char c = getc(file);
  while (c != '\n')
    c = getc(file);
}

int main()
{
  char inputLine[MAX_LINE_SIZE];
  char ** strArrayPtr = malloc(10*sizeof(char *));
  
  int strIndex = 0;
  int currentArraySize = 10;
  FILE * in = fopen("input.txt", "r");
  FILE * out = fopen("output.txt", "w");
  char * inputResults;
  int i;
 
  inputResults = fgets(inputLine, MAX_LINE_SIZE, in);
 
  while (inputResults != NULL)
    {
 
      if (strIndex == currentArraySize)
	{
          currentArraySize += 10;
	  strArrayPtr = realloc(strArrayPtr, currentArraySize * sizeof(char *));
	}
      
      int len = strlen(inputLine);
     
      if (len == MAX_LINE_SIZE - 1 && inputLine[MAX_LINE_SIZE - 1] != '\n')
	{
	 
	   * (strArrayPtr + strIndex) = malloc(MAX_LINE_SIZE);
	   inputLine[MAX_LINE_SIZE - 1] = '\0';
	   fprintf(stderr,"%s\n", inputLine);
	   strncpy(*(strArrayPtr + strIndex), inputLine,
         	      MAX_LINE_SIZE);
	    clearLine(in); //remove remainder of input line

	}
      else
	{

          char * nlPtr = strchr(inputLine, '\n');

	  if (nlPtr != NULL)
	    *nlPtr = '\0';

	  *(strArrayPtr + strIndex) = malloc(strlen(inputLine) + 1);
	  strncpy(*(strArrayPtr + strIndex), inputLine,
         	      MAX_LINE_SIZE - 1);
	  
	}
     
      strIndex++;
      inputResults = fgets(inputLine, MAX_LINE_SIZE, in);
    }
 
  for (i = strIndex - 1; i >= 0; i--)
    fprintf(out, "%s\n", *(strArrayPtr + i));
    
 }
