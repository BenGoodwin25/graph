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
        if(self->value[j][i] != -1
            && self->value[i][k] != -1
            && self->value[j][i] + self->value[i][k] < self->value[j][k])
        {
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

size_t getEulerianCircuit(Graph *self, int heuristic){
  /*FILE name;
  size_t error=0;
  error+=outputResultsToStream(self, &name);
  error+=displayResults(self);
  return error;*/
  size_t result = 10;
  isEulerian(self, &result);
  switch (result) {
    case GRAPH_EULERIAN:
      printf("# The graph is eulerian.\n");
      break;
    case GRAPH_HALF_EULERIAN:
      printf("# The graph is half eulerian.\n");
      break;
    case GRAPH_NON_EULERIAN:
      printf("# The graph isn't eulerian.\n");
      break;
    default:
      break;
  }
  if(heuristic == 0 ) {
    // TODO: Do all heuristics
  }
  /*
  if(heuristic == 1) {
    Matrix *m0 = malloc(sizeof(Matrix));
    Matrix *m1 = malloc(sizeof(Matrix));
    create_matrix(m0, self->nbMaxNodes, self->isDirected);
    create_matrix(m1, self->nbMaxNodes, self->isDirected);
    Floyd_Warshall(self, m0, m1);
  }
  */
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

void checkVisited(Graph *graph, size_t v, bool visited[]) {
  visited[v] = true;
  Neighbour *tmp = graph->adjList[v];
  while (tmp->neighbour != -1) {
    if (!visited[tmp->neighbour]) {
      checkVisited(graph, tmp->neighbour, visited);
    }
    tmp = tmp->nextNeighbour;
  }
}

size_t isConnected(Graph *self, bool *connectedResult) {
  // Create a tab of boolean to check if all verticies are visited
  bool visited[self->nbMaxNodes];
  for (size_t i = 0; i < self->nbMaxNodes; i++) {
    visited[i] = false;
  }

  // Find a not connected node
  size_t node;
  for (node = 0; node < self->nbMaxNodes; node++) {
    if(self->adjList[node]->neighbour != -1) {
      break;
    }
  }

  // if there is no edges in the graph
  if (node == self->nbMaxNodes) {
    *connectedResult = true;
    return 0;
  }

  // Go throught all edges to check that each nodes are visited
  checkVisited(self, node, visited);

  // Check if there is a not connected node in the graph
  for (size_t i = 0; i < self->nbMaxNodes; i++) {
    if (visited[i] == false && self->adjList[i]->neighbour != -1) {
      *connectedResult = false;
      return 0;
    }
  }

  *connectedResult = true;
  return 0;
}

size_t getNodeDegree(Neighbour *self) {
  size_t degree = 0;
  while (self->neighbour != -1) {
    degree++;
    self = self->nextNeighbour;
  }
  return degree;
}

size_t isEulerian(Graph *self, size_t *eulerianResult) {
  // if the graph isn't connected, then the graph isn't eulerian
  bool connectedResult = false;
  isConnected(self, &connectedResult);
  if (connectedResult == false) {
    *eulerianResult = 2;
    return 0;
  }

  // Count for verticies with odd degrees
  size_t oddDegrees = 0;
  for (size_t i = 0; i < self->nbMaxNodes; i++) {
    if (getNodeDegree(self->adjList[i]) % 2 == 1) {
      oddDegrees++;
    }
  }

  if (oddDegrees > 2) {
    *eulerianResult = 2;
    return 0;
  }

  *eulerianResult = ( oddDegrees == 0 ) ? 0 : 1;
  return 0;
}

void createExampleNonEulerian(Graph *self) {
  create_graph(self, 12, false);
  add_node(self, 1);
  add_node(self, 2);
  add_node(self, 3);
  add_node(self, 4);
  add_node(self, 5);
  add_node(self, 6);
  add_node(self, 7);
  add_node(self, 8);
  add_node(self, 9);
  add_node(self, 10);
  add_node(self, 11);
  add_node(self, 12);
  add_edge(self, 1, 2, 0, 1, false);
  add_edge(self, 1, 3, 1, 1, false);
  add_edge(self, 2, 3, 2, 5, false);
  add_edge(self, 2, 4, 3, 2, false);
  add_edge(self, 3, 4, 4, 1, false);
  add_edge(self, 4, 5, 5, 2, false);
  add_edge(self, 5, 6, 6, 2, false);
  add_edge(self, 5, 7, 7, 3, false);
  add_edge(self, 6, 7, 8, 15, false);
  add_edge(self, 6, 8, 9, 1, false);
  add_edge(self, 7, 8, 10, 3, false);
  add_edge(self, 8, 9, 11, 1, false);
  add_edge(self, 9, 10, 12, 1, false);
  add_edge(self, 9, 11, 13, 5, false);
  add_edge(self, 10, 11, 14, 50, false);
  add_edge(self, 10, 12, 15, 2, false);
  add_edge(self, 11, 12, 16, 3, false);
  printf("# Example non eulerian graph created!\n");
}

void createExampleHalfEulerian(Graph *self) {
  create_graph(self, 6, false);
  add_node(self, 1);
  add_node(self, 2);
  add_node(self, 3);
  add_node(self, 4);
  add_node(self, 5);
  add_node(self, 6);
  add_edge(self, 1, 2, 0, 1, false);
  add_edge(self, 1, 3, 1, 1, false);
  add_edge(self, 2, 3, 2, 1, false);
  add_edge(self, 2, 4, 3, 1, false);
  add_edge(self, 2, 5, 4, 1, false);
  add_edge(self, 3, 4, 5, 1, false);
  add_edge(self, 3, 6, 6, 1, false);
  add_edge(self, 4, 5, 7, 1, false);
  add_edge(self, 4, 6, 8, 1, false);
  add_edge(self, 5, 6, 9, 1, false);
  printf("# Example half eulerian graph created!\n");
}

void createExampleEulerian(Graph *self) {
  create_graph(self, 10, false);
  add_node(self, 1);
  add_node(self, 2);
  add_node(self, 3);
  add_node(self, 4);
  add_node(self, 5);
  add_node(self, 6);
  add_node(self, 7);
  add_node(self, 8);
  add_node(self, 9);
  add_node(self, 10);
  add_edge(self, 1, 2, 0, 1, false);
  add_edge(self, 1, 3, 1, 1, false);
  add_edge(self, 1, 4, 2, 1, false);
  add_edge(self, 1, 9, 3, 1, false);
  add_edge(self, 2, 3, 4, 1, false);
  add_edge(self, 3, 6, 5, 1, false);
  add_edge(self, 3, 10, 6, 1, false);
  add_edge(self, 4, 5, 7, 1, false);
  add_edge(self, 4, 6, 8, 1, false);
  add_edge(self, 4, 7, 9, 1, false);
  add_edge(self, 5, 6, 10, 1, false);
  add_edge(self, 6, 8, 11, 1, false);
  add_edge(self, 7, 8, 12, 1, false);
  add_edge(self, 9, 10, 13, 1, false);
  printf("# Example eulerian graph created!\n");
}
