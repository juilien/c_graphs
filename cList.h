#ifndef CLIST_INCLUDED
#define CLIST_INCLUDED

/**
*\file  cList.h
*\brief Contains basic functions to manage double-chained lists.
*
**/

#include "cLibs.h"




/**
*\fn cList* cg_clist_new_empty(void)
*\brief Create an empty list node.
*\return Returns an empty list node.
**/
cList*    cg_clist_new_empty(void) {
  cList* newList = NULL;
  newList = (cList*) calloc(1, sizeof(cList));
  return newList;
}
/**
*\fn cList* cg_clist_new(cPointer data)
*\param[in] data A default pointer.
*\brief Creates a list node filled with the input data. If data is empty, will return the same as cg_clist_new_empty.
*\return A list node.
**/
cList*    cg_clist_new(cPointer data) {
  cList* newList = cg_clist_new_empty();
  newList->content = data;
  return newList;
}

/**
*\fn cList* cg_clist_seek(cList* list, unsigned int offset, char dir)
*\param[in] list A list.
*\param[in] offset A unsigned int.
*\param[in] dir A char
*\brief Seeks of (offset) nodes in (list). The direction depends of the (dir) parameter :
*   - Forward if (dir) > 0
*   - Backward if (dir) < 0
*   - Doesn't seek if (dir) = 0.
*If (offset) is higher than possible offset, will return the first or the last node, corresponding to (dir).
*\return A list node
**/
cList*    cg_clist_seek(cList* list, unsigned int offset, char dir) {
  if (!list) return NULL;

  cList* currentNode = NULL;

  if (dir > 0)        currentNode = cg_clist_seek(list->next, offset - 1, SEEK_FORWARD);
  else if (dir < 0)   currentNode = cg_clist_seek(list->previous, offset - 1, SEEK_BACKWARD);
  else offset = 0;

  if (currentNode == NULL || offset == 0) return list;
  else return currentNode;
}
/**
*\fn int cg_clist_get_pos(cList* list)
*\param[in] list The node in the list to get the position from
*\brief Returns the position of the input node in its list. If (list) is NULL, wille return -1.
*\return int An integer.
**/
int       cg_clist_get_pos(cList* list) {
  if (!list) return -1;
  else return cg_clist_get_pos(list->previous) + 1;
}
/**
*\fn cList* cg_clist_set_pos(cList* list, int pos)
*\param[in] list A list.
*\param[in] pos An integer.
*\brief Returns a pointer on the list node located at (pos) int the list. If (pos) is higher/lower than possible positions, will return the last/first node of the list.
*\return A list node.
**/
cList*    cg_clist_set_pos(cList* list, int pos) {
  int current_pos = cg_clist_get_pos(list);
  list = cg_clist_seek(list, abs(pos - current_pos), pos - current_pos);
  return list;
}
/**
*\fn int cg_clist_get_size(cList* list)
*\param[in] list A list.
*\brief Returns the total length of a list, not depending of the begin position in this list. If (list) is NULL, returns -1.
*\return An integer.
**/
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

