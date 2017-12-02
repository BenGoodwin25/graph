#include <eulerianlist.h>

void addToList(List **self, size_t value) {
  if (*self == NULL) {
    *self = malloc(sizeof(List));
    (*self)->value = value;
    (*self)->next = NULL;
    return;
  }
  List *tmp = *self;
  while (tmp != NULL && tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = malloc(sizeof(List));
  tmp = tmp->next;
  tmp->value = value;
  tmp->next = NULL;
}

void addListToLists(LList **listsOfList, List *list) {
  if (*listsOfList == NULL) {
    *listsOfList = malloc(sizeof(LList));
    (*listsOfList)->list = list;
    (*listsOfList)->next = NULL;
    return;
  }
  LList *tmp = *listsOfList;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = malloc(sizeof(LList));
  tmp = tmp->next;
  tmp->list = list;
  tmp->next = NULL;
}

void cloneList(List *src, List **dst) {
  if (src == NULL) {
    *dst = NULL;
    return;
  }
  *dst = malloc(sizeof(List));
  (*dst)->value = src->value;
  (*dst)->next = NULL;
  List *tmp = *dst;
  while (src->next != NULL) {
    src = src->next;
    tmp->next = malloc(sizeof(List));
    tmp = tmp->next;
    tmp->value = src->value;
    tmp->next = NULL;
  }
}

void addPair(List **dst, size_t x, size_t y) {
  if (*dst == NULL) {
    *dst = malloc(sizeof(List));
    (*dst)->value = x;
    (*dst)->next = malloc(sizeof(List));
    List *tmp = (*dst)->next;
    tmp->value = y;
    tmp->next = NULL;
    return;
  }
  List *tmp = *dst;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = malloc(sizeof(List));
  tmp = tmp->next;
  tmp->value = x;
  tmp->next = malloc(sizeof(List));
  tmp = tmp->next;
  tmp->value = y;
  tmp->next = NULL;
}

void deletePair(List **dst, size_t x, size_t y) {
  List *tmp = *dst;
  if (tmp->value == x || tmp->value == y) {
    deleteFirstElement(dst);
    tmp = *dst;
  }
  if (tmp->value == x || tmp->value == y) {
    deleteFirstElement(dst);
    tmp = *dst;
  }
  while (tmp != NULL && tmp->next != NULL) {
    if (tmp->next->value == x || tmp->next->value == y) {
      List *save = tmp->next->next;
      free(tmp->next);
      tmp->next = save;
    }
    tmp = tmp->next;
  }
}

void deleteFirstElement(List **self) {
  List *tmp = *self;
  *self = tmp->next;
  free(tmp);
}

void printLList(LList *self) {
  printf("LList :\n");
  while (self != NULL) {
    List *tmp = self->list;
    while (tmp != NULL) {
      printf("%zu/", tmp->value);
      tmp = tmp->next;
    }
    printf("\n");
    self = self->next;
  }
}

void printList(List *self) {
  printf("List :\n");
  while (self != NULL) {
    printf("%zu/", self->value);
    self = self->next;
  }
  printf("\n");
}
