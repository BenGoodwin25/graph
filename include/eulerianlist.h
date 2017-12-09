#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* structure for a list of element */
typedef struct _list{
  size_t value;
  struct _list *next;
} List;

/* structure for list of lists */
typedef struct _llist{
  List *list;
  struct _llist *next;
} LList;

/*
 * Function : add an element to the list
 *
 * Param :
 *  self : the list to store the element in
 *  value : the element to store
 */
void addToList(List **self, size_t value);

/*
 * Function : add a list to a list of lists
 *
 * Param :
 *  self : the list to store the list in
 *  value : the list to store
 */
void addListToLists(LList **listsOfList, List *list);

/*
 * Function : add a list of lists at the end of a list of lists
 *
 * Param :
 *  self : the list of lists where the other list of lists will be store
 *  value : the new list of lists to store
 */
void addLListToLList(LList **self, LList *list);

/*
 * Function : clone a list from the source to the destination
 *
 * Param :
 *  src : the source list to clone
 *  dst : the destination list where the clone will be saved
 */
void cloneList(List *src, List **dst);

/*
 * Function : add a pair to the destination list
 *
 * Param :
 *  dst : the destination where the pair will be stored
 *  x : the first element of the pair to store
 *  y : the second element of the pair to store
 */
void addPair(List **dst, size_t x, size_t y);

/*
 * Function : delete a pair from the destination
 *
 * Param :
 *  dst : the list where the pair will be removed
 *  x : the first element of the pair to delete
 *  y : the second element of the pair to delete
 */
void deletePair(List **dst, size_t x, size_t y);

/*
 * Function : delete the ifrst element of the given list
 *
 * Param :
 *  self : the list where the first element will be deleted
 */
void deleteFirstElement(List **self);

/*
 * Function : check if an element is in the given list
 *
 * Param :
 *  self : the list where to find the element
 *  element : the element to find in the list
 *
 * Return :
 *  true if the element is in the list, false otherwise
 */
bool isInList(List *self, size_t element);

/*
 * Function : compute the size of the given list
 *
 * Param :
 *  self : the list on which to compute the size
 *
 * Return : the size of the list
 */
size_t getListSize(List *self);

/*
 * Function : Print the list of lists on the terminal
 *
 * Param :
 *  self : the list of lists to print
 */
void printLList(LList *self);

/*
 * Function : Print the given list on the terminal
 *
 * Param :
 *  self : the list to print
 */
void printList(List *self);

#endif
