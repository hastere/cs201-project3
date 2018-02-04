#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include "vertex.h"


vertex *newVertex(int n, int max) {
  struct vertex *v = (struct vertex *) malloc(sizeof(struct vertex));
  v->key = max;
  v->number = n;
  v->predecessor = -1;
  v->owner = NULL;
  return(v);
}

int vertexComparator(void *a,void *b) {
  //cast from the generic type to the actual type
  vertex *v = (vertex *) a;
  vertex *w = (vertex *) b;
  //return a positive number if v's key > w's
  if (v->key > w->key)
    return 1;
  //return a negative number if if v's key < w's
  else if (v->key < w->key)
    return -1;
  else {
    if (v->predecessor > w->predecessor)
      return 1;
    else if (v->predecessor < w->predecessor)
      return -1;
    else {
      if (v->number > w->number)
        return 1;
      else if (v->number < w->number)
        return -1;
      else {
        printf("\t SOMETHING FUCKY IS GOING ON\n");
        return 0;
      }

    }
  }
  //return a zero if they are equal (break ties with vertex numbers)
}

void swap(node* a, node * b) {
    vertex* v = (vertex*) a->value;
    vertex* w = (vertex*) b->value;
    v->owner = b;
    w->owner = a;
    vertex *temp = b->value;
    b->value = v;

    a->value = temp;
}
