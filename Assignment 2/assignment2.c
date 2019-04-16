// Nicholas Rahbany
// CS231
// assignment2.c

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_title_author(char * title, char * proginfo);
int words(const char sentence[ ]);

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

  int c2 = 0;
  int countTotal[26] = {0};
  char file_name[25];
  char stringRev[100];
  char string[100];
  int count[26] = {0};

  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  size_t read;
 
  printf("Enter name of a file you wish to see >>> ");
  gets(file_name);
 
  fp = fopen(file_name, "r"); // read mode
 
  if (fp == NULL)
  {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }

  while ((read = getline(&line, &len, fp)) != EOF) {

    strcpy(string, line);

    int c = 0;
    while (string[c] != '\0') {
    /** Considering characters from 'a' to 'z' only and ignoring others. */
     
      if (string[c] >= 'a' && string[c] <= 'z') {
        int x = string[c] - 'a';
        count[x]++;
        countTotal[x]++;
      }

      else if (string[c] >= 'A' && string[c] <= 'Z') {
        int x = string[c] - 'A';
        count[x]++;
        countTotal[x]++;
      }
     
      c++;
    }

    int reverseIndex, begin, end = 0;
    while (string[reverseIndex] != '\0') {
      reverseIndex++;
      end = reverseIndex - 1;
      for (begin = 0; begin < reverseIndex; begin++) {
        stringRev[begin] = string[end];
        end--;
      }
      stringRev[begin] = '\0';
    }
    printf("\nReversed String: %s", stringRev);
    memset(stringRev, 0, sizeof stringRev);

    printf("\n\n%d word(s) in this string\n", words(string));

    for (int index = 0; index < 26; index++) {
      if (count[index] != 0) {
        printf("%c occurs %d times in the string.\n", index + 'a', count[index]);
      }
    }

  }

  printf("\n");

  for (c2 = 0; c2 < 26; c2++) {
    if (countTotal[c2] != 0) {
      printf("%c occurs %d times in total.\n", c2 + 'a', countTotal[c2]);
    }
  }
  
  return 0;
}

int words(const char sentence[ ])
{
    int counted = 0; // result

    // state:
    const char* it = sentence;
    int inword = 0;

    do switch(*it) {
        case '\0': 
        case ' ': case '\t': case '\n': case '\r':
            if (inword) { inword = 0; counted++; }
            break;
        default: inword = 1;
    } while(*it++);

    return counted;
}