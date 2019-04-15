#include <stdio.h>

#include "cGraph.h"

int compare(cPointer a, cPointer b) {
  int c = *(INT(a));
  int d = *(INT(b));
  if (c > d) return -1;
  else if (c < d) return 1;
  else return 0;
}

int main(int argc, char** argv) {
  cList* newList = NULL;
  int data1 = 8;
  int data2 = 16;
  int data3 = 32;
  int data4 = 4;
  newList = cg_clist_new(&data1);
  newList = cg_clist_append_data(newList, &data2);
  newList = cg_clist_append_data(newList, &data3);
  newList = cg_clist_prepend_data(newList, &data4);

  newList = cg_clist_set_pos(newList, 0);
  printf("pos %d : %p : %d\n", cg_clist_get_pos(newList), newList, *(INT(newList->content)));
  newList = cg_clist_set_pos(newList, 1);
  printf("pos %d : %p : %d\n", cg_clist_get_pos(newList), newList, *(INT(newList->content)));
  newList = cg_clist_set_pos(newList, 2);
  printf("pos %d : %p : %d\n", cg_clist_get_pos(newList), newList, *(INT(newList->content)));
  newList = cg_clist_set_pos(newList, 3);
  printf("pos %d : %p : %d\n", cg_clist_get_pos(newList), newList, *(INT(newList->content)));
  
  return 0;
}
