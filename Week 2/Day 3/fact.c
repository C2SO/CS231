
#include <stdio.h>
#include <stdlib.h>

int factor(int);

int main()
{
  int num;
  printf("enter a value, we will find factorial: ");
  scanf("%d", &num);
  int fact = factor(num);
  printf("%d! = %d\n", num, fact);
}

int factor(int n)
{
  if (n < 2) //ignore negative values
    return 1;
  return n * factor(n - 1);
}