#include <matrix.h>

size_t create_matrix(Matrix *self, size_t maxNodes, bool isDirected){
  self->maxNodes = maxNodes;
  self->isDirected = isDirected;
  self->neighbour = malloc(maxNodes*sizeof(ssize_t));
  if(self->neighbour == NULL){
    LOG_ERROR("Unexpected allocation error while creation of the matrix.\n");
    return 1;
  }
  for(size_t i=0; i < maxNodes; i++){
    for(size_t f=0; f < maxNodes; f++){
      self->neighbour[i][f] = NULL;
    }
  }
  return 0;
}

size_t delete_matrix(Matrix *self){
  return 20;
}

