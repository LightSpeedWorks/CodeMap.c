
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codemap.h"

/*
******************************************************************************************
main
メイン
******************************************************************************************
*/
int main (int argc, char**argv, char **envp)
{
  CodeMap cmap;
  int i;

  printf("char   %d\n", sizeof(char));
  printf("short  %d\n", sizeof(short));
  printf("int    %d\n", sizeof(int));
  printf("long   %d\n", sizeof(long));
  printf("float  %d\n", sizeof(float));
  printf("double %d\n", sizeof(double));
  printf("\n");

  CodeMap_showCount();

  cmap = CodeMap_create();
  CodeMap_showCount();

  printf("main cm 0 = %d\n", CodeMap_get(cmap, 0));
  CodeMap_set(cmap, 0, 0);
  CodeMap_showCount();
  printf("main cm 0 = %d\n", CodeMap_get(cmap, 0));
  printf("\n");

  printf("main cm 1 = %d\n", CodeMap_get(cmap, 1));
  CodeMap_set(cmap, 1, 0);
  CodeMap_showCount();
  printf("main cm 1 = %d\n", CodeMap_get(cmap, 1));
  printf("\n");

  printf("main cm 100 = %d\n", CodeMap_get(cmap, 0x100));
  CodeMap_set(cmap, 0x100, 0);
  CodeMap_showCount();
  printf("main cm 100 = %d\n", CodeMap_get(cmap, 0x100));
  printf("\n");

  for (i = 0; i < 0x10000; ++i) {
    CodeMap_set(cmap, i, i);
  }
  CodeMap_showCount();

  CodeMap_delete(cmap);
  CodeMap_showCount();
}

