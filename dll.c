
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vertex.h"
#include "node.h"
#include "dll.h"

dll *initDLL(void) {
  dll *d = (dll *) malloc(sizeof(struct dll));
  d->head = NULL;
  d->no = 0;
  return d;
}

void addNode(dll *d, node *n) {
  if (d->head == NULL) {
    n->next = n;
    n->previous = n;
    d->head = n;
  }
  else {
    n->previous = d->head->previous;
    d->head->previous->next = n;

    n->next = d->head;
    d->head->previous = n;

    d->head = n;
  }
  d->no++;
}


 void merge(dll *A, dll *B) {
  if (B->no == 0)
    return;
  else if (A->no == 0) {
    A->head = B->head;
    A->no = B->no;
    return;
  }

  else {
  A->head->previous->next = B->head;
  B->head->previous->next = A->head;
  node *temp = B->head->previous;
  B->head->previous = A->head->previous;
  A->head->previous = temp;
  A->no += B->no;
  B->head = 0;
  B->no = 0;
  B->no = 0;
  }
}

//TODO ADD DELETION CODE
void deleteHead(dll *d) {
  if (d->no == 1) {
    --d->no;
    d->head = NULL;
    return;
  }
  d->head->previous->next = d->head->next;
  d->head->next->previous = d->head->previous;
  d->head = d->head->next;
  --d->no;
}

void deleteDLL(dll *d, node *y) {
  if (d->no == 0)
    printf("DELETION FROM EMPTY LIST\n");
  else if (d->no == 1) {
    d->head = NULL;
    d->no--;
  }
  else {
    if (d->head == y)
      d->head = y->next;
    y->previous->next = y->next;
    y->next->previous = y->previous;
    d->no--;
  }
}
