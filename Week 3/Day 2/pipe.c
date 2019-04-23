/*
Interprocess Communication Using Pipes
Remove vowels from words in child process.
Parent uses pipe to send a string to child.
Child processes string and sends back message to parent on pipe.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void nullString(char * c, int size)
{
  int i;
  for(i = 0; i < size; i++)
    *c = '\0';
}

void removeVowels(char * src, char * dest)
{
  int splace = 0;
  int dplace = 0;
  while (*(src + splace) != '\0')
    {
      char c = *(src + splace);
      if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')
	{
          *(dest + dplace) = c;
	  dplace++;
	}
      splace++;
    }
  *(dest + dplace) = '\0';
  
}

int main()
{
  FILE * fromParent;
  FILE * toChild;
  pid_t pid;
  int fd[2];
  char msg[100];
  char outMsg[100];
  int len;
  nullString(msg, 100);
  nullString(outMsg, 100);
  pipe(fd);
  pid = fork();
  if (pid > 0) //parent
    {
      close(fd[0]); //close read end, child reads this
      
      while (fgets(msg, 100, stdin) != NULL)
	 {
	   len = strlen(msg);
	   write(fd[1], msg, len);
	 }
       close(fd[1]);//close remaining pipe end
       return 0;
    }
  else //child
    {
      close(fd[1]);//close write end, parent writes this
      dup2(fd[0], STDIN_FILENO);
      close(fd[0]);//not needed after dup2
      while (fgets(msg, 100, stdin) != NULL)
	{
          removeVowels(msg, outMsg);
	  printf("child did: %s\n",outMsg);
	}
      return 0;
    }

 
  
}