/**
*\fn cList* cg_clist_prepend_data(cList* list, cPointer data)
*\param[in] list A list
*\param[in] data A default pointer.
*\brief Create a new node at the beginning of the list filled with data. Creates a new list if (list) is NULL.
*\return A list node.
**/
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
/**
*\fn cList* cg_clist_append_data(cList* list, cPointer data)
*\param[in] list A list
*\param[in] data A default pointer.
*\brief Create a new node at the end of the list filled with data. Creates a new list if (list) is NULL.
*\return A list node.
**/
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
/**
*\fn cList* cg_clist_prepend_clist(cList* list, cList* listToPrepend)
*\param[in] list A list.
*\param[in] listToPrepend A list.
*\brief Merges (listToPrepend) at the beginning of (list). Returns the beginning of the new list. If one of those is empty, will return the other. Returns NULL if both are empty.
*\return A list node.
**/
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
/**
*\fn cList* cg_clist_append_clist(cList* list, cList* listToAppend)
*\param[in] list A list.
*\param[in] listToPrepend A list.
*\brief Merges (listToPrepend) at the end of (list). Returns the beginning of the new list. If one of those is empty, will return the other. Returns NULL if both are empty.
*\return A list node.
**/
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
/**
*\fn cList* cg_clist_set_content(cList* list, int pos, cPointer data)
*\param[in] list A list
*\param[in] pos An integer
*\param[in] data A default pointer
*\brief Modify the content of the node located at (pos). Return a pointer on it. If (pos) is higher/lower than the possible offset, will act the same as cg_clist_append_data/cg_clist_prepend_data.
*\return A list node
**/
cList*    cg_clist_set_content(cList* list, int pos, cPointer data) {
  if (!list) list =  cg_clist_new_empty();
  else if (pos > cg_clist_get_size(list)) list = cg_clist_append_data(list, data);
  else if (pos < 0) list = cg_clist_prepend_data(list, data);
  else list = cg_clist_set_pos(list, pos);

  list->content = data;
  return list;
}
/**
*\fn cPointer cg_clist_get_content(cList* list, int pos)
*\param[in] list A list.
*\param[in] pos An integer.
*\brief Return a pointer on the content of the list node located at position (pos). If (pos) is higher/lower than the possible offset, will return the content of the last/first node.
*\return A default pointer.
**/
cPointer  cg_clist_get_content(cList* list, int pos) {
  if (!list) return NULL;
  if (pos > 0) list = cg_clist_seek(list, pos, SEEK_FORWARD);
  if (pos < 0) list = cg_clist_seek(list, -pos, SEEK_BACKWARD);
  return list->content;
}
/**
*\fn cList* cg_clist_insert_data(cList* list, int pos, cPointer data)
*\param[in] list A list.
*\param[in] pos An integer.
*\param[in] data A default pointer.
*\brief Inserts a new node at (pos) filled with (data) and returns a pointer on it. If (pos) is higher/lower than possible positions, will act the same as cg_clist_append_data/cg_clist_prepend_data
*\return A list node.
**/
cList*    cg_clist_insert_data(cList* list, int pos, cPointer data) {
  cList* newNode = cg_clist_new(data);
  list = cg_clist_set_pos(list, pos);

  newNode->previous = list->previous;
  newNode->next = list;

  return newNode;
}
/**
*\fn cList* cg_clist_insert_clist(cList* list, int pos, cList* listToInsert)
*\param[in] list A list.
*\param[in] pos An integer.
*\param[in] listToInsert A list.
*\brief Inserts (listToInsert) between (pos - 1) and (pos) in (list) and returns a pointer on it. If (pos) is higher/lower than possible positions, will act the same as cg_clist_append_clist/cg_clist_prepend_clist.s
*\return A list node.
**/
cList*    cg_clist_insert_clist(cList* list, int pos, cList* listToInsert) {
  list = cg_clist_set_pos(list, pos - 1);
  listToInsert = cg_clist_set_pos(list, 0);

  cList* tmp = list->next;
  list->next = listToInsert;
  list = cg_clist_seek(list, INT_MAX, SEEK_FORWARD);
  list->next = tmp;
  list->next->previous = list;

  return list;
}

/**
*\fn cList* cg_clist_copy(cList* list)
*\param[in] list A list.
*\brief Create a new list node which points on the same content as (list). Return NULL if (list) is NULL.
*\return A list node.
**/
cList*    cg_clist_copy(cList* list) {
  if (!list) return NULL;
  else return cg_clist_new(list->content);
}
/**
*\fn cList* cg_clist_copy_full(cList* list)
*\param[in] list A list node.
*\brief Creates a full copy of (list) which has the same content and returns its first node. Return NULL if (list) is NULL.
*\return A list node.
**/
cList*    cg_clist_copy_full(cList* list) {
  if (!list) return NULL;
  list = cg_clist_set_pos(list, 0);
  cList* copyList;
  while (list) {
    copyList = cg_clist_append_clist(copyList, cg_clist_copy(list));
    list = list->next;
  }
  return copyList;
}

