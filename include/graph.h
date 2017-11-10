#ifndef GRAPH_H
#define GRAPH_H

#include <matrix.h>
#include <libGraph.h>

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
 *  G :
 *  self :
 *  predecessor :
 *
 * Return :
 *  error code 0 : function correctly executed
 *  error code 1 : function couldn't be done
 *  error code 20 : function not yet implemented
 */
size_t Floyd_Warshall(Graph *G, Matrix **self, Matrix **predecessor);


#endif //GRAPH_GRAPH_H
