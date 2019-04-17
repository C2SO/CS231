// Nicholas Rahbany
// CS231
// assignment2.c

// The purpose of this program is to learn how to manipulate a string
// and learn to work with C. The requirements of this project was to 
// be able to input a string (or in this case 100 strings), count the 
// number of letters in them, reverse them, and return the total 
// amount of letters that were in the string

// The Algorith is as follows:
//   Define the text input you want
//   If the file cannot be found
//     Exit the program
//   While it is not the end of the file
//     Copy the current line into an array
//     If there is a letter at this current index
//       Increase the tally of that letter
//     Do the same with capital letters
//     While the string is not at it's end
//       For each index for stringRev
//         Store the letter in the array
//       Print the reversed string
//       Print how many of each letter was used (if it was used)
//     Print the total number of hits for each letter


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_title_author(char * title, char * progInfo);
int words(const char sentence[ ]);

void print_title_author(char * title, char * progInfo)
{
  // I liked how you added this in your code, so I am chosing
  // to implement it in mine   

  // This function will print the title and thhe program's info that
  // is passed into the function.

  // data table

  // NAME     | Description
  // title    | The title of the program
  // progInfo | The program info

  printf("\n%s\n", title);
  printf("Nicholas Rahbany\nCPSC231\n%s\n\n", progInfo);
}

int main()
{
  // This is the controling function for the program. It will set all
  // the global indexes to 0 and will create the char arrays.
  // There is a loop that will continue until the File that is definded
  // by the user does not have any more lines left to read. In that
  // loop, it will call the words function, will reverse the current
  // line, and will tally each letter that is called

  // main data table

  // NAME         | DESCRIPTION
  // countTotal[] | The array which holds the total tally for each letter
  // file_name    | The file name that is defined by the user
  // string[]     | Used as the current line of the file
  // stringRev[]  | The reversed line of the file
  // count[]      | The array which holds the line's tally for each letter
  // fp           | The file object that is opened
  // line         | The current line of fp
  // len          | Used as the length in getline()
  // read         | Used to check if the line has ended

  print_title_author("Assignment 2", 
                   "Reverse Strings & Count Letters");

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

  for (int c2 = 0; c2 < 26; c2++) {
    if (countTotal[c2] != 0) {
      printf("%c occurs %d times in total.\n", c2 + 'a', countTotal[c2]);
    }
  }
  
  return 0;
}

int words(const char sentence[ ])
{
  // words will count the number of words that are in the string

  // data table

  // NAME     | Description
  // sentence | The string that will have it's words counted

    int counted = 0;

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