/**
*\fn cList* cg_clist_sort_asc(cList* list, int (*compareFunction)(cPointer, cPointer))
*\param[in] list A list.
*\param[in] (*compareFunction) A comparison function (More details following).
*\brief Takes a list as entry. Sort the list depending its content. The parameter to use must be given by (*compareFunction), which must return an integer :
* -   > 0 if the node with the lowest value must be placed before the second.
* -   < 0 if the node with the lowest value must be placed after the second.
* -   = 0 if nodes should keep the same order.
* Returns the beginning of the sorted list.
* Returns NULL if (list) is empty.
*\return A list node.
**/
cList*    cg_clist_sort_asc(cList* list, int (*compareFunction)(cPointer, cPointer)) {
  if (!list) return NULL;
  /* Loop variables */
  int i, j;

  /* Temp variable */
  cList* tmp;

  int list_length = cg_clist_get_size(list);
  for (i = list_length - 1; i > 0; i--) {
    list = cg_clist_seek(list, INT_MAX, SEEK_BACKWARD);
    for (j = 0; j < i; j++) {
      if ((*compareFunction)(list->next->content, list->content) > 0) {
        tmp = list->next->content;
        list->next->content = list->content;
        list->content = tmp;
      }
      list = list->next;
    }
  }
  list = cg_clist_set_pos(list, 0);
  return list;
}
/**
*\fn cList* cg_clist_sort_desc(cList* list, int (*compareFunction)(cPointer, cPointer))
*\param[in] list A list.
*\param[in] (*compareFunction) A comparison function (More details following).
*\brief Takes a list as entry. Sort the list depending its content. The parameter to use must be given by (*compareFunction), which must return an integer :
* -   > 0 if the node with the lowest value must be placed after the second.
* -   < 0 if the node with the lowest value must be placed before the second.
* -   = 0 if nodes should keep the same order.
* Returns the beginning of the sorted list.
* Returns NULL if (list) is empty.
*\return A list node.
**/
cList*    cg_clist_sort_desc(cList* list, int (*compareFunction)(cPointer, cPointer)) {
  if (!list) return NULL;
  /* Loop variables */
  int i, j;

  /* Temp variable */
  cList* tmp;

  int list_length = cg_clist_get_size(list);
  for (i = list_length - 1; i > 0; i--) {
    list = cg_clist_seek(list, INT_MAX, SEEK_BACKWARD);
    for (j = 0; j < i; j++) {
      if ((*compareFunction)(list->next->content, list->content) < 0) {
        tmp = list->next->content;
        list->next->content = list->content;
        list->content = tmp;
      }
      list = list->next;
    }
  }
  list = cg_clist_set_pos(list, 0);
  return list;
}
/**
*\fn cList* cg_clist_find_first(cList* list, int (*searchFunction)(cPointer, cPointer), cPointer data)
*\param[in] list A list.
*\param[in] (*searchFunction) A research function (More details following).
*\param[in] data A default pointer.
*\brief Returns the list node that contains the first occurence of (data) in the list. The (*searchFunction) must return 0 if the node's content matches to (data). Returns NULL if (list) is NULL, or if no matches were found.
*\return A list node.
**/
cList*    cg_clist_find_first(cList* list, int (*searchFunction)(cPointer, cPointer), cPointer data) {
  if (!list) return NULL;

  list = cg_clist_set_pos(list, 0);

  while (list) {
    if ((*searchFunction)(list->content, data) == 1) return list;
    list =list->next;
  }
  return NULL;
}
/**
*\fn cList* cg_clist_find_last(cList* list, int (*searchFunction)(cPointer, cPointer), cPointer data)
*\param[in] list A list.
*\param[in] (*searchFunction) A research function (More details following).
*\param[in] data A default pointer.
*\brief Returns the list node that contains the first occurence of (data) in the list. The (*searchFunction) must return 0 if the node's content matches to (data). Returns NULL if (list) is NULL, or if no matches were found.
*\return A list node.
**/
cList*    cg_clist_find_last(cList* list, int (*searchFunction)(cPointer, cPointer), cPointer data) {
  if (!list) return NULL;

  list = cg_clist_set_pos(list, INT_MAX);

  while (list) {
    if ((*searchFunction)(list->content, data) == 1) return list;
    list = list->previous;
  }
  return NULL;
}
/**
*\fn cList* cg_clist_find_all(cList* list, int (*searchFunction)(cPointer, cPointer), cPointer data)
*\param[in] list A list.
*\param[in] (*searchFunction) A research function (More details following).
*\param[in] data A default pointer.
*\brief Returns the list node that contains all the nodes which match with (data) in the list. The (*searchFunction) must return 0 if the node's content matches to (data). Returns NULL if (list) is NULL, or if no matches were found.
*WARNING : The new list's content field is filled with list nodes, not with their datas.
*\return A list node.
**/
cList*    cg_clist_find_all(cList* list, int (*searchFunction)(cPointer, cPointer), cPointer data) {
  if (!list) return NULL;
  cList* occurencesList = NULL;
  cList* buffer = NULL;

  list = cg_clist_set_pos(list, 0);

  do {
    buffer = cg_clist_find_first(list, (*searchFunction), data);

    if (buffer) occurencesList = cg_clist_append_data(occurencesList, buffer);
    list = list->next;
  } while(buffer);
  return occurencesList;
}

/**
*\fn void cg_clist_destroy(cList* list)
*\param[in] list A list node.
*\brief Will destroy the list from current position in the list to the end.
*WARNING : cg_clist_destoy doesn't destroy the content of the list.
**/
void      cg_clist_destroy(cList* list) {
  if (list) {
    if (list->previous) list->previous->next = NULL;
    cg_clist_destroy(list->next);
    free(list);
  }
}
/**
*\fn void cg_clist_destroy_full(cList* list)
*\param[in] list A list node.
*\brief Will destroy the whole list, not depending of the position on (list) in the list.
*WARNING : cg_clist_destoy doesn't destroy the content of the list.
**/
void      cg_clist_destroy_full(cList* list) {
  if (list) {
    list = cg_clist_set_pos(list, 0);
    cg_clist_destroy(list);
  }
}
/**
*\fn void cg_clist_destroy_current(cList* list)
*\param[in] list A list node.
*\brief Will destroy the list node and preserves links.
*WARNING : cg_clist_destoy doesn't destroy the content of the list node.
**/
void      cg_clist_destroy_current(cList* list) {
  if (list) {
    if (list->previous) list->previous->next = list->next;
    if (list->next) list->next->previous = list->previous;
    free(list);
  }
}

#endif
