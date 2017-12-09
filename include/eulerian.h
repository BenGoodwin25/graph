#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <unistd.h>

#include <eulerianlist.h>
#include <eulerianpath.h>
#include <matrix.h>
#include <graph.h>

/*  Definitions for eulerian graph state constants  */
#define GRAPH_EULERIAN 0
#define GRAPH_HALF_EULERIAN 1
#define GRAPH_NON_EULERIAN 2

/*  Definitions for heuristic choice  */
#define HEURISTIC_ALL 0
#define HEURISTIC_SIMPLE_RANDOM 1
#define HEURISTIC_MULTIPLE_RANDOM 2
#define HEURISTIC_EXCLUDE_MAX 3
#define HEURISTIC_NONE 4

/*
 * Function : duplicate a graph from the source to the destination
 *
 * Param :
 *  source : the source graph to duplicate
 *  destination : the destination graph to duplicate
 *
 * Return :
 *  error code 0 : copy correctly executed
 */
size_t copyGraph(Graph *source, Graph *destination);

/*
 * Function : Apply floyd warshall algorithm on the graph storing informations in two matricies
 *
 * Param :
 *  G : The graph on which floyd warshall will be applied
 *  weights : matrix such that M(x, y) gives the shortest distance between nodes x and y
 *  predecessors : matrix such that Prec(x, y) gives the predecessors of y on the shortest path form x
 *
 * Return :
 *  error code 0 : function correctly executed
 */
size_t Floyd_Warshall(Graph *g, Matrix *weights, Matrix *predecessors);

/*
 * Function : Minimal-length Pairwise Matching by Enumeration
 *
 * Param :
 *  V : list of odd degree nodes sorted by node number
 *  bestMaching : the minimal-length pairwise matching of V nodes
 *  bestMachingWeight : the total weight of this minimal-length pairwise matching
 *  weights : matrix containing all shortest way between two nodes
 *  heuristic : the heuristic to apply on the pairwise matching
 *  nbPass : the number of iteration for the multiple random heuristic
 *
 * Return :
 *  error code 0 : function correctly executed
 */
size_t minLengthPairwise(List *V, List **bestMatching, size_t *bestMatchingWeight, Matrix *weights, size_t heuristic, size_t nbPass);

/*
 * Function : list pairs of odd degree nodes with a random heuristic
 *
 * Param :
 *  V :  the set of nodes to match by pairs (must have an even number of elements), ordered by node numbers
 *  currentListOfPairs : the current list of pairs under construction
 *  listsOfPairs : The list (initially empty) of all the possible list of pairs
 *
 * Return : A list of random pairwise matching
 */
LList *listPairsSimpleRandom(List *V, List *currentListOfPairs, LList *listsOfPairs);

/*
 * Function : list pairs of odd degree nodes with a random heuristic done multiple times
 *
 * Param :
 *  V :  the set of nodes to match by pairs (must have an even number of elements), ordered by node numbers
 *  currentListOfPairs : the current list of pairs under construction
 *  listsOfPairs : The list (initially empty) of all the possible list of pairs
 *  nbPass : The number of execution to do with random heuristic
 *
 * Return : A list of all random results pairwise matching
 */
LList * listPairsMultipleRandom(List *V, List *currentListOfPairs, LList *listsOfPairs, size_t nbPass);

/*
 * Function : list pairs of odd degree nodes with a reject max heuristic
 *
 * Param :
 *  V :  the set of nodes to match by pairs (must have an even number of elements), ordered by node numbers
 *  currentListOfPairs : the current list of pairs under construction
 *  listsOfPairs : The list (initially empty) of all the possible list of pairs
 *  weights : a matrix containing all shortest path between two nodes
 *
 * Return : A list of pairwise matching computed with the reject max heuristic
 */
LList * listPairsExcludeMax(List *V, List *currentListOfPairs, LList *listsOfPairs, Matrix *weights);

/*
 * Function : list all pairs of odd degree nodes (no heuristic at all)
 *
 * Param :
 *  V :  the set of nodes to match by pairs (must have an even number of elements), ordered by node numbers
 *  currentListOfPairs : the current list of pairs under construction
 *  listsOfPairs :  The list (initially empty) of all the possible list of pairs
 *
 * Return : A list of all pairwise matching
 */
LList * listPairsNoHeuristic(List *V, List *currentListOfPairs, LList *listsOfPairs);

/*
 * Function : get Eulerian circuit, display it and write it on a file
 *
 * Param :
 *  self : graph to get Eulerian circuit
 *  heuristic : heuristic to use 1,2,3 ... 0 is all
 *  eulerianState : tells if the graph is (half) eulerian or not
 *  nbPass : the number of iteration to do with multiple random heuristic if heuristic is selected
 *
 * Return :
 *  error code 0 : function executed with no error
 */
size_t getEulerianCircuit(Graph *self, size_t heuristic, size_t eulerianState, size_t nbPass);

/*
 * Function : check if a graph is eulerian or not
 *
 * Param :
 *  self : The graph to check if it is eulerian
 *  eulerianResult :  The result of eulerian state (see above for values)
 *
 * Return :
 *  error code 0 : function correctly executed
 */
size_t isEulerian(Graph *self, size_t *eulerianResult);

/*
 * Function : create a non eulerian graph
 *
 * Param :
 *  self : The graph to create
 *
 * Return : store the created graph in self
 */
void createExampleNonEulerian(Graph *self);

/*
 * Function : create a non eulerian graph twice larger than the original one
 *
 * Param :
 *  self : The graph to create
 *
 * Return : store the created graph in self
 */
void createExampleDoubleNonEulerian(Graph *self);

/*
 * Function : create a half eulerian graph
 *
 * Param :
 *  self : The graph to create
 *
 * Return : store the created graph in self
 */
void createExampleHalfEulerian(Graph *self);

/*
 * Function : check if a graph is eulerian or not
 *
 * Param :
 *  self : The graph to create
 *
 * Return : store the created graph in self
 */
void createExampleEulerian(Graph *self);

/*
 * Function : output the eulerian path into the stream
 *
 * Param :
 *  path : the eulerian path to output
 *  stream : the stream where the eulerian path is writen
 *
 * Return : store the created graph in self
 */
void output_result(EulerianPath *path, FILE *stream);

#endif //GRAPH_GRAPH_H
