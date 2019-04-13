#include <stdio.h>

#include "cGraph.h"

int main(int argc, char** argv) {
  cList* newList = NULL;
  printf("%p\n", newList);

  int data1 = 1;
  newList = cg_clist_new(&data1);
  


  return 0;
}
