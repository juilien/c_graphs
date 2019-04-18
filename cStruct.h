#ifndef CSTRUCT_INCLUDED
#define CSTRUCT_INCLUDED

typedef void* cPointer;

/**
*\struct cList cStruct.h
*\brief A basic double-chained list node definition, with a default pointer for datas.
**/
typedef struct cList_s {
  struct cList_s *    previous;
  struct cList_s *    next;
  cPointer            content;
} cList;

/**
*\struct cVert_s cStruct.h
*\brief A basic vertice structure. Contains a field ofr datas, and a list of related edges.
**/
typedef struct cVert_s {
  cPointer  data;
  cList*    edges;
} cVert;

/**
*\struct cEdge cStruct.h
*\brief A basic edge definition, with two fields for linked vertices, a default pointer for datas, and an interger for orientation :
*  1 : A-->B
*  0 : A<->B
* -1 : A<--B
**/
typedef struct cEdge_s {
  cVert*    vertA;
  cVert*    vertB;
  cPointer  value;
  int       orientation;
} cEdge;

/**
*\struct cGraph cStruct.h
*\brief A basic graph definition, containg two lists for edges and vertices.
**/
typedef struct cGraph_s {
  cList* vertices;
  cList* edges;
}cGraph;

#endif
