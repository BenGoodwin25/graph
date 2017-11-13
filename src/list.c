#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <unistd.h>

typedef struct _list{
  size_t value;
  struct _list *next;
} List;

#endif
