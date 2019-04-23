#include <fnmatch.h>
#include <stdio.h>
#include <string.h>
#define MAX_FILE_NAME_CHARS 255

void checkArgs(int argc, char *argv[]);
void printFile(char *argv);
void printString(int ch);

int e, b, n, printed = 0;
char file_name[MAX_FILE_NAME_CHARS], ch;
int newLine, lineNumber = 1;
int blankLine = 0;

int main(int argc, char *argv[])
{

   if (argc < 1)
   {
      printf("Usage mycat <filename> \n");
      return 0;
   }

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
   char string[256];
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
