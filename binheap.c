
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "node.h"
#include "dll.h"
#include "vertex.h"
#include "binheap.h"


void consolidate(bnh *);
node *bubbleUp(bnh *, node *);
void updateConsolidationArray(bnh *, node **, node *, int);
node *combine(bnh *, node *, node *);

//done
bnh *newBinheap(int (* comparator)(void *,void *), void (* swapper)(struct node *, struct node *)) {
  bnh *b = (bnh *)malloc(sizeof(struct bnh));
  b->comparator = comparator;
  b->swapper = swapper;
  b->doubly = initDLL();
  b->extr = NULL;
  b->size = 0;
  return b;
}

//done
void unionHeap(struct bnh *b, struct bnh *donor) {
  //b and donor are binomial heaps
  merge(b->doubly, donor->doubly);
  b->size += donor->size;
  donor->doubly = initDLL();
  donor->size = 0;
  donor->extr = NULL;
  consolidate(b);
}

//done
node *insert(bnh *b, void *v) {
  //b is a binomial heap, v is the value to be inserted
  node *n = newNode(v);
  addNode(b->doubly,n);
  b->size++;
  consolidate(b);
  return n;
}

//done
node *decreaseKey(bnh *b, node *n, void *v) {
  n->value = v;
  node *t = bubbleUp(b,n);

  if (b->comparator(t->value,b->extr->value) == -1)
    b->extr = t;
  return t;
}

//done?
node *bubbleUp(bnh *b, node *n) {
  printf("in bubble up\n");
  if (n->parent == n)
    return n;
  else if (b->comparator(n->value,n->parent->value) > 0) {
    return n;
  }
  else {
    b->swapper(n, n->parent);
    return bubbleUp(b,n->parent);
  }
  printf("leaving bubble up\n");

}

//done
void delete(bnh *b, node *n) {
  decreaseKey(b, n, NULL);
  extractMin(b);
}

//done
vertex *extractMin(bnh *b) {
  node *y = b->extr;
  deleteDLL(b->doubly, y);
  // the children of y are a linked list
  //set each of the children's parent to point to themselves
  int i = 0;
  node *temp = y->children->head;
  while (i < y->children->no) {
    //set parent = y
    temp->parent = temp;
    temp = temp->next;

    //y->children->head->parent = temp;
    //shift forward
    //y->children->head = y->children->head->next;
    ++i;
  }
  //merge the children of y into b's root list (via linked-list union)
  merge(b->doubly,y->children);
  consolidate(b);
  b->size--;
  return y->value;
}

//done
void consolidate(bnh *b) {
  //create the consolidation array D
  int sizeD = floor(log2(b->size) + 1);
  //  set D to the allocation of an array  D's size
  node **D = (node **) malloc(sizeof(struct node *) * sizeD);
  //  initialize the D array to nulls
  int i;
  for (i = 0; i < sizeD; ++i) {
    D[i] = NULL;
  }
  node *spot;
  i = 0;
  while (b->doubly->no != 0) {
    //  set spot to the head node in b's root list
    spot = b->doubly->head;
    deleteHead(b->doubly);
    // update the D array with spot
    updateConsolidationArray(b,D,spot,sizeD);
    i++;
  }

  // set b's extreme pointer to null
  b->extr = NULL;
  for (i = 0; i < sizeD; ++i) {
    if (D[i] != NULL) {
      //D[i] into b's root list (via the linked-list's insert method)
      addNode(b->doubly, D[i]);
      if (b->extr == NULL)
        b->extr = D[i];
      else if (b->comparator(b->extr->value, D[i]->value) == 1)
        b->extr = D[i];
    }
  }

}

void updateConsolidationArray(bnh *b, node **D, node *spot, int max) {
  // set degree to the number of spot's children (using linked-list size)
  int deg = spot->children->no;
  while (D[deg] != NULL && deg < max) {
  //combine spot and D[degree], setting spot to the combined subheap

  spot = combine(b,spot,D[deg]);
  // set D[degree] to null, since that slot is now empty
  D[deg] = NULL;
  // increment degree
  deg++;
  }
  // set D[degree] to spot
  D[deg] = spot;
}

node *combine(bnh *b, node *x, node *y) {
  // if b's comparator says x's value is more extreme than y's

  if (b->comparator(x->value,y->value) == -1) {
    //insert y into the children of x (via linked list insert)
    addNode(x->children, y);
    //set the parent of y to x
    y->parent = x;
    //return x

    return x;
  }
  else {
    //insert x into the children of y (via linked list insert)
    addNode(y->children, x);
    //set the parent of x to y
    x->parent = y;

    //return y
    return y;
  }
}
