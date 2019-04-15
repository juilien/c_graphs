#ifndef CEDGE_INCLUDED
#define CEDGE_INCLUDED

#include "cVert.h"
#include "cList.h"

int cg_edge_compare(cPointer a, cPointer b) {
  cEdge* c = CEDGE(a);
  cEdge* d = CEDGE(b);
  return (c->vertA == d->vertA && c->vertB == d->vertB && c->value == d->value && c->orientation == d->orientation);
}
#endif
