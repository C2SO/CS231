//signal3.c
//infinite loop
//cannot interrupt or kill with quit
//use kill signal from terminal to terminate

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main()
{

  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  
  while (1)
  {
    printf("ha ha, can't stop me. I am %d\n", getpid());
  }
}
