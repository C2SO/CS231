//signal4.c
//infinite loop
//unreliable signal handling


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void handler(int);

int main()
{

  signal(SIGINT, handler);
  signal(SIGQUIT, handler);
  
  while (1)
  {
    printf("ha ha, can't stop me. I am %d\n", getpid());
    sleep(2);
  }
}

void handler(int signum)
{
  if (signum == SIGINT)
    {
      printf("ouch\n");
      sleep(1);
      return;
    }
  printf("that really hurts!\n");
    exit(0);
}
