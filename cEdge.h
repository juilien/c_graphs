#ifndef CEDGE_INCLUDED
#define CEDGE_INCLUDED

#include "cLibs.h"
#include "cList.h"

/**
*\fn int cg_edge_compare(cPointer a, cPointer b)
*\param[in] a A graph edge.
*\param[in] b A graph edge.
*\brief Takes two edges. Returns 0 if they are the same, 1 otherwise.
*\return A integer.
**/
int       cg_cedge_compare(cPointer a, cPointer b) {
  cEdge* c = CEDGE(a);
  cEdge* d = CEDGE(b);
  return !(c == d);
}

/**
*\fn cEdge* cg_cedge_new_empty(void)
*\brief Creates a grapĥ edge with all fields blank, and returns it.
*\return A graph edge.
**/
cEdge*    cg_cedge_new_empty(void) {
  cEdge* newEdge = (cEdge*) calloc(1, sizeof(cEdge));
  return newEdge;
}
/**
*\fn cEdge* cg_cedge_new(cVert* vertA, cVert* vertB, cPointer data, int orientation)
*\param[in] vertA A graph vertice.
*\param[in] vertB A graph vertice.
*\param[in] data A default pointer.
*\param[in] orientation An integer.
*\brief Creates a new edge between vertices A and B (The edge isn't added to vertices' edges list), filled with (data) and returns it.
*\return A graph edge.
**/
cEdge*    cg_cedge_new(cVert* vertA, cVert* vertB, cPointer data, int orientation) {
  cEdge* newEdge = cg_cedge_new_empty();
  newEdge->vertA = vertA;
  newEdge->vertB = vertB;
  newEdge->value = data;
  newEdge->orientation = orientation;
  return newEdge;
}

/**
*\fn void cg_cedge_set_vertA(cEdge* edge, cVert* vert)
*\param[in] edge A graph edge.
*\param[in] vert A graph vertice.
*\brief If edge exists, set its vertA field to (vert).
**/
void      cg_cedge_set_vertA(cEdge* edge, cVert* vert) {
  if (!edge) return;
  edge->vertA = vert;
}

cVert*    cg_cedge_get_vertA(cEdge* edge) {
  if (!edge) return NULL;
  return edge->vertA;
}
/**
*\fn void cg_cedge_set_vertB(cEdge* edge, cVert* vert)
*\param[in] edge A graph edge.
*\param[in] vert A graph vertice.
*\brief If edge exists, set its vertB field to (vert).
**/
void      cg_cedge_set_vertB(cEdge* edge, cVert* vert) {
  if (!edge) return;
  edge->vertB = vert;
}

cVert*    cg_cedge_get_vertB(cEdge* edge) {
  if (!edge) return NULL;
  return edge->vertB;
}
/**
*\fn void cg_cedge_set_value(cEdge* edge, cPointer data)
*\param[in] edge A graph edge.
*\param[in] vert A graph vertice.
*\brief If edge exists, set its value field to (value).
**/
void      cg_cedge_set_value(cEdge* edge, cPointer data) {
  if (!edge) return;
  edge->value = data;
}

cPointer  cg_cedge_get_value(cEdge* edge) {
  if (!edge) return NULL;
  return edge->value;
}
/**
*\fn void cg_cedge_set_orientation(cEdge* edge, int orientation)
*\param[in] edge A graph edge.
*\param[in] vert A graph vertice.
*\brief If edge exists, set its orientation field to (orientation).
**/
void      cg_cedge_set_orientation(cEdge* edge, int orientation) {
  if (!edge) return;

  if (orientation > 0) edge->orientation = ASC_ORIENTATION;
  else if(orientation < 0) edge->orientation = DES_ORIENTATION;
  else edge->orientation = EQU_ORIENTATION;
}

int       cg_cedge_get_orientation(cEdge* edge) {
  if (!edge) return ERR_ORIENTATION;

  if (edge->orientation > 0) return ASC_ORIENTATION;
  else if(edge->orientation < 0) return DES_ORIENTATION;
  else return EQU_ORIENTATION;
}


void      cg_cedge_destroy(cEdge* edge) {
  if (edge) {
    free(edge);
  }
}

#endif
