#ifndef CGRAPH_INCLUDED
#define CGRAPH_INCLUDED

#include "cEdge.h"
#include "cVert.h"
#include "cList.h"

/**
* \file cGraph.h
* \brief Graph library main file
* \author Gabriel JUILIEN
**/

typedef struct cGraph_s {
  cList* vertices;
  cList* edges;
}cGraph;

cGraph*   cg_cgraph_new_empty(void) {
  return (cGraph*) calloc(1, sizeof(cGraph));
}

cGraph*   cg_cgraph_fill(cGraph* graph, cList* vertices, cList* edges) {
  if (!graph) graph = cg_cgraph_new_empty();
  graph->vertices = vertices;
  graph->edges = edges;
  return graph;
}

cGraph*   cg_cgraph_cvert_add(cGraph* graph, cVert* vertice) {
  if (!graph) return NULL;
  graph->vertices = cg_clist_append_data(graph->vertices, vertice);
  return graph;
}

cGraph*   cg_cgraph_cvert_remove(cGraph* graph, cVert* vertice) {
  if (!graph) return NULL;
  cg_cvert_destroy(vertice);
  cg_clist_destroy_current(cg_clist_find_first(graph->vertices, (*cg_cvert_compare), vertice));
  return graph;
}

cGraph*   cg_cgraph_cedge_add(cGraph* graph, cEdge* edge) {
  if (!graph) return NULL;
  graph->edges = cg_clist_append_data(graph->edges, edge);
  return graph;
}

cGraph*   cg_cgraph_cedge_remove(cGraph* graph, cEdge* edge) {
  if (!graph) return NULL;
  cg_cedge_destroy(edge);
  cg_clist_destroy_current(cg_clist_find_first(graph->edges, (*cg_cedge_compare), edge));
  return graph;
}
#endif
