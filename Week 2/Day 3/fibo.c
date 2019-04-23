
#include <stdio.h>
#include <stdlib.h>

int fib(int);

int main()
{
  int num;
  printf("enter a value, we will find fib(value): ");
  scanf("%d", &num);
  int fibo = fib(num);
  printf("fib(%d) = %d\n", num, fibo);
}

int fib(int n)
{
  if (n < 2) //ignore negative values
    return n;
  return fib(n-1) + fib(n-2);
}