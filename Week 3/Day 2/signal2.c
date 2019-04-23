//signal2.c
//infinite loop
//ignores interrupt
//can still stop, but use quit signal (ctl-\)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main()
{

  signal(SIGINT, SIG_IGN);
  
  while (1)
  {
    printf("ha ha, can't stop me. I am %d\n", getpid());
  }
}
