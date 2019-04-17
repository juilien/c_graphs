#ifndef CVERT_INCLUDED
#define CVERT_INCLUDED
/**
*\file  cVert.h
*\brief Contains basic functions to manage graph vertices.
**/

#include "cEdge.h"
#include "cList.h"

int       cg_cvert_compare(cPointer a, cPointer b) {
  cVert* c = CVERT(a);
  cVert* d = CVERT(b);
  return !(c == d);
}


/**
*\fn cVert* cg_cvert_new_empty(void)
*\brief Create an empty graph vertice.
*\return An empty graph vertice.
**/
cVert*    cg_cvert_new_empty(void) {
  cVert* newVert = NULL;
  newVert = (cVert*) calloc(1, sizeof(cVert));
  return newVert;
}
/**
*\fn cVert* cg_cvert_new(cPointer data)
*\param[in] data A default pointer.
*\brief Create a graph vertice containing (data).
*\return A graph vertice.
**/
cVert*    cg_cvert_new(cPointer data) {
  cVert* newVert = cg_cvert_new_empty();
  newVert->data = data;
  return newVert;
}

/**
*\fn cVert* cg_cvert_set_data(cVert* vert, cPointer data)
*\param[in] vert A graph vertice
*\param[in] data A default pointer
*\brief Modify the content of (vert) with (data). If (vert) is NULL, returns a new graph vertice filled with (data).
*\return A graph vertice.
**/
cVert*    cg_cvert_set_data(cVert* vert, cPointer data) {
  if (vert) vert->data = data;
  else vert = cg_cvert_new(data);
  return vert;
}
/**
*\fn cVert* cg_cvert_get_data(cVert* vert)
*\param[in] vert A graph vertice.
*\brief Get the content of a graph vertice. Returns NULL if the vertice doesn't exist, or if it's empty.
*\return A default pointer.
**/
cPointer  cg_cvert_get_data(cVert* vert) {
  if (!vert) return NULL;
  return vert->data;
}
/**
*\fn cVert* cg_cvert_add_edge(cVert* vert, cEdge* edge)
*\param[in] vert A graph vertice
*\param[in] edge A graph edge
*\brief Add (edge) at the end of the list of edges of (vert). Returns (vert).
*\return A graph vertice.
**/
cVert*    cg_cvert_add_edge(cVert* vert, cEdge* edge) {
  if (!vert) return NULL;
  if (!edge) return vert;
  vert->edges = cg_clist_append_data(vert->edges, edge);
  return vert;
}
/**
*\fn cVert* cg_cvert_remove_edge(cVert* vert, cEdge* edge)
*\param[in] vert A graph vertice.
*\param[in] edge A graph edge.
*\brief Remove (edge) from the list of edges of (vert).
*\return A graph vertice.
**/
cVert*    cg_cvert_remove_edge(cVert* vert, cEdge* edge) {
  if (!vert) return NULL;
  if (!edge) return vert;
  int (*cg_cedge_compare)(cPointer, cPointer) = cg_cedge_compare;
  cg_clist_destroy_current(cg_clist_find_first(vert->edges, cg_cedge_compare, edge));
  return vert;
}

/**
*\func void cg_cvert_destroy(cVert vert)
*\param[in] A graph vertice.
*\brief Destroy a graph vertice and the list of its edges (not edges themselves).
**/
void      cg_cvert_destroy(cVert* vert) {
  if (vert) {
    cg_clist_destroy_full(vert->edges);
    free(vert);
  }
}

#endif
