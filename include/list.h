#ifndef LIB_LIST_H
#define LIB_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <log.h>

/* structure to save neighbours of a graph */
typedef struct _neighbour {
  int neighbour;
  int edgeName;
	int weight;
	struct _neighbour *nextNeighbour;
} Neighbour;

/*
 * Function : Check if an edge exists in the list
 *
 * Param :
 *  self : the list where the check have to be applied
 *  edgeName : the name of the edge to check
 *
 * Return : true if the edge exists, false otherwise
 */
bool edgeExist(Neighbour *self, int edgeName);

/*
 * Function : Add an edge/node in the list
 *
 * Param :
 *  self : the list where to add the edge
 *  neighbour : destination of the edge
 *  edgeName : the name of the edge to create
 *  weight : weight of the edge to create
 *
 * 0 : the edge have been created
 * 1 : Edge already exist
 * 2 : unexpected allocation error
 */
int addEdge(Neighbour **self, int neighbour, int edgeName, int Weight);

/*
 * Function : Delete all edge to a certain node
 *
 * Param :
 *  self : the list where the deletion will be operated
 *  nodeName : the name of the node to delete all edge
 *
 * 0 : the edges have been deleted
 * $deleteEdge()$ : code of deleteEdge
 */
int deleteEdgeFromNodeName(Neighbour** self, int nodeName);

/*
 * Function : Delete edge with the number edgeName
 *
 * Param :
 *  self : the list where the deletion will be operated
 *  edgeName : the name of the edge to delete
 *
 * 0 : the edge has been deleted
 * 1 : Edge doesn't exist
 */
int deleteEdge(Neighbour** self, int edgeName);

/*
 * Function : Delete first edge
 *
 * Param :
 *  self : the list where the first element will be deleted
 *
 * 0 : the first element has been deleted
 * 1 : Edge doesn't exist/empty
 */
int delFirstEdge(Neighbour** self);

/*
 * Function : Destroy list, and free the memory
 *
 * Param :
 *  self : the list to destroy, and deallocate
 *
 * 0 : the list has been properly deleted
 * 1 : otherwise
 */
int destroyList(Neighbour** self);

/*
 * Function : Check if the list is empty, has no edge
 *
 * Param :
 *  self : the list to check if it's empty
 *
 * true : the edge exist
 * false : the edge doesn't exist
 */
bool isEmptyList(const Neighbour* self);

/*
 * Function : Display into a file stream the list, with each of his edges.
 *
 * Param :
 *  self : the list to display
 *  output : the file stream to output (use stdout, for basic output)
 *
 * 0 : the output had no error,
 * 1 : otherwise
 */
int outputList(Neighbour *self, FILE *stream);

#endif
