#include <stdio.h>
#include <stdlib.h>

int num0s(int);

int main()
{
  int num;
  printf("enter a value, we will find number of zeroes at end of factorial: ");
  scanf("%d", &num);
  int zeroes = num0s(num);
  printf("Number of zeroes at end of %d! is %d\n", num, zeroes);
}

int num0s(int n)
{
  if (n < 5) //ignore negative values
    return 0;
  return n / 5 + num0s(n / 5);
}
