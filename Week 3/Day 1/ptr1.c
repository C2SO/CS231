
#include <stdio.h>
#include <stdlib.h>

int main()
{
 
  int *p;
 
  printf("enter value: ");
  scanf("%d",p);
  (*p)++;
  printf("inc. value is %d\n", *p);

  
}
