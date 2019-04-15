#ifndef CLIST_INCLUDED
#define CLIST_INCLUDED

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define INT(u) ((int*) (void*) u)
#define DOUBLE(u) ((double*) (void*) u)
#define FLOAT(u) ((float*) (void*) u)

#define INT_MAX         2147483647
#define SEEK_FORWARD    1
#define SEEK_BACKWARD   -1
#define OFFSET_MIN      -1
#define OFFSET_CURRENT  0
#define OFFSET_MAX      1

typedef void* cPointer;

typedef struct cList_s {
    struct cList_s *    previous;
    struct cList_s *    next;
    cPointer            content;
} cList;

cList*    cg_clist_new_empty(void) {
  cList* newList = NULL;
  newList = (cList*) calloc(1, sizeof(newList));
  return newList;
}

cList*    cg_clist_new(cPointer data) {
  cList* newList = cg_clist_new_empty();
  newList->content = data;
  return newList;
}


cList*    cg_clist_seek(cList* list, unsigned int offset, char dir) {
  if (!list) return NULL;

  cList* currentNode = NULL;

  if (dir > 0)        currentNode = cg_clist_seek(list->next, offset - 1, SEEK_FORWARD);
  else if (dir < 0)   currentNode = cg_clist_seek(list->previous, offset - 1, SEEK_BACKWARD);
  else offset = 0;

  if (currentNode == NULL || offset == 0) return list;
  else return currentNode;
}

int       cg_clist_get_pos(cList* list) {
  if (!list) return -1;
  else return cg_clist_get_pos(list->previous) + 1;
}

cList*    cg_clist_set_pos(cList* list, int pos) {
  int current_pos = cg_clist_get_pos(list);
  list = cg_clist_seek(list, abs(pos - current_pos), pos - current_pos);
  return list;
}

int       cg_clist_get_size(cList* list) {
  if (!list) return -1;
  int i = 1;
  list = cg_clist_seek(list, INT_MAX, SEEK_BACKWARD);
  while((list = list->next)) {
    if (list == NULL) break;
    i++;
  }
  return i;
}


cList*    cg_clist_set_content(cList* list, int pos, cPointer data) {

  if (list) list = cg_clist_set_pos(list, pos);
  else list =  cg_clist_new_empty();
  list->content = data;
  return list;
}

cPointer  cg_clist_get_content(cList* list, int pos) {
  if (!list) return NULL;
  if (pos > 0) list = cg_clist_seek(list, pos, SEEK_FORWARD);
  if (pos < 0) list = cg_clist_seek(list, -pos, SEEK_BACKWARD);
  return list->content;
}


cList*    cg_clist_prepend_data(cList* list, cPointer data) {
  cList* newNode = cg_clist_new(data);
  if (!list) return newNode;
  else {
    list = cg_clist_seek(list, INT_MAX, SEEK_BACKWARD);

    list->previous = newNode;
    newNode->next = list;

    return newNode;
  }
}

cList*    cg_clist_append_data(cList* list, cPointer data) {
  cList* newNode = cg_clist_new(data);
  if (!list) return newNode;
  else {
    list = cg_clist_seek(list, INT_MAX, SEEK_FORWARD);

    list->next = newNode;
    newNode->previous = list;

    list = cg_clist_seek(list, INT_MAX, SEEK_BACKWARD);
    return list;
  }
}

cList*    cg_clist_prepend_clist(cList* list, cList* listToPrepend) {
  if (!listToPrepend) {
    if(!list) return cg_clist_new_empty();
    else return list;
  }
  else {
    if (!list) return listToPrepend;
    else {
      list = cg_clist_seek(list, INT_MAX, SEEK_BACKWARD);
      listToPrepend = cg_clist_seek(listToPrepend, INT_MAX, SEEK_FORWARD);

      list->next = listToPrepend;
      listToPrepend->previous = list;

      list = cg_clist_seek(list, INT_MAX, SEEK_BACKWARD);
      return list;
    }
  }
}

cList*    cg_clist_append_clist(cList* list, cList* listToAppend) {
  if (!listToAppend) {
    if(!list) return cg_clist_new_empty();
    else return list;
  }
  else {
    if (!list) return listToAppend;
    else {
      list = cg_clist_seek(list, INT_MAX, SEEK_FORWARD);
      listToAppend = cg_clist_seek(listToAppend, INT_MAX, SEEK_BACKWARD);

      list->next = listToAppend;
      listToAppend->previous = list;

      list = cg_clist_seek(list, INT_MAX, SEEK_BACKWARD);
      return list;
    }
  }
}

cList*    cg_clist_insert_data(cList* list, int pos, cPointer data) {
  cList* newNode = cg_clist_new(data);
  list = cg_clist_set_pos(list, pos);

  newNode->previous = list->previous;
  newNode->next = list;

  return newNode;
}

cList*    cg_clist_insert_clist(cList* list, int pos, cList* listToInsert) {
  list = cg_clist_set_pos(list, pos);
  listToInsert = cg_clist_set_pos(list, 0);

  cList* tmp = list->next;
  list->next = listToInsert;
  list = cg_clist_seek(list, INT_MAX, SEEK_FORWARD);
  list->next = tmp;

  return list;
}


cList*    cg_clist_sort_asc(cList* list, int (*sortFunction)(cPointer, cPointer)) {
  /* Loop variables */
  int i, j;

  /* Temp variable */
  cList* tmp;

  int list_length = cg_clist_get_size(list);
  for (i = list_length - 1; i > 0; i--) {
    list = cg_clist_seek(list, INT_MAX, SEEK_BACKWARD);
    for (j = 0; j < i; j++) {
      if ((*sortFunction)(list->next->content, list->content) > 0) {
        tmp = list->next->content;
        list->next->content = list->content;
        list->content = tmp;
      }
      list = list->next;
    }
  }
  return list;
}

cList*    cg_clist_sort_desc(cList* list, int (*sortFunction)(cPointer, cPointer)) {
  /* Loop variables */
  int i, j;

  /* Temp variable */
  cList* tmp;

  int list_length = cg_clist_get_size(list);
  for (i = list_length - 1; i > 0; i--) {
    list = cg_clist_seek(list, INT_MAX, SEEK_BACKWARD);
    for (j = 0; j < i; j++) {
      if ((*sortFunction)(list->next->content, list->content) < 0) {
        tmp = list->next->content;
        list->next->content = list->content;
        list->content = tmp;
      }
      list = list->next;
    }
  }
  return list;
}

//TODO
cList*    cg_clist_find(cList* list, int (*searchFunction)(cPointer, cPointer), cPointer data) {

}


void      cg_clist_destroy(cList* list) {
  if (list) {
    if (list->previous) list->previous->next = NULL;
    cg_clist_destroy(list->next);
    free(list);
  }
}

void      cg_clist_destoy_current(cList* list) {
  if (list) {
    if (list->previous) list->previous->next = NULL;
    if (list->next) list->next->previous = NULL;
    free(list);
  }
}
#endif
