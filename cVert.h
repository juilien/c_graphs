#ifndef CVERT_INCLUDED
#define CVERT_INCLUDED

#include "cEdge.h"
#include "cList.h"

typedef struct cVert_s {
  cPointer data;
  cList* edges;
} cVert;

typedef struct cEdge_s {
  cVert*    vertA;
  cVert*    vertB;
  cPointer  value;
  int       orientation;
} cEdge;


cVert* cg_cvert_new_empty(void) {
  cVert* newVert = NULL;
  newVert = (cVert*) calloc(1, sizeof(cVert));
  return newVert;
}

cVert* cg_cvert_new(cPointer data) {
  cVert* newVert = cg_cvert_new_empty();
  newVert->data = data;
  return newVert;
}


cVert* cg_cvert_set_content(cVert* vert, cPointer data) {
  if (vert) vert->data = data;
  else vert = cg_cvert_new(data);
  return vert;
}


cVert* cg_cvert_add_edge(cVert* vert, cEdge* edge) {
  if (!vert) return NULL;
  if (!edge) return vert;
  vert->edges = cg_clist_append_data(vert->edges, edge);
  return vert;
}

void cg_cvert_remove_edge(cVert* vert, cEdge* edge) {
  int (*edge_equal)(cPointer, cPointer) = cg_cedge_compare;
  cg_clist_destoy_current(cg_clist_find_first(vert->edges, edge_equal, edge));
}


void cg_cvert_destroy(cVert* vert) {
  if (vert) {
    cg_clist_destroy(vert->edges);
    free(vert);
  }
}
#endif
