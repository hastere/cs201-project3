#ifndef VERTEX_H
#define VERTEX_H

#include "node.h"

typedef struct vertex {
  int key;
  int number;
  int predecessor;
  struct node *owner;
} vertex;

vertex *newVertex(int,int);
int vertexComparator(void *,void *);
void swap(struct node *, struct node *);

#endif
