
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int a[5] = {0,0,0,0,0};
  int *p = a;

  *p = 7;
  printf("contents of p %x\n", (unsigned)p);

  int *r = p + 3;
   *r = 18;
  printf("contents of r %x\n", (unsigned)r);

  int i;

  for (i = 0; i < 5; i++)
    printf("a[%d] = %d\n", i, a[i]);

  printf("difference between r(%x) and p(%x): r - p = %ld\n",
	 (unsigned)r, (unsigned)p, r - p);
  
  
}
