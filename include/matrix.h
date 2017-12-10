#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <graph.h>
#include <log.h>

/*
 * the structure that represent a matrix
 * maxNodes : the size of the matrix
 * value : 2D array contaning values
 */
typedef struct _matrix{
  size_t maxNodes;
  int **value;
} Matrix;

/*
 * Function : creation of a matrix
 *
 * Param :
 *  self : the matrix to create
 *  maxNodes : the number nodes maximum (size of the matrix)
 *
 * Return :
 *  error code 0 : create correctly executed
 *  error code 1 : create couldn't be executed
 */
size_t create_matrix(Matrix *self, size_t maxNodes);

/*
 * Function : deletion of a matrix
 *
 * Param :
 *  self : the matrix to delete
 *
 * Return :
 *  error code 0 : delete correctly executed
 */
size_t delete_matrix(Matrix *self);

/*
 * Function : copy of a matrix
 *
 * Param :
 *  self : the destination matrix
 *  predecessor : the source matrix
 *
 * Return :
 *  error code 0 : predecessor correctly executed
 */
size_t copy_matrix(Matrix *src, Matrix *dst);

#endif //GRAPH_MATRIX_H
