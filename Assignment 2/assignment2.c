// Nicholas Rahbany
// CS231
// assignment2.c

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define LARGEST 1000

void print_title_author(char * title, char * proginfo)
{
  printf("%s\n", title);
  printf("Nicholas Rahbany\nCS231-01\n%s\n\n", proginfo);
}

void compute_primes(int * sieve)  //Note, an array of int was passed into this function
{
  int next_prime;
  int next_multiple;

  *sieve = FALSE;
  *(sieve+1) = FALSE;

  next_prime = 2;
  while (next_prime <= LARGEST)
  {
    if ( *(sieve + next_prime))
    {
      next_multiple = next_prime * 2;
      while (next_multiple <= LARGEST)
      {
        *(sieve + next_multiple) = FALSE;
        next_multiple += next_prime;
      }
    }
    next_prime++;
  }
}

int next_prime(int prime, int * sieve)
{
  prime++;
  while (prime <= LARGEST)
  {
    if (*(sieve + prime)) return prime;
    prime++;
  }
  return -1;
}

int main(int argc, char * argv[], char * env[])
{
  int sieve[LARGEST + 1]; //Notice: this is an array of int
  int current_prime;
  int value;
  int i;

  print_title_author("Assignment 2", 
                   "Reverse Strings & Count Letters");

  for (i=0; i <= LARGEST; i++) sieve[i] = TRUE;

  compute_primes(sieve);
//Use pumping method of input
  scanf("%d", &value); //prime the pump

  while (value >= 0)
  {
    if (value > LARGEST)
      printf("error, %d is too large\n", value);
    else if (value <= 1)
      printf("%d has no prime divisors\n", value);
    else
    {
      printf("%d has the following prime divisors\n", value);
      current_prime = next_prime(0, sieve);
      while ((current_prime > 0) && (current_prime <= value))
      {
        if ((value % current_prime) == 0)
          printf("\t%d\n", current_prime);
        current_prime = next_prime(current_prime, sieve);  
      }
    }
    scanf("%d", &value);//pump the input
    printf("\n");
  }
                                        
}