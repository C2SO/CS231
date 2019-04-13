// Nicholas Rahbany
// CS231
// assignment2.c

#include <ctype.h>
#include <stdio.h>
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

  char string[100];
  int c = 0, count[26] = {0}, x;
     
  printf("Enter a string\n");
  fgets(string, 100, stdin);
    
  while (string[c] != '\0') {
  /** Considering characters from 'a' to 'z' only and ignoring others. */
     
    if (string[c] >= 'a' && string[c] <= 'z') {
      x = string[c] - 'a';
      count[x]++;
    }
     
    c++;
  }

  printf("%d word(s) in this string\n", words(string));

  for (c = 0; c < 26; c++)
    if (count[c] != 0) {
      printf("%c occurs %d times in the string.\n", c + 'a', count[c]);
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
        case ' ': case '\t': case '\n': case '\r': // TODO others?
            if (inword) { inword = 0; counted++; }
            break;
        default: inword = 1;
    } while(*it++);

    return counted;
}