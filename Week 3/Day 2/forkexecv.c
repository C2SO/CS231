#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[], char * envp[])
{
  pid_t pid;
  char * arg[4];
  arg[0] = "ls";
  arg[1] = "-l";
  arg[2] = NULL;
  pid = fork();
   if (pid == 0)
   {
     char * en[2];
     en[0] = "stuff";
     en[1] = NULL;

      execle("./env","env", NULL, en);

   }

   else
   {
     pid = fork();

     if (pid == 0)
       {
         execvp(arg[0], arg);
	 printf("This will not print, code replaced by ls -l");
       }
   }
}
