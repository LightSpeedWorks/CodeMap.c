
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char**argv, char **envp)
{
  printf("char   %d\n", sizeof(char));
  printf("short  %d\n", sizeof(short));
  printf("int    %d\n", sizeof(int));
  printf("long   %d\n", sizeof(long));
  printf("float  %d\n", sizeof(float));
  printf("double %d\n", sizeof(double));
}

