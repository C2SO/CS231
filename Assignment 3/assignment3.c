// Nicholas Rahbany
// CS231
// assignment3.c

// The purpose of this program is to learn how the "cat"
// function works while also accepting user input, manipulating
// data, and understanding standard _IOS_INPUT

// The algorithm is as follows:
//    If there is no file that matches the specifiec, throw an error
//    Check the arguments of the command
//    for each argument in the command
//       If the command is "-"
//          Accept the user's standard input
//       Else if the command does not contain "-"
//          Print the text of the files with the format specified by the arguments

#include <fnmatch.h>
#include <stdio.h>
#include <string.h>
#define MAX_FILE_NAME_CHARS 255 // The max length of a file name

void checkArgs(int argc, char *argv[]);
void printFile(char *argv);
void printString(int ch);

int e, b, n, printed = 0; // e, b, and n are used from the arguments while printed
                          // is the boolean that checks if anything printed 
char file_name[MAX_FILE_NAME_CHARS], ch; // Stores the file names
int newLine, lineNumber = 1; // newLine is a boolean to determine if it is a new line
                             // lineNumber stores the line number

int main(int argc, char *argv[])
{
   // This is the starting point of the program. It will take the input
   // and distribute it to checkArgs, printFile, and printString

   // Name | Description
   // argc | Number of arguments made
   // argv | Stores the arguments made

   checkArgs(argc, argv);

   for (int i = 1; i < argc; i++)
   {
      if (0 == fnmatch("-", argv[i], 0))
      {
         int e;
         while ((e = getchar()) != EOF)
         {
            printString(e);
         }
      }
      else if (strstr(argv[i], "-") == NULL)
      {
         printFile(argv[i]);
      }
   }

   return 1;
}

void checkArgs(int argc, char *argv[])
{

   // This function checks the user's arguments and sets booleans based on each
   // argument that the user wants

   // Name | Description
   // argc | Number of arguments made
   // argv | Stores the arguments made
   
   for (int i = 1; i < argc; i++)
   {

      if (strstr(argv[i], "-") != NULL)
      {
         if (strstr(argv[i], "E") != NULL)
         {
            e = 1;
         }
         if (strstr(argv[i], "b") != NULL)
         {
            b = 1;
         }
         if (strstr(argv[i], "n") != NULL)
         {
            n = 1;
         }
      }
   }

   if (b == 1 && n == 1)
   {
      n = 0;
   }
}

void printFile(char *argv)
{

   // The function of this... function... is to send a text file to it,
   // which it will then send the arguments to printString or will return
   // an error to the user

   // Name      | Description
   // argv      | The file name
   // fp        | Used to define the opened file
   // file_name | The specific file the program is looking at
   // ch        | The current character of the open file


   FILE *fp;
   char file_name[MAX_FILE_NAME_CHARS], ch;

   strncpy(file_name, argv, MAX_FILE_NAME_CHARS);

   fp = fopen(file_name, "r");
   if (fp == NULL)
   {
      printf("%s: No such file or directory\n", file_name);
      return;
   }

   while ((ch = fgetc(fp)) != EOF)
   {
      printString(ch);
   }
   fclose(fp);
}

void printString(int ch)
{

   // The role of this function is to print what was passed in

   // Name | Description
   // ch   | The character that is passed in

   if (ch == '\n')
   {
      if (e == 1)
      {
         printf("$");
      }
      if (newLine == 1 && b == 1)
      {
         lineNumber--;
      }
      if (newLine == 1 && n == 1)
      {
         printf("     %d  ", lineNumber);
         printed = 1;
      }
      lineNumber++;
      newLine = 1;
   }
   else if (b == 1 || n == 1)
   {
      if (printed == 0 || newLine == 1)
      {
         printf("     %d  ", lineNumber);
      }
      newLine = 0;
      printed = 1;
   }
   putchar(ch);
}
