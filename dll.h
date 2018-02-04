#ifndef DLL_H
#define DLL_H

#include "node.h"
struct node;
typedef struct dll {
  struct node *head;
  int no;
} dll;

dll *initDLL(void);
void addNode(dll *, struct node *);
void merge(dll *, dll *);
void display(dll *);
void deleteHead(dll *);
void deleteDLL(dll *, struct node *);

#endif
