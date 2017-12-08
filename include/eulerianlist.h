#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _list{
  size_t value;
  struct _list *next;
} List;

typedef struct _llist{
  List *list;
  struct _llist *next;
} LList;

void addToList(List **self, size_t value);

void addListToLists(LList **listsOfList, List *list);

void cloneList(List *src, List **dst);

void addPair(List **dst, size_t x, size_t y);

void deletePair(List **dst, size_t x, size_t y);

void deleteFirstElement(List **self);

bool isInList(List *self, size_t element);

void printLList(LList *self);

void printList(List *self);

#endif
