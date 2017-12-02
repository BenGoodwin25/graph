#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#include <eulerianlist.h>
#include <eulerianpath.h>
#include <matrix.h>
#include <graph.h>

#define GRAPH_EULERIAN 0
#define GRAPH_HALF_EULERIAN 1
#define GRAPH_NON_EULERIAN 2

/*
 * Function : duplicate a graph to do efficient work on it
 *
 * Param :
 *  source : the source graph to duplicate
 *  destination : the destination graph to duplicate
 *
 * Return :
 *  error code 0 : copy correctly executed
 *  error code 1 : copy could not be done
 *  error code 20 : function not yet implemented
 */
size_t copyGraph(Graph *source, Graph *destination);

/*
 * Function :
 *
 * Param :
 *  G : a graph
 *  weights : matrix such that M(x, y) gives the shortest distance between nodes x and y
 *  predecessors : matrix such that P rec(x, y) gives the predecessors of y on the shortest path form x
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
size_t Floyd_Warshall(Graph *g, Matrix *weights, Matrix *predecessors);

/*
 * Function : Minimal-length Pairwise Matching by Enumeration
 *
 * Param :
 *  V : list of odd degree nodes sorted by node numbe
 *  bestMaching : the minimal-length pairwise matching of V nodes
 *  bestMachingWeight : the total weight of this minimal-length pairwise matching
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
size_t minLengthPairwise(List *V, List **bestMatching, size_t *bestMatchingWeight, Matrix *weights);

/*
 * Function :
 *
 * Param :
 *  V :  the set of nodes to match by pairs (must have an even number of elements), ordered by node numbers
 *  currentListOfPairs : the current list of pairs under construction
 *  listsOfPairs :  The list (initially empty) of all the possible list of pairs
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
LList *listPairs(List *V, List *currentListOfPairs, LList *listsOfPairs);

/*
 * Function : get Eulerian circuit, display it and write it on a file
 *
 * Param :
 *  self : graph to get Eulerian circuit
 *  h : heuristic to use 1,2,3 ... 0 is all
 *
 * Return :
 *  error code 0 : create correctly executed
 *  error code 1 : create couldn't be executed
 *  error code 20 : function not yet implemented
 */
size_t getEulerianCircuit(Graph *self, size_t heuristic);

/*
 * Function : check if a graph is eulerian or not
 *
 * Param :
 *  self :  The graph to check if it is eulerian
 *  eulerianResult :  The result if its eulerian (0 : eulerian, 1 : half-eulerian, 2 : non eulerian)
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
size_t isEulerian(Graph *self, size_t *eulerianResult);

/*
 * Function : create a non eulerian graph
 *
 * Param :
 *  self :  The graph to create
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
void createExampleNonEulerian(Graph *self);

/*
 * Function : create a half eulerian graph
 *
 * Param :
 *  self :  The graph to create
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
void createExampleHalfEulerian(Graph *self);

/*
 * Function : check if a graph is eulerian or not
 *
 * Param :
 *  self :  The graph to create
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
void createExampleEulerian(Graph *self);

void output_result(EulerianPath *path, FILE *stream);

#endif //GRAPH_GRAPH_H
