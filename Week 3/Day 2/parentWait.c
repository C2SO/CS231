#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[], char * envp[])
{
  printf("parent, id is %d\n", getpid());
  int pid;
  int status;

  pid = fork();
  if (pid > 0)
    {
      printf("parent process. My child id is %d\n", pid);
      pid = wait(&status);
      printf("wait returned %d\n", pid);
      printf("child status is %X\n",status);
    }
  else
    {
      printf("child process, id is %d\n", getpid());
      printf("my parent has id %d\n", getppid());
      exit(5);
    }
  
}
