#ifndef EULERIAN_PATH_H
#define EULERIAN_PATH_H

#include <unistd.h>

/* structure to save informations for the eulerian trail */
typedef struct _eulerlist{
  ssize_t node;
  size_t weight;
  struct _eulerlist *next;
} EulerianList;

/* structure to save the eulerian trail of a graph */
typedef struct _path {
  size_t totalWeight;
  int heuristicNumber;
  EulerianList *start;
} EulerianPath;

#endif
