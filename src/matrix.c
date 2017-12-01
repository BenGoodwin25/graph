#include <matrix.h>
#include <limits.h>

size_t create_matrix(Matrix *self, size_t maxNodes, bool isDirected){
  // init basic vars
  self->maxNodes = maxNodes;
  self->isDirected = isDirected;

  // init memory for columns
  self->value = malloc(maxNodes*sizeof(ssize_t*));
  if(self->value == NULL){
    LOG_ERROR("Unexpected allocation error while creation of the matrix.\n");
    return 1;
  }

  // init memory for rows
  for (size_t i = 0; i < maxNodes; i++) {
    self->value[i] = malloc(maxNodes*sizeof(ssize_t));
  }
  for(size_t i = 1; i < maxNodes; i++){
    if(self->value[i] == NULL){
      LOG_ERROR("Unexpected allocation error while creation of the matrix.\n");
      return 1;
    }
  }

  for(size_t i = 0; i < self->maxNodes; i++){
    for(size_t f = 0; f < self->maxNodes; f++){
      self->value[i][f] = INT_MAX;
    }
  }
  return 0;
}

size_t delete_matrix(Matrix *self){
  for(size_t i=0; i < self->maxNodes; i++){
    for(size_t f=0; f < self->maxNodes; f++){
      self->value[i][f] = -1;
    }
  }
  free(self->value[0]);
  free(self->value);
  return 0;
}

size_t copy_matrix(Matrix *src, Matrix *dst) {
  for (size_t i = 0; i < src->maxNodes; i++) {
    for (size_t j = 0; j < src->maxNodes; j++) {
      dst->value[i][j] = src->value[i][j];
    }
  }
  return 0;
}
