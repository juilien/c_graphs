#ifndef CVERT_INCLUDED
#define CVERT_INCLUDED

#include "cList.h"

typedef struct cVert_s {
  cPointer data;
  cList* edges;
} cVert;

#endif
