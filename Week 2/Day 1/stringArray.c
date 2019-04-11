//Subtle problems with dealing with arrays of strings
#include <stdio.h>
#include <string.h>

int main()
{
  char str[10][5];//10 strings, 5 chars each
  int pos=0;
  int rdflag;
  rdflag=1;
  while (rdflag)
  {
    rdflag = scanf("%s",str[pos]);
    if (rdflag != EOF) pos++;
    else rdflag = 0;
  }
  for (rdflag = 0; rdflag <= pos; rdflag++) printf("%s\n",str[rdflag]);
}
