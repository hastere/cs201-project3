/*Various BST Node functions
By Andrew Stere
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "dll.h"
#include "vertex.h"

struct node *newNode(void *v) {
    struct node *node = (struct node *) malloc(sizeof(struct node));
    node->value = v;
    node->children = initDLL();
    node->previous = NULL;
    node->next = NULL;
    node->parent = node;
    return(node);
}
