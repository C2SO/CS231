// Nicholas Rahbany
// CS231
// assignment2.c

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define LARGEST 1000

void print_title_author(char * title, char * proginfo)
{
  // I liked how you added this in your code, so I am chosing to implement it in mine    
  printf("\n%s\n", title);
  printf("Nicholas Rahbany\nCPSC231\n%s\n\n", proginfo);
}
int main()
{
  print_title_author("Assignment 2", 
                   "Reverse Strings & Count Letters");

  char arr[100];
  char upperArr[100];

  printf("\nInput Text >>> ");
  scanf("%s", arr);

  strcpy(upperArr, arr);
  for(char* c=upperArr; *c=toupper(*c); ++c);

  printf("%s\n", upperArr);
}