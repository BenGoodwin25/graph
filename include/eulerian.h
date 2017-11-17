#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#include <eulerianlist.h>
#include <matrix.h>
#include <graph.h>

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
 *  self : matrix such that M(x, y) gives the shortest distance between nodes x and y
 *  predecessor : matrix such that P rec(x, y) gives the predecessor of y on the shortest path form x
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
size_t Floyd_Warshall(Graph *G, Matrix **self, Matrix **predecessor);

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
size_t minLengthPairwise(size_t *V,List *bestMatching, List *bestMatchingWeight);

/*
 * Function :
 *
 * Param :
 *  V :  the set of nodes to match by pairs (must have an even number of elements), ordered by node
numbers
 *  currentListOfPairs : the current list of pairs under construction
 *  listsOfPairs :  The list (initially empty) of all the possible list of pairs
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
size_t listPairs(size_t *V, List *currentListOfPairs, List *listsOfPairs);

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
size_t getEulerianCircuit(Graph *self, size_t h);

/*
 * Function : output result to stream (stdout, FILE)
 *
 * Param :
 *  self :  The result to output
 *  stream : output stream
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
size_t outputResultsToStream(size_t *self, FILE *stream);

/*
 * Function : output result to stdout, call of outputResultsToStream()
 *
 * Param :
 *  self :  The result to display
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
size_t displayResults(size_t *self);

#endif //GRAPH_GRAPH_H
