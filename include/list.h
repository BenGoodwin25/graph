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

//ajout
int addEdge(Neighbour **self, int neighbour, int edgeName, int Weight);

// supression de toutes les edges dans la liste donnée ayant pour endpoint le  point passer en paramètre
int deleteEdgeFromNodeName(Neighbour** self, int nodeName);

//suppression du node ayant la donnée neighbour
int deleteEdge(Neighbour** self, int edgeName);

//suppression du premier node
int delFirstEdge(Neighbour** self);

//destruction
int destroyList(Neighbour** self);

//vide
bool isEmptyList(const Neighbour* self);

// écrit toute la liste dans le stream (pas de retour à la ligne)
int outputList(Neighbour *self, FILE *stream);

#endif
