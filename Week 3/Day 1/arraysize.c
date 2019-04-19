
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int a[] = {1,2,3};
  printf("size of a is %lu\n", sizeof(a));

  int b[5] = {1,2,3};
  printf("size of b is %lu\n", sizeof(b));

  int i;
  for (i = 0; i < 5; i++)
    printf("%d\n", b[i]);

  char c[] = "hello";
  printf("size of c is %lu\n", sizeof(c));
}
