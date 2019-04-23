
#include <stdio.h>
#include <stdlib.h>

int main()
{
 
  int *p;  //contents of p are not defined
  int a;
  p = &a;  //p points at memory
 
  printf("enter value: ");
  scanf("%d",p);
  (*p)++;
  printf("inc. value is %d\n", *p);

  
}
