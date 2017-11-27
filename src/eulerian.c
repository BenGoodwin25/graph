#include <eulerian.h>
#include <stdio.h>

size_t copyGraph(Graph *source, Graph *destination){
  delete_graph(destination);
  create_graph(destination, source->nbMaxNodes, source->isDirected);

  for (size_t i = 0; i < source->nbMaxNodes; i++) {
    if (is_node_exists(source, i)) {
      add_node(destination, i+1);
    }
  }

  for (size_t i = 0; i < source->nbMaxNodes; i++) {
    if (is_node_exists(source, i)) {
      Neighbour *tmp = source->adjList[i];
      while (tmp->neighbour != -1) {
        add_edge(destination, i+1, tmp->neighbour+1, tmp->edgeName, tmp->weight, true);
        tmp = tmp->nextNeighbour;
      }
    }
  }

  return 0;
}

void print_matrix(Matrix *self){
  printf("______________________________________________________\n");
  for(size_t i = 0; i < self->maxNodes; i++) {
    for(size_t j = 0; j < self->maxNodes; j++) {
      printf(" | %4zd", self->value[i][j]);
    }
    printf(" | \n");
  }
}

void convertToWeightMatrix(Graph *g, Matrix *weights) {
  for (size_t i = 0; i < g->nbMaxNodes; i++) {
    if(is_node_exists(g, i)){
      Neighbour *tmp = g->adjList[i];
      weights->value[i][i] = 0;
      while (tmp->neighbour != -1) {
        weights->value[i][tmp->neighbour] = tmp->weight;
        tmp = tmp->nextNeighbour;
      }
    }
  }
}

void convertToPredecessorMatrix(Graph *g, Matrix *predecessor) {
  for (size_t i = 0; i < g->nbMaxNodes; i++) {
    if(is_node_exists(g, i)){
      Neighbour *tmp = g->adjList[i];
      while (tmp->neighbour != -1) {
        predecessor->value[tmp->neighbour][i] = i;
        tmp = tmp->nextNeighbour;
      }
    }
  }
}

