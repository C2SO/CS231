//Nicholas Rahbany

#include <stdio.h>

int tons;
double pounds;
double remaining = -1;

double output(int, double);

int main()
{
  printf ("How many tons is the maximum weight? > ");
  scanf("%d", &tons);
  printf("How many pounds? > ");
  scanf("%lf", &pounds);
  remaining = output(tons, pounds);
  printf("\n");
  printf("Nicholas Rahbany \n");
  printf("Total number of tons: %d\n", tons);
  printf("Inputted number of pounds: %.2f\n", pounds);
  printf("Remaining number of pounds: %.2f\n", remaining);
  return 0; 
}

double tonsToPounds;

double output(int t, double p)
{
  //Every ton has 2000 pounds
  tonsToPounds = (t * 2000);
  return tonsToPounds - pounds;
}
