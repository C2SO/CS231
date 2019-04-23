
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int a = 7;
  int *p = &a;

  char c = '@';
  char * cp = &c;
 
  printf("value of a is %d, a is at address %x\n", a, (unsigned)(&a));
  printf("contents of p are %x\n", (unsigned)p);

  printf("value of c is %c, c is at address %x\n", c, (unsigned)(&c));
  printf("contents of cp are %x\n", (unsigned)cp);

  
}
