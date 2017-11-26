#ifndef EULERIAN_PATH_H
#define EULERIAN_PATH_H

#include <unistd.h>

typedef struct _eulerlist{
  size_t node;
  size_t weight;
  struct _eulerlist *next;
} EulerianList;

typedef struct _path {
  size_t totalWeight;
  int heuristicNumber;
  EulerianList *start;
} EulerianPath;

#endif
