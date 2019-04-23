#include <stdio.h>
#include <stdlib.h>




int and(int a, int b)
{
  return a && b;
}

int or(int a, int b)
{
  return a || b;
}

void booleanFunction(int val1, int val2, int (*bool)(int, int))
{
  printf("the result of the boolean function on %d and %d is %d\n",
              val1, val2, bool(val1, val2));
}

int main()
{
  int and = 17;
  booleanFunction(0, 1, or);
  booleanFunction(0, 1, and);
  return 0;
}