size_t Floyd_Warshall(Graph *g, Matrix *weights, Matrix *predecessor){
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
  create_matrix(weights, g->nbMaxNodes, g->isDirected);
  create_matrix(predecessor, g->nbMaxNodes, g->isDirected);
  convertToWeightMatrix(g, weights);
  convertToPredecessorMatrix(g, predecessor);
  for(size_t z = 0; z < weights->maxNodes; z++) {
    for(size_t x = 0; x < weights->maxNodes; x++) {
      for (size_t y = 0; y < weights->maxNodes; y++) {
        if(weights->value[x][z] != -1
            && weights->value[z][y] != -1
            && weights->value[x][z] + weights->value[z][y] < weights->value[x][y])
        {
          weights->value[x][y] = weights->value[x][z] + weights->value[z][y];
          predecessor->value[x][y] = z;
        }
      }
    }
  }
  /*
  EulerianPath path = {0};
  output_result(&path, stdout);
  //*/
  return 0;
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

void computeChineseCircuit(Graph *self, size_t heuristic) {
  // TODO: compute chinese circuit
  if (heuristic == 1) {
    // Floyd_Warshall
  }
}

void union_eulerelement(EulerianList *result, size_t element) {
  EulerianList *tmp = result;
  while(tmp->next != NULL) {
    tmp = tmp->next;
  }
  EulerianList *newElement = malloc(sizeof(EulerianList));
  newElement->node = element;
  newElement->weight = 0;
  newElement->next = NULL;
  tmp->next = newElement;
}

size_t size(EulerianList *list) {
  size_t count = 0;
  while (list->node != -1) {
    count++;
    list = list->next;
  }
  return count;
}

void union_eulerlist(EulerianList **dst, EulerianList *src) {
  if(*dst == NULL) {
    *dst = src;
    return;
  }
  EulerianList *destination = *dst;
  while (destination->node != src->node) {
    destination = destination->next;
  }
  EulerianList *tmp = destination->next;
  destination = src;
  while (src->next != NULL) {
    src = src->next;
  }
  src->next = tmp;
}

EulerianList* parse(Graph *graph, size_t x) {
  EulerianList *result = malloc(sizeof(EulerianList));
  result->node = x;
  result->weight = 0;
  result->next = NULL;
  size_t current = x;
  while (graph->adjList[current]->neighbour != -1) {
    Neighbour *n = graph->adjList[current];
    union_eulerelement(result, n->neighbour);
    current = n->neighbour;
    remove_edge(graph, n->edgeName);
  }
  EulerianList *tmp = result;
  while (tmp->next != NULL) {
    tmp = tmp->next;
    union_eulerlist(&result, parse(graph, tmp->node));
  }
  return result;
}

void rebuildPathWeight(Graph *graph, EulerianPath *path) {
  size_t totalWeight = 0;
  EulerianList *list = path->start;
  while(list->next != NULL) {
    Neighbour *n = graph->adjList[list->node];
    while (n->neighbour != list->next->node) {
      n = n->nextNeighbour;
    }
    list->weight = n->weight;
    totalWeight += list->weight;
    list = list->next;
  }
  path->totalWeight = totalWeight;
}

void buildEulerianPath(Graph *graph) {
  Graph copy = {0};
  EulerianPath result = {0};
  EulerianList *list = NULL;
  copyGraph(graph, &copy);
  // find the first odd degree node
  //
}

void buildEulerianCircuit(Graph *graph) {
  Graph copy = {0};
  EulerianPath result = {0};
  EulerianList *list = NULL;
  copyGraph(graph, &copy);
  for (size_t i = 0; i < copy.nbMaxNodes; i++) {
    if (copy.adjList[i]->neighbour != -1) {
      union_eulerlist(&list, parse(&copy, i));
    }
  }
  result.start = list;
  rebuildPathWeight(graph, &result);
  output_result(&result, stdout);
}

size_t getEulerianCircuit(Graph *self, size_t heuristic){
  /*FILE name;
  size_t error=0;
  error+=outputResultsToStream(self, &name);
  error+=displayResults(self);
  return error;*/
  size_t result = 10;
  isEulerian(self, &result);
  bool isHalfEulerian = false;
  switch (result) {
    case GRAPH_EULERIAN:
      printf("# The graph is eulerian.\n");
      break;
    case GRAPH_HALF_EULERIAN:
      printf("# The graph is half eulerian.\n");
      isHalfEulerian = true;
      break;
    case GRAPH_NON_EULERIAN:
      printf("# The graph isn't eulerian.\n");
      computeChineseCircuit(self, heuristic);
      break;
    default:
      break;
  }
  if (isHalfEulerian) {
    buildEulerianPath(self);
  } else {
    buildEulerianCircuit(self);
  }
  return 20;
}

size_t outputResultsToStream(size_t *self, FILE *stream){
  /*
  H(1) = 40 : 1 --(the predecessor matrix of self20)--> 2 --(10)--> 3 --(10)--> 4
  H(2) = 60 : 1 --(30)--> 3 --(10)--> 2 --(20)--> 4
  */
  return 20;
}

size_t displayResults(size_t *self) {
  /*
  if (Verify result have been calculated) {
    LOG_ERROR("result have to be calculated !\n");
    return 1;
  }
  return outputResultsToStream(self, stdout);
  //*/
  return 20;
}

void output_result(EulerianPath *path, FILE *stream) {
  fprintf(stream, "H(%d) = %zu : ", path->heuristicNumber, path->totalWeight);
  EulerianList *pathList = path->start;
  while(pathList->next != NULL) {
    fprintf(stream, "%zu --(%zu)--> ", pathList->node+1, pathList->weight);
    pathList = pathList->next;
  }
  fprintf(stream, "%zu\n", pathList->node+1);
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

size_t getNodeDegree(Neighbour *self) {
  size_t degree = 0;
  while (self->neighbour != -1) {
    degree++;
    self = self->nextNeighbour;
  }
  return degree;
}

size_t isEulerian(Graph *self, size_t *eulerianResult) {
  // Count for verticies with odd degrees
  size_t oddDegrees = 0;
  for (size_t i = 0; i < self->nbMaxNodes; i++) {
    if (getNodeDegree(self->adjList[i]) % 2 == 1) {
      oddDegrees++;
    }
  }

  if (oddDegrees > 2) {
    *eulerianResult = GRAPH_NON_EULERIAN;
    return 0;
  }

  *eulerianResult = ( oddDegrees == 0 ) ? GRAPH_EULERIAN : GRAPH_HALF_EULERIAN;
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
  add_edge(self, 1, 2, 0, 8, false);
  add_edge(self, 1, 3, 1, 3, false);
  add_edge(self, 2, 3, 2, 1, false);
  add_edge(self, 2, 4, 3, 9, false);
  add_edge(self, 2, 5, 4, 4, false);
  add_edge(self, 3, 4, 5, 10, false);
  add_edge(self, 3, 6, 6, 6, false);
  add_edge(self, 4, 5, 7, 1, false);
  add_edge(self, 4, 6, 8, 8, false);
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
  add_edge(self, 1, 3, 1, 4, false);
  add_edge(self, 1, 4, 2, 2, false);
  add_edge(self, 1, 9, 3, 8, false);
  add_edge(self, 2, 3, 4, 4, false);
  add_edge(self, 3, 6, 5, 1, false);
  add_edge(self, 3, 10, 6, 6, false);
  add_edge(self, 4, 5, 7, 2, false);
  add_edge(self, 4, 6, 8, 2, false);
  add_edge(self, 4, 7, 9, 1, false);
  add_edge(self, 5, 6, 10, 7, false);
  add_edge(self, 6, 8, 11, 9, false);
  add_edge(self, 7, 8, 12, 1, false);
  add_edge(self, 9, 10, 13, 3, false);
  printf("# Example eulerian graph created!\n");
}
