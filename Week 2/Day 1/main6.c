#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[], char * env[])
{
  printf("env[1] = %s\n", env[1]);
}