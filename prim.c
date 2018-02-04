
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "scanner.h"
#include "vertex.h"
#include "binheap.h"
#include "node.h"

int findMaxV(FILE *);
void Fatal(char *, ...);
int **newAdjMatrix(int);
void fillMatrix(int **, FILE *);
vertex **newVertexList(int);

void mstPrim(int **, vertex **, int);
vertex *mstPrimTrue(bnh *Q,int **, vertex **, int);

int maxW;
int main(int argc, char **argv) {
  FILE *data = fopen(argv[1],"r");
    if (data == NULL) {
        Fatal("Unable to open file for read\n");
    }
  maxW = 2;
  int maxV = findMaxV(data) + 1;
  printf("max found was %d, incremented by 1\n", maxV);
  int **adjMatrix = newAdjMatrix(maxV);
  fclose(data);
  data = fopen(argv[1],"r");
    if (data == NULL) {
        Fatal("Unable to open file for read\n");
      }
  fillMatrix(adjMatrix,data);
  for (int x = 0; x < maxV; ++x) {
    printf("\n");
    for (int y = 0; y < maxV; ++y) {
      printf ("| %d |", adjMatrix[x][y]);
    }
  }
  printf("\n");
  vertex **vList = newVertexList(maxV);
  mstPrim(adjMatrix, vList, maxV);
  for (int i = 0; i < (maxV); ++i){
    if (vList[i]->predecessor != -1)
      printf("vertex %d has predecessor %d\n", i, vList[i]->predecessor);
  }
  return 0;
}

void fillMatrix(int **m, FILE *fp) {
  char *temp, *begin, *term, *weight;
  temp = readToken(fp);
  if (temp == NULL)
    Fatal("Bad input file format\n");
  while (!feof(fp)) {
    begin = temp;

    temp = readToken(fp);
    if (temp == NULL)
      Fatal("Bad input file format\n");
    term = temp;

    temp = readToken(fp);
    if (temp == NULL)
      Fatal("Bad input file format\n");
    weight = temp;

    if (strcmp(weight, ";") == 0)
      weight = "1";
    else
      temp = readToken(fp);

    if (m[atoi(begin)][atoi(term)] == 0 && m[atoi(term)][atoi(begin)] == 0)
      m[atoi(term)][atoi(begin)] = m[atoi(begin)][atoi(term)] = atoi(weight);

    if (atoi(weight) > maxW)
      maxW = atoi(weight) + 1;
    temp = readToken(fp);
  }
}

int **newAdjMatrix(int max){
  int **adjMatrix = malloc(max * (sizeof (adjMatrix)));
  int i,j;
  for (i = 0; i < max; i++){
    adjMatrix[i] = malloc(max * (sizeof(adjMatrix[i])));
  }

  for (i = 0; i < max; ++i) {
    for (j = 0; j < max; ++j) {
      adjMatrix[i][j] = 0;
    }
  }
  return adjMatrix;
}

int findMaxV(FILE *f) {
  int max = 0;
  char *v1;
  int count = 0;
  v1 = readToken(f);
  if (v1 == NULL)
    Fatal("Bad input file format\n");
  while (!feof(f)){

    while (count < 2) {
      if (atoi(v1) > max)
        max = atoi(v1);
      v1 = readToken(f);
      ++count;
    }
    count = 0;
    while (strcmp(v1,";") != 0) {
      v1 = readToken(f);
    }
    v1 = readToken(f);
  }
  return max;
}


vertex **newVertexList(int maxV) {
  vertex **v = malloc(sizeof(vertex *) * (maxV));
  int i;
  for (i = 0; i < (maxV); ++i) {
    v[i] = newVertex(i,maxW);
  }
  return v;
}

void mstPrim(int **G, vertex **v, int maxV) {
  bnh *Q = newBinheap(vertexComparator,swap);

  for (int i = 0; i < maxV; ++i) {
    v[i]->owner = insert(Q, v[i]);
  }
  while (Q->size > 0) {
    mstPrimTrue(Q,G,v,maxV);
    printf("AGAIN!\n");
  }
}

vertex *mstPrimTrue(bnh * Q, int **G, vertex **v, int maxV) {
  //for each u in G.V
  //  u.key = INT_MAX
  //  u.parent = NULL
  //r.key = 0

  //Q = G.V
  //while Q != O
  vertex *start = (vertex *) Q->extr->value;
  start->key = 0;
  decreaseKey(Q,start->owner,start);

  vertex * u;
  printf("all values inserted\n");
  while (Q->size != 0) {
    //u = extractMin(Q)
    u = extractMin(Q);
    printf("Pulled %d\n", u->number);
    u->owner = NULL;
    if (u->key == maxW) {
      v[u->number]->owner = insert(Q,u);
      break;
    }
    //for each v in G.Adj[u]
    for (int i = 0; i < maxV; ++i) {
      if (G[u->number][i] != 0) {
        printf("\t\tpoint %d is adjacent to  %d\n",  i, u->number);
        if (v[i]->owner != NULL && G[u->number][i] < v[i]->key) {
          v[i]->predecessor = u->number;
          v[i]->key = G[u->number][i];
          decreaseKey(Q, v[i]->owner, v[i]);
        }
      }
    }
  }
  return start;
}


//void printTree() {}
void Fatal(char *fmt, ...) {
  va_list ap;
  fprintf(stderr,"An error occured: ");
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  exit(-1);
}
