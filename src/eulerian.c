#include <eulerian.h>

size_t copyGraph(Graph *source, Graph *destination){
  size_t error;
  error = save_graph(source, "tmpGraph");
  error += load_graph(destination,"tmpGraph");
  unlink("tmpGraph");
  return error;
}

void print_matrix(Matrix *self){
  printf("%zu maxNodes\n", self->maxNodes);
  for(size_t i = 0; i < self->maxNodes; i++) {
    for(size_t j = 0; j < self->maxNodes; j++) {
      printf("|%zd", self->value[i][j]);
    }
    printf("|\n");
  }
}

size_t Floyd_Warshall(Graph *g, Matrix *self, Matrix *predecessor){
  /*
  for each node z ∈ V {
    for each node x ∈ V {
      for each node y ∈ V {
        if self(x, z) != +∞ and self(z, y) != +∞ and self(x, z) + self(z, y) < self(x, y) {
          self(x, y) ← self(x, z) + self(z, y);
          predecessor(x, y) ← predecessor(z, y);
        }
      }
    }
  }
  */
  print_matrix(self);
  print_matrix(predecessor);
  for(size_t i = 0; i < self->maxNodes; i++) {
    for(size_t j = 0; j < self->maxNodes; j++) {
      for (size_t k = 0; k < self->maxNodes; k++) {
        if(self->value[j][i] != -1 && self->value[i][k] != -1 && self->value[j][i] + self->value[i][k] < self->value[j][k]) {
          self->value[j][k] = self->value[j][i] + self->value[i][k];
          predecessor->value[j][k] = predecessor->value[i][k];
        }
      }
    }
  }
  print_matrix(self);
  print_matrix(predecessor);
  return 20;
}

size_t minLengthPairwise(size_t *V, List *bestMatching, List *bestMatchingWeight){
  /*
  bestMatching ← NULL;
  bestMatchingWeight ← +∞;

  LPM ← ∅;
  LPM ← listPairs(V, ∅, LPM);

  foreach (pairwise matching PM of LPM) {
    if (weight(PM) < bestMatchingWeight) {
      bestMatching ← PM;
      bestMatchingWeight ← weigth(PM);
    }
  }
   */
  return 20;
}


size_t listPairs(size_t *V, List *currentListOfPairs, List *listsOfPairs){
  /*
  if (V = ∅){
    listsOfPairs ← listsOfPairs+currentListOfPairs;
  } else {
    x ← min(V );
    foreach (y ∈ V such that x < y) {
      listPairs(V − {x, y}, currentListOfPairs+(x, y), listsOfPairs);
    }
  }
  return listsOfPairs;
  */
  return 20;
}

size_t getEulerianCircuit(Graph *self, size_t h){
  /*FILE name;
  size_t error=0;
  error+=outputResultsToStream(self, &name);
  error+=displayResults(self);
  return error;*/
  return 20;
};

size_t outputResultsToStream(size_t *self, FILE *stream){
  /*
  H(1) = 40 : 1 --(20)--> 2 --(10)--> 3 --(10)--> 4
  H(2) = 60 : 1 --(30)--> 3 --(10)--> 2 --(20)--> 4
  */
  return 20;
}

size_t displayResults(size_t *self) {
  /*if (Verify result have been calculated) {
    LOG_ERROR("result have to be calculated !\n");
    return 1;
  }
  return outputResultsToStream(self, stdout);*/
  return 20;
}