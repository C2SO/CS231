//show various string functions, pointers, arrays of char as strings
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
  function to initialize a string to the empty string
 */
void make_null(char * s)
{
  *s = '\0';
}

/*
  function to put '\0' in every slot of array,
  if user initializes array by placing in characters, this
  provides a safety net.
 */
void make_all_null(char *s, int size)
{
  int charPos;
  for(charPos = 0; charPos < size; charPos++)
    *(s + charPos) = '\0';
}

int main()
{
  char c = 'A';
  char *p;
  char s[100];
  int i;

  make_null(s);
  int length = strlen(s);
  printf("The length of s is %d.  It should be 0.\n", length);
  p = &c;
  printf("\n%c%c%c\nint value: %d\naddress: %u\n",*p, *p+1, *p+2,
	   *p, (unsigned)p);

  make_all_null(s, 100);
  s[0] = 'a';
  s[1] = 'b';
  s[2] = 'c';
  p = s;
  printf("\n%s%s%c%s\n", s, p, *(p + 1), p + 1);

  strcpy(s, "\nshe sells sea shells");
  printf(s); //insecure possibly
  printf("\n%s\n", s);
  strcat(s, " by the seashore");
  printf("\n%s\n", s);
  int comp = strcmp(s, "\nshe buys macaroni shells");
  printf("comparison value: %d positive, s1 > s2\n", comp);
  comp = strcmp("\nshe buys macaroni shells", s);
  printf("comparison value: %d negative, s1 < s2\n", comp);
  comp = strcmp(s, s);
  printf("comparison value: %d zero, s1 == s2\n", comp);
  for(p = s, p += 17; *p != '\0'; ++p)
  {
    if(*p == 'e')
      *p = toupper(*p);
    if(isspace(*p))
      *p = '\n';
  }
  printf("%s\n",s);

  int number = atoi("42");
  printf("\n%d should be 42\n", number);

  int values[10];
  int * valPtr = values;
  for (i =0; i < 10; i++)
    values[i] = i * 10;
  printf("\nfirst value in array should be 0: %d\n", *valPtr);
  printf("\naddress contained in valPtr is %u\n", (unsigned)valPtr);
  valPtr = valPtr + 5;
  printf("\n value in array at index 5 should be 50: %d\n", *valPtr);
  printf("\nnew address contained in p is %u\n", (unsigned)valPtr);
}
