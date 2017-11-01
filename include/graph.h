#ifndef GRAPH_H
#define GRAPH_H

#include <libGraph.h>

/*
 * Function :
 *
 * Param :
 *  source :
 *  destination :
 *  filename :
 *
 * Return :
 *  error code 0 : copy correctly executed
 *  error code 1 : copy could not be done
 *  error code 20 : function not yet implemented
 */
size_t copyGraph(Graph *source, Graph **destination);

#endif //GRAPH_GRAPH_H
