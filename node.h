#ifndef NODE_H
#define NODE_H
#include "dll.h"
#include "vertex.h"
typedef struct node {
    void *value;
    struct dll *children;
    struct node *previous;
    struct node *next;
    struct node *parent;
} node;

struct node *newNode(void *);

#endif
