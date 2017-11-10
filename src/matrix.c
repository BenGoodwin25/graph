#include <matrix.h>

size_t create_matrix(Matrix *self, size_t maxNodes, bool isDirected){
  self->maxNodes = maxNodes;
  self->isDirected = isDirected;
  self->neighbour = malloc(maxNodes*2*sizeof(ssize_t));

  self->neighbour = (ssize_t **)malloc(sizeof(ssize_t *)*self->maxNodes);
  self->neighbour[0] = (ssize_t *)malloc(sizeof(ssize_t)*self->maxNodes*self->maxNodes);


  if(self->neighbour == NULL){
    LOG_ERROR("Unexpected allocation error while creation of the matrix.\n");
    return 1;
  }

  for(size_t i=1; i < maxNodes; i++){
    self->neighbour[i]=self->neighbour[i-1]+maxNodes;
    if(self->neighbour[i] == NULL){
      LOG_ERROR("Unexpected allocation error while creation of the matrix.\n");
      return 1;
    }
  }

  for(size_t i=0; i < self->maxNodes; i++){
    for(size_t f=0; f < self->maxNodes; f++){
      self->neighbour[i][f] = -1;
    }
  }
  return 0;
}

size_t delete_matrix(Matrix *self){
  for(size_t i=0; i < self->maxNodes; i++){
    for(size_t f=0; f < self->maxNodes; f++){
      self->neighbour[i][f] = NULL;
    }
  }
  free(self->neighbour[0]);
  free(self->neighbour);
  return 20;
}

