#include <matrix.h>

size_t create_matrix(Matrix *self, size_t maxNodes, bool isDirected){
  self->maxNodes = maxNodes;
  self->isDirected = isDirected;
  self->value = malloc(maxNodes*2*sizeof(ssize_t));

  self->value = (ssize_t **)malloc(sizeof(ssize_t *)*self->maxNodes);
  self->value[0] = (ssize_t *)malloc(sizeof(ssize_t)*self->maxNodes*self->maxNodes);


  if(self->value == NULL){
    LOG_ERROR("Unexpected allocation error while creation of the matrix.\n");
    return 1;
  }

  for(size_t i=1; i < maxNodes; i++){
    self->value[i]=self->value[i-1]+maxNodes;
    if(self->value[i] == NULL){
      LOG_ERROR("Unexpected allocation error while creation of the matrix.\n");
      return 1;
    }
  }

  for(size_t i=0; i < self->maxNodes; i++){
    for(size_t f=0; f < self->maxNodes; f++){
      self->value[i][f] = -1;
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
  return 20;
}