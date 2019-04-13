#ifndef CLIST_INCLUDED
#define CLIST_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

#define INT_MAX         2147483647
#define SEEK_FORWARD    1
#define SEEK_BACKWARD   1
#define OFFSET_MIN      -1
#define OFFSET_CURRENT  0
#define OFFSET_MAX      1


typedef void* cPointer;

typedef struct cList_s {
    struct cList_s *    previous;
    struct cList_s *    next;
    cPointer          data;
} cList;

cList* cg_list_new_empty(void) {
  cList* newList = NULL;
  newList = (cList*) calloc(1, sizeof(newList));
  return newList;
}

cList* cg_list_new(cPointer data) {
  cList* newList = cg_list_new_empty();
  newList->data = data;
  return newList;
}

cList* cg_list_seek(cList* list, int offset, char dir) {
  if (!list) return NULL;

  cList* currentNode = NULL;

  if (dir > 0)        currentNode = cg_list_seek(list->next, offset - 1, SEEK_FORWARD);
  else if (dir < 0)   currentNode = cg_list_seek(list->previous, offset + 1, SEEK_BACKWARD);

  if (currentNode == NULL || offset == 0) return list;
  else return currentNode;
}

cList* cg_list_prepend_list(cList* list, cList* listToPrepend) {
  if (!listToPrepend) {
    if(!list) return cg_list_new_empty();
    else return list;
  }
  else {
    if (!list) return listToPrepend;
    else {
      list = cg_list_seek(list, INT_MAX, SEEK_BACKWARD);
      listToPrepend = cg_list_seek(listToPrepend, INT_MAX, SEEK_FORWARD);

      list->next = listToPrepend;
      listToPrepend->previous = list;

      list = cg_list_seek(list, INT_MAX, SEEK_BACKWARD);
      return list;
    }
  }
}

cList* cg_list_append_list(cList* list, cList* listToAppend) {
  if (!listToAppend) {
    if(!list) return cg_list_new_empty();
    else return list;
  }
  else {
    if (!list) return listToAppend;
    else {
      list = cg_list_seek(list, INT_MAX, SEEK_FORWARD);
      listToAppend = cg_list_seek(listToAppend, INT_MAX, SEEK_BACKWARD);

      list->next = listToAppend;
      listToAppend->previous = list;

      list = cg_list_seek(list, INT_MAX, SEEK_BACKWARD);
      return list;
    }
  }
}

cList* cg_list_prepend_data(cList* list, cPointer data) {
  cList* newNode = cg_list_new(data);
  if (!list) return newNode;
  else {
    list = cg_list_seek(list, INT_MAX, SEEK_BACKWARD);

    list->previous = newNode;
    newNode->next = list;

    return newNode;
  }
}

cList* cg_list_append_data(cList* list, cPointer data) {
  cList* newNode = cg_list_new(data);
  if (!list) return newNode;
  else {
    list = cg_list_seek(list, INT_MAX, SEEK_FORWARD);

    list->next = newNode;
    newNode->previous = list;

    list = cg_list_seek(list, INT_MAX, SEEK_BACKWARD);
    return list;
  }
}

cList* cg_list_sort_asc(cList* list, int (*sortFunction)(cPointer, cPointer)) {
  return NULL;
}

#endif
