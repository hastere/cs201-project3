#ifndef BINHEAP_H
#define BINHEAP_H

#include "node.h"
#include "dll.h"

typedef struct bnh {
  int (*comparator)(void *,void *);
  void (* swapper)(node *, node *);
  struct dll *doubly;
  struct node *extr;
  int size;
} bnh;

bnh *newBinheap(int (*)(void *,void *), void (*)(struct node *, struct node *));
node *insert(bnh *, void *);
vertex *extractMin(bnh *);
node *decreaseKey(bnh *, node *, void *);

#endif
