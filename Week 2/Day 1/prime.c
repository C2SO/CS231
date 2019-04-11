/*  Dr. Vineyard
    CPSC 231 all sections
    Example program - finding prime divisors
    Complete example, show #define; relation between pointers and arrays
*/

/*  The purpose of this program is to input non-negative integers
    less than or equal to the predefined constant LARGEST.  For each
    input integer, determine the prime numbers which are also divisors
    of the integer.  The output will consist of the input integer and
    a list of its prime divisors.
    
    The program algorithm is:
    
    Compute all prime numbers less than or equal to LARGEST.
    Loop for non-negative input values:
      If value is negative, end program
      If value is larger than LARGEST, print error message
      If value is in range 0 to LARGEST
        print value
        for each prime number less than or equal to LARGEST
          if the prime number divides value, print the prime number.
          
The external data table 
NAME              DESCRIPTION 

LARGEST           the largest input allowed for this program. 
TRUE              1 is true in C
FALSE             0 is false in C 

          
*/
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define LARGEST 1000


void print_title_author(char * title, char * proginfo)
{
/*
    print_title_author will print the title of the output
    and it will also print the author information, including
    some program information.
    
data table

NAME               DESCRIPTION
title              parameter - the title of the output.
proginfo           parameter - identifies programming task.

*/ 
    
  printf("\t\t%s\n\n", title);
  printf("\t\tDr. Vineyard\n\t\tCPSC231 all sections\n\t\t%s\n\n", proginfo);
}

void compute_primes(int * sieve)  //Note, an array of int was passed into this function
{
/*
  compute_primes uses as its method the sieve of Eratosthenes.
  The integers are marked as all prime (value of TRUE for associated
  array value indexed by integer), then integers 0 and 1 are marked
  as non-prime (set to FALSE).  Then beginning at value = 2, if value is
  prime, mark all integer multiples of value as non-prime.  Repeat the
  process for all primes from 2 to largest value in array.
  
data table

NAME             DESCRIPTION

sieve            array showing primality of index value.
                 value of TRUE is prime, FALSE is non-prime
next_prime       index on sieve, used to find next smallest prime
next_multiple    index on sieve, used to set multiples of primes to FALSE                 
*/

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
/*
    next_prime uses its input parameter prime as an index into
    the sieve and returns the next larger prime if one exists.
    If there is no next larger prime, next_prime returns -1; 
    
data table

NAME            DESCRIPTION
prime           input parameter, lower bound for returned prime
sieve           input array denoting primes.
*/

  prime++;
  while (prime <= LARGEST)
  {
    if (*(sieve + prime)) return prime;
    prime++;
  }
  return -1;
}

int main(void)
{
/*  main is the controlling function of the program.
    main will initialize all slots in the array sieve to  TRUE, then
    call the procedure compute_primes to place a FALSE in each
    array element of sieve which is not indexed by a prime.
    
    main will then loop for input until the input value is negative.
    If the input is non-negative, main will print the value, and
    if the input is too large, print an error message, else
    main will repeatedly call the function next_prime and check 
    if that prime divides the input value.
    If the prime divides the input value, then main will print
    the prime.
    
main data table

NAME                DESCRIPTION
sieve               integer array of LARGEST + 1 items, 
                    sieve[i] == FALSE if i non-prime, sieve[i] == TRUE if i prime
value               input integer
current_prime       the variable for determining if the prime divides value
                    current_prime == -1 if no more primes exist in sieve
                    
*/

  int sieve[LARGEST + 1]; //Notice: this is an array of int
  int current_prime;
  int value;
  int i;

  print_title_author("Prime Factorization", 
                   "Example program - finding prime divisors");

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
