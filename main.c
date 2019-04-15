#include <stdio.h>

#include "cGraph.h"

int main(int argc, char** argv) {
  cList* newList = NULL;
  int data1 = 8;
  int data2 = 6;
  int data3 = 20;
  newList = cg_clist_new(&data1);
  printf("pos %d : %p : %d\n", cg_clist_get_pos(newList), newList, *(INT(newList->content)));

  newList = cg_clist_append_data(newList, &data2);
  printf("pos %d : %p : %d\n", cg_clist_get_pos(newList), newList, *(INT(newList->content)));

  

  return 0;
}
