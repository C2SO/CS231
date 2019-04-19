#include <stdio.h>
#include <string.h>
#define MAX_FILE_NAME_CHARS 255

void checkArgs(int argc, char *argv[]);
void printFile(int argc, char *argv);

int e, b, n, printed = 0;
char file_name[MAX_FILE_NAME_CHARS], ch;
int newLine, lineNumber = 1;

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
      if (strstr(argv[i], "-") == NULL)
      {
         printFile(argc, argv[i]);
      }
   }

   return 1;
}

void checkArgs(int argc, char *argv[])
{

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
}

void printFile(int argc, char *argv)
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
      if (ch == '\n')
      {
         if (e == 1)
         {
            printf("$");
         }
         lineNumber++;
         newLine = 1;
      }
      else if (newLine == 1 && n == 1)
      {
         printf("     %d  ", lineNumber);
         newLine = 0;
      }
      else if (printed == 0) {
         printf("     %d  ", lineNumber);
         printed = 1;
      }
      putchar(ch);
   }
   fclose(fp);
}
