#ifndef CEDGE_INCLUDED
#define CEDGE_INCLUDED

#include "cVert.h"

typedef struct cEdge_s {
  cVert*  vertA;
  cVert*  vertB;
  cPointer  value;
  int       orientation;
} cEdge;

#endif
