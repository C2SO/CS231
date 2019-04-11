#include <stdio.h>
#include <unistd.h>

extern char ** environ;
int main(int argc, char * argv[])
{
  printf("*environ = %s\n", *environ);
}