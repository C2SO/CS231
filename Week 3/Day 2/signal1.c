//signal1.c
//infinite loop
//stop with interrupt (ctl-c)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
  while (1)
  {
    printf("ha ha, can't stop me. I am %d\n", getpid());
  }
}
