#ifndef CGRAPH_INCLUDED
#define CGRAPH_INCLUDED

/**
* \file cGraph.h
* \brief Graph library main file
* \author Gabriel JUILIEN
**/

#include "cLibs.h"

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
  if (!vertice) return graph;
  graph->vertices = cg_clist_append_data(graph->vertices, vertice);
  return graph;
}

cGraph*   cg_cgraph_cvert_remove(cGraph* graph, cVert* vertice) {
  if (!graph) return NULL;
  if (!vertice) return graph;
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


cGraph*   cg_cgraph_cverts_link(cGraph* graph, cVert* vertA, cVert* vertB, cPointer edgeData, int edgeOrientation) {
  if (!graph) return NULL;
  if (!vertA || !vertB) return graph;
  cEdge* newEdge = cg_cedge_new_empty();
  cg_cedge_set_value(newEdge, edgeData);
  cg_cedge_set_vertA(newEdge, vertA);
  cg_cedge_set_vertB(newEdge, vertB);
  if (edgeOrientation > 0) cg_cedge_set_orientation(newEdge, ASC_ORIENTATION);
  else if (edgeOrientation < 0) cg_cedge_set_orientation(newEdge, DES_ORIENTATION);
  else cg_cedge_set_orientation(newEdge, EQU_ORIENTATION);
  cg_cvert_add_edge(vertA, newEdge);
  cg_cvert_add_edge(vertB, newEdge);
  return graph;
}


cList*    cg_cgraph_cvert_find_linked(cGraph* graph, cVert* vertice) {
  cList* linkedVertices = NULL;
  cList* edges = cg_clist_set_pos(graph->edges, 0);
  while (edges) {
    if (CEDGE(edges->content)->vertA == vertice && CEDGE(edges->content)->orientation >= 0)
      cg_clist_append_data(linkedVertices, CEDGE(edges->content)->vertB);
    else if (CEDGE(edges->content)->vertB == vertice && CEDGE(edges->content)->orientation <= 0)
      cg_clist_append_data(linkedVertices, CEDGE(edges->content)->vertA);
  }
  return linkedVertices;
}

cList*    cg_cgraph_check_edges(cGraph* graph, bool autoremove) {
  cList* edges = cg_clist_set_pos(graph->edges, 0);
  cList* vertices = cg_clist_set_pos(graph->vertices, 0);
  cList* mistaken_edges = NULL;
  while (edges != NULL) {
    if (cg_clist_find_first(vertices, (*cg_cvert_compare), CEDGE(edges->content)->vertA) || cg_clist_find_first(vertices, (*cg_cvert_compare), CEDGE(edges->content)->vertB)) {
      if (autoremove == FALSE) {
        cg_clist_append_data(mistaken_edges, edges);
        edges = edges->next;
      }
      else {
        cg_clist_destroy_current(edges);
      }
    }
    else edges = edges->next;
  }
  return mistaken_edges;
}


#endif
