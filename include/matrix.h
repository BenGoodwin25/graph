#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <graph.h>
#include <log.h>

typedef struct _matrix{
  size_t maxNodes;
  int **value;
  bool isDirected;
} Matrix;


/*
 * Function : creation of a matrix
 *
 * Param :
 *  self : the matrix to create
 *  maxNodes : the number nodes maximum (size of the matrix)
 *  isDirected : is the graph directed
 *
 * Return :
 *  error code 0 : create correctly executed
 *  error code 1 : create couldn't be executed
 *  error code 20 : function not yet implemented
 */
size_t create_matrix(Matrix *self, size_t maxNodes, bool isDirected);

/*
 * Function : deletion of a matrix
 *
 * Param :
 *  self : the matrix to delete
 *
 * Return :
 *  error code 0 : delete correctly executed
 *  error code 1 : delete couldn't be executed
 *  error code 20 : function not yet implemented
 */
size_t delete_matrix(Matrix *self);

/*
 * Function : creation of a predecessor matrix
 *
 * Param :
 *  self : the matrix to create
 *  predecessor : the predecessor matrix of self
 *
 * Return :
 *  error code 0 : predecessor correctly executed
 *  error code 1 : predecessor couldn't be executed
 *  error code 20 : function not yet implemented
 */
size_t create_predecessor(Matrix *self, Matrix *predecessor);

/*
 * Function : copy of a matrix
 *
 * Param :
 *  self : the destination matrix
 *  predecessor : the source matrix
 *
 * Return :
 *  error code 0 : predecessor correctly executed
 *  error code 1 : predecessor couldn't be executed
 *  error code 20 : function not yet implemented
 */
size_t copy_matrix(Matrix *src, Matrix *dst);

#endif //GRAPH_MATRIX_H
