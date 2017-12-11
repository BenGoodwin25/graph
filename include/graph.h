#ifndef LIB_GRAPH_H
#define LIB_GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <list.h>
#include <log.h>

/* structure representing a graph */
typedef struct _graph{
  bool isDirected;
  size_t nbMaxNodes;
  Neighbour **adjList;
} Graph;

/*
 * Function : Create a graph with the right number of nodes
 *
 * Param :
 *  self : the structure where the result graph will be saved
 *  maxNodes : the maximum number of nodes for the graph
 *  isDirected : tells if the graph is directed or not
 *
 * Return :
 *  value 0 : the graph were successfully created
 *  value 1 : unexpected allocation error
 */
int create_graph(Graph *self, size_t maxNodes, bool isDirected);

/*
 * Function : Load a graph from the given file
 *
 * Param :
 *  self : the structure where the loaded graph will be saved
 *  graphFile : the file containing the saved graph to load
 *
 * Return :
 *  value 0 : the graph were successfully loaded from the file
 *  value 1 : error while opening the file
 */
int load_graph(Graph *self, const char *graphFile);

/*
 * Function : Add a node to the given graph
 *
 * Param :
 *  self : the structure where the node will be added
 *  nodeName : the name of the node to create
 *
 * Return :
 *  value 0 : the node has been successfully added
 *  value 1 : the node is Out Of Bound
 *  value 2 : unexpected allocation error
 *  value 3 : Node name invalid
 */
int add_node(Graph *self, int nodeName);

/*
 * Function : Add an edge to the given graph
 *
 * Param :
 *  self : the structure where the edge will be added
 *  fromName : the start node of the edge
 *  toName : the end node of the edge
 *  edgeName : the name of the edge
 *  Weight : the wieght of the edge
 *  isSymmetric : tells if the edge is symmetric or not
 *
 * Return :
 *  value 0 : the edge has been successfully added
 *  value 8 : the start node doesn't exists
 *  value 9 : the end node doesn't exists
 *  value 10 : the edge already exists
 */
int add_edge(Graph *self, int fromName, int toName, int edgeName, int Weight, bool isSymmetric);

/*
 * Function : Check if a node exists in the given graph
 *
 * Param :
 *  self : the graph to check if the node exists
 *  nodeName : the name of the node to check
 *
 * Return : true if the node exists, false otherwise
 */
bool is_node_exists(Graph* self, int nodeName);

/*
 * Function : Check if an edge already exists in the graph
 *
 * Param :
 *  self : the graph to check if the edge exists
 *  edgeName : the name of the edge to check
 *
 * Return : true if the edge exists, false otherwise
 */
bool is_edge_exists(Graph* self, int edgeName);

/*
 * Function : Delete a node from the given graph
 *
 * Param :
 *  self : the graph where the node will be deleted
 *  nodeName : the name of the node to delete
 *
 * Return :
 *  value 0 : the node has been successfully deleted
 *  value 9 : the node is Out Of Bound
 *  value 10 : the node is unknown
 */
int remove_node(Graph *self, int nodeName);

/*
 * Function : Delete an edge from the given graph
 *
 * Param :
 *  self : the graph where the edge will be deleted
 *  edgeName : the name of the edge to delete
 *
 * Return :
 *  value 0 : the edge has been successfully deleted
 *  value 1 : encountered an error will deleting the edge
 */
int remove_edge(Graph *self, int edgeName);

/*
 * Function : Display a graph in the terminal
 *
 * Param :
 *  self : the graph to output to the terminal
 *
 * Return :
 *  value 1 : the graph doesn't exists
 *  other value : check values of output_graph_to_stream
 */
int view_graph(Graph *self);

/*
 * Function : Save a graph in a file
 *
 * Param :
 *  self : the graph to save in the file
 *  fileName : the name of the file where the graph will be saved
 *
 * Return :
 *  value 10 : error while openning the file
 *  other value : check values of output_graph_to_stream
 */
int save_graph(Graph *self, const char *fileName);

/*
 * Function : Delete the given graph
 *
 * Param :
 *  self : the graph to delete
 *
 * Return :
 *  value 0 : the graph is successfully delete
 */
int delete_graph(Graph *self);

#endif
