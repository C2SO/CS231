#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[], char * envp[])
{
  printf("parent, id is %d\n", getpid());
  int pid;

  pid = fork();
  if (pid > 0)
    {
      printf("parent process. My child id is %d\n", pid);
      sleep(2);
      exit(0);
    }
  else
    {
      printf("child process, id is %d\n", getpid());
      printf("my parent has id %d\n", getppid());
      sleep(5);
      printf("my parent has id %d\n", getppid());
    }
  
}
