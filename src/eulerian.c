#include <eulerian.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

/*****************************************/
/** INTERNAL FILE FUNCTIONS DECLARATION **/
/*****************************************/

size_t getNodeDegree(Neighbour *self);
void print_matrix(Matrix *self);
void convertToWeightMatrix(Graph *g, Matrix *weights);
void convertToPredecessorMatrix(Graph *g, Matrix *predecessors);
void graphToEulerianGraph(Graph *self, size_t heuristic, size_t nbPass);
void duplicateEdgesFromPairwiseList(Graph *self, List *bestMatching, Matrix *predecessors);
void union_eulerelement(EulerianList *result, size_t element);
void union_eulerlist(EulerianList **dst, EulerianList *src);
size_t size(EulerianList *list);
size_t getPMWeight(List *pm, Matrix *weights);
int getMaxEdgeName(Graph *self);
EulerianList* parse(Graph *graph, size_t x);
void rebuildPathWeight(Graph *graph, EulerianPath *path);
void buildEulerianWay(Graph *graph, size_t heuristicNumber, bool isHalfEulerian);
void deleteMatrix(Matrix *self);

/**********************/
/** PUBLIC FUNCTIONS **/
/**********************/

size_t copyGraph(Graph *source, Graph *destination){
  delete_graph(destination);
  create_graph(destination, source->nbMaxNodes, source->isDirected);

  for (size_t i = 0; i < source->nbMaxNodes; i++) {
    if (is_node_exists(source, i)) {
      add_node(destination, i+1);
    }
  }

  List *edgesDone = NULL;
  for (size_t i = 0; i < source->nbMaxNodes; i++) {
    if (is_node_exists(source, i)) {
      Neighbour *tmp = source->adjList[i];
      while (tmp->neighbour != -1) {
        if (!isInList(edgesDone, tmp->edgeName)) {
          add_edge(destination, i+1, tmp->neighbour+1, tmp->edgeName, tmp->weight, true);
          addToList(&edgesDone, tmp->edgeName);
        }
        tmp = tmp->nextNeighbour;
      }
    }
  }

  return 0;
}

size_t Floyd_Warshall(Graph *g, Matrix *weights, Matrix *predecessors){
  // Initialize our matricies
  create_matrix(weights, g->nbMaxNodes);
  create_matrix(predecessors, g->nbMaxNodes);
  convertToWeightMatrix(g, weights);
  convertToPredecessorMatrix(g, predecessors);

  // Then apply the Floyd-Warshall algorithm
  for(size_t z = 0; z < weights->maxNodes; z++) {
    for(size_t x = 0; x < weights->maxNodes; x++) {
      for (size_t y = 0; y < weights->maxNodes; y++) {
        if(weights->value[x][z] != INT_MAX
            && weights->value[z][y] != INT_MAX
            && weights->value[x][z] + weights->value[z][y] < weights->value[x][y])
        {
          weights->value[x][y] = weights->value[x][z] + weights->value[z][y];
          predecessors->value[x][y] = predecessors->value[z][y];
        }
      }
    }
  }

  return 0;
}

size_t minLengthPairwise(List *V, List **bestMatching, size_t *bestMatchingWeight, Matrix *weights, size_t heuristic, size_t nbPass){
  *bestMatching = NULL;
  *bestMatchingWeight = INT_MAX;

  LList *lpm = NULL;
  srand(time(NULL));
  if (heuristic == HEURISTIC_SIMPLE_RANDOM) {
    lpm = listPairsSimpleRandom(V, NULL, lpm);
  } else if (heuristic == HEURISTIC_MULTIPLE_RANDOM) {
    lpm = listPairsMultipleRandom(V, NULL, lpm, nbPass);
  } else if (heuristic == HEURISTIC_EXCLUDE_MAX) {
    lpm = listPairsExcludeMax(V, NULL, lpm, weights);
  } else {
    lpm = listPairsNoHeuristic(V, NULL, lpm);
  }

  LList *tmplpm = lpm;
  while(tmplpm != NULL) {
    List *pm = tmplpm->list;
    size_t pmWeight = getPMWeight(pm, weights);
    if (pmWeight < *bestMatchingWeight) {
      *bestMatching = pm;
      *bestMatchingWeight = pmWeight;
    }
    tmplpm = tmplpm->next;
  }
  return 0;
}

LList * listPairsSimpleRandom(List *V, List *currentListOfPairs, LList *listsOfPairs){
  if (V == NULL) {
    addListToLists(&listsOfPairs, currentListOfPairs);
  } else {
    List *x = V;
    size_t vSize = getListSize(V);
    List *y = x->next;
    if (vSize > 2) {
      double random = (double)rand() / (double)RAND_MAX;
      size_t pairWithElement = (size_t)(random * vSize);
      for(size_t cpt = 1; cpt < pairWithElement; cpt++) {
        y = y->next;
      }
    }
    List *lv = NULL;
    cloneList(V, &lv);
    deletePair(&lv, x->value, y->value);
    List *clop = NULL;
    cloneList(currentListOfPairs, &clop);
    addPair(&clop, x->value, y->value);
    listsOfPairs = listPairsSimpleRandom(lv, clop, listsOfPairs);
  }
  return listsOfPairs;
}

LList * listPairsMultipleRandom(List *V, List *currentListOfPairs, LList *listsOfPairs, size_t nbPass){
  for (size_t i = 0; i < nbPass; i++) {
    listsOfPairs = listPairsSimpleRandom(V, currentListOfPairs, listsOfPairs);
  }
  return listsOfPairs;
}

LList * listPairsExcludeMax(List *V, List *currentListOfPairs, LList *listsOfPairs, Matrix *weights){
  if (V == NULL) {
    addListToLists(&listsOfPairs, currentListOfPairs);
  } else {
    List *x = V;
    List *lMin = NULL;
    ssize_t minWeight = INT_MAX;
    for (List *y = x->next; y != NULL && x->value < y->value; y = y->next) {
      if (weights->value[x->value][y->value] < minWeight) {
        lMin = y;
        minWeight = weights->value[x->value][y->value];
      }
    }
    List *lv = NULL;
    cloneList(V, &lv);
    deletePair(&lv, x->value, lMin->value);
    List *clop = NULL;
    cloneList(currentListOfPairs, &clop);
    addPair(&clop, x->value, lMin->value);
    listsOfPairs = listPairsExcludeMax(lv, clop, listsOfPairs, weights);
  }
  return listsOfPairs;
}

LList * listPairsNoHeuristic(List *V, List *currentListOfPairs, LList *listsOfPairs){
  if (V == NULL) {
    addListToLists(&listsOfPairs, currentListOfPairs);
  } else {
    List *x = V;
    for (List *y = x->next; y != NULL && x->value < y->value; y = y->next) {
      List *lv = NULL;
      cloneList(V, &lv);
      deletePair(&lv, x->value, y->value);
      List *clop = NULL;
      cloneList(currentListOfPairs, &clop);
      addPair(&clop, x->value, y->value);
      listsOfPairs = listPairsNoHeuristic(lv, clop, listsOfPairs);
    }
  }
  return listsOfPairs;
}

size_t getEulerianCircuit(Graph *self, size_t heuristic, size_t eulerianState, size_t nbPass){
  unlink("eulerianResults.txt");
  if (heuristic == HEURISTIC_ALL) {
    for (size_t i = 1; i < HEURISTIC_NONE; i++) {
      Graph copy = {0};
      copyGraph(self, &copy);
      if (eulerianState == GRAPH_NON_EULERIAN) {
        graphToEulerianGraph(&copy, i, nbPass);
      }
      buildEulerianWay(&copy, i, eulerianState == GRAPH_HALF_EULERIAN);
      delete_graph(&copy);
    }
  } else {
    Graph copy = {0};
    copyGraph(self, &copy);
    if (eulerianState == GRAPH_NON_EULERIAN) {
      graphToEulerianGraph(&copy, heuristic, nbPass);
    }
    buildEulerianWay(&copy, heuristic, eulerianState == GRAPH_HALF_EULERIAN);
    delete_graph(&copy);
  }
  printf("# Eulerian result(s) saved in file named 'eulerianResults.txt'\n");
  return 0;
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
  create_graph(self, 24, false);
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

  add_node(self, 13);
  add_node(self, 14);
  add_node(self, 15);
  add_node(self, 16);
  add_node(self, 17);
  add_node(self, 18);
  add_node(self, 19);
  add_node(self, 20);
  add_node(self, 21);
  add_node(self, 22);
  add_node(self, 23);
  add_node(self, 24);

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


  add_edge(self, 12, 13, 42, 1, false);

  add_edge(self, 12+1, 12+2, 17+0, 1, false);
  add_edge(self, 12+1, 12+3, 17+1, 1, false);
  add_edge(self, 12+2, 12+3, 17+2, 5, false);
  add_edge(self, 12+2, 12+4, 17+3, 2, false);
  add_edge(self, 12+3, 12+4, 17+4, 1, false);
  add_edge(self, 12+4, 12+5, 17+5, 2, false);
  add_edge(self, 12+5, 12+6, 17+6, 2, false);
  add_edge(self, 12+5, 12+7, 17+7, 3, false);
  add_edge(self, 12+6, 12+7, 17+8, 15, false);
  add_edge(self, 12+6, 12+8, 17+9, 1, false);
  add_edge(self, 12+7, 12+8, 17+10, 3, false);
  add_edge(self, 12+8, 12+9, 17+11, 1, false);
  add_edge(self, 12+9, 12+10, 17+12, 1, false);
  add_edge(self, 12+9, 12+11, 17+13, 5, false);
  add_edge(self, 12+10, 12+11, 17+14, 50, false);
  add_edge(self, 12+10, 12+12, 17+15, 2, false);
  add_edge(self, 12+11, 12+12, 17+16, 3, false);

  printf("# Example non eulerian graph created!\n");
}

void createExampleDoubleNonEulerian(Graph *self) {
  create_graph(self, 24, false);
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

  add_node(self, 13);
  add_node(self, 14);
  add_node(self, 15);
  add_node(self, 16);
  add_node(self, 17);
  add_node(self, 18);
  add_node(self, 19);
  add_node(self, 20);
  add_node(self, 21);
  add_node(self, 22);
  add_node(self, 23);
  add_node(self, 24);

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


  add_edge(self, 12, 13, 42, 1, false);

  add_edge(self, 12+1, 12+2, 17+0, 1, false);
  add_edge(self, 12+1, 12+3, 17+1, 1, false);
  add_edge(self, 12+2, 12+3, 17+2, 5, false);
  add_edge(self, 12+2, 12+4, 17+3, 2, false);
  add_edge(self, 12+3, 12+4, 17+4, 1, false);
  add_edge(self, 12+4, 12+5, 17+5, 2, false);
  add_edge(self, 12+5, 12+6, 17+6, 2, false);
  add_edge(self, 12+5, 12+7, 17+7, 3, false);
  add_edge(self, 12+6, 12+7, 17+8, 15, false);
  add_edge(self, 12+6, 12+8, 17+9, 1, false);
  add_edge(self, 12+7, 12+8, 17+10, 3, false);
  add_edge(self, 12+8, 12+9, 17+11, 1, false);
  add_edge(self, 12+9, 12+10, 17+12, 1, false);
  add_edge(self, 12+9, 12+11, 17+13, 5, false);
  add_edge(self, 12+10, 12+11, 17+14, 50, false);
  add_edge(self, 12+10, 12+12, 17+15, 2, false);
  add_edge(self, 12+11, 12+12, 17+16, 3, false);

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

void output_result(EulerianPath *path, FILE *stream) {
  fprintf(stream, "H(%d) = %zu : ", path->heuristicNumber, path->totalWeight);
  EulerianList *pathList = path->start;
  while(pathList->next != NULL) {
    fprintf(stream, "%zu --(%zu)--> ", pathList->node+1, pathList->weight);
    pathList = pathList->next;
  }
  fprintf(stream, "%zu\n", pathList->node+1);
}

/****************************/
/** PRIVATE FILE FUNCTIONS **/
/****************************/

size_t getNodeDegree(Neighbour *self) {
  size_t degree = 0;
  while (self->neighbour != -1) {
    degree++;
    self = self->nextNeighbour;
  }
  return degree;
}

void print_matrix(Matrix *self){
  printf("______________________________________________________\n");
  for(size_t i = 0; i < self->maxNodes; i++) {
    for(size_t j = 0; j < self->maxNodes; j++) {
      printf(" | %11d", self->value[i][j]);
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

void convertToPredecessorMatrix(Graph *g, Matrix *predecessors) {
  for (size_t i = 0; i < g->nbMaxNodes; i++) {
    if(is_node_exists(g, i)){
      Neighbour *tmp = g->adjList[i];
      while (tmp->neighbour != -1) {
        predecessors->value[i][tmp->neighbour] = i;
        tmp = tmp->nextNeighbour;
      }
    }
  }
}

void graphToEulerianGraph(Graph *self, size_t heuristic, size_t nbPass) {
  // find all odd degree nodes :
  List *oddDegreeNodes = NULL;
  for (size_t i = 0; i < self->nbMaxNodes; i++) {
    if (getNodeDegree(self->adjList[i]) % 2 == 1) {
      addToList(&oddDegreeNodes, i);
    }
  }

  //compute all shortest path
  Matrix *shortest = malloc(sizeof(Matrix));
  Matrix *predecessors = malloc(sizeof(Matrix));
  Floyd_Warshall(self, shortest, predecessors);

  // get all costs of each pairwise matching for odd degree nodes
  List *bestMatching;
  size_t bestMWeight;
  minLengthPairwise(oddDegreeNodes, &bestMatching, &bestMWeight, shortest, heuristic, nbPass);
  duplicateEdgesFromPairwiseList(self, bestMatching, predecessors);

  delete_matrix(shortest);
  delete_matrix(predecessors);
}

void duplicateEdgesFromPairwiseList(Graph *self, List *bestMatching, Matrix *predecessors) {
  while (bestMatching != NULL) {
    size_t start = bestMatching->value;
    size_t end = bestMatching->next->value;
    int edgeName = getMaxEdgeName(self);

    while (end != start) {
      Neighbour *n = self->adjList[predecessors->value[start][end]];
      while (n->neighbour != end) {
        n = n->nextNeighbour;
      }
      add_edge(self, predecessors->value[start][end]+1, end+1, ++edgeName, n->weight, true);
      end = predecessors->value[start][end];
    }

    bestMatching = bestMatching->next->next;
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

size_t size(EulerianList *list) {
  size_t count = 0;
  while (list->node != -1) {
    count++;
    list = list->next;
  }
  return count;
}

size_t getPMWeight(List *pm, Matrix *weights) {
  size_t totalWeight = 0;
  while (pm != NULL) {
    totalWeight += weights->value[pm->value][pm->next->value];
    pm = pm->next->next;
  }
  return totalWeight;
}

int getMaxEdgeName(Graph *self) {
  int maxEdgeName = -1;
  for (size_t i = 0; i < self->nbMaxNodes; i++) {
    Neighbour *n = self->adjList[i];
    while (n->neighbour != -1) {
      maxEdgeName = n->edgeName > maxEdgeName ? n->edgeName : maxEdgeName;
      n = n->nextNeighbour;
    }
  }
  return maxEdgeName;
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

void buildEulerianWay(Graph *graph, size_t heuristicNumber, bool isHalfEulerian) {
  Graph copy = {0};
  EulerianPath result = {0};
  EulerianList *list = NULL;
  copyGraph(graph, &copy);
  // if the graph is half eulerian, then start the path from an odd degree node
  if (isHalfEulerian) {
    // find the first odd degree node
    size_t oddNode = 0;
    while (getNodeDegree(graph->adjList[oddNode]) % 2 == 0) {
      oddNode++;
    }
    union_eulerlist(&list, parse(&copy, oddNode));
  }
  for (size_t i = 0; i < copy.nbMaxNodes; i++) {
    if (copy.adjList[i]->neighbour != -1) {
      union_eulerlist(&list, parse(&copy, i));
    }
  }
  result.start = list;
  result.heuristicNumber = heuristicNumber;
  rebuildPathWeight(graph, &result);
  // output result to stdout
  output_result(&result, stdout);
  // output result to file
  FILE *file = fopen("eulerianResults.txt", "a");
  if(!file){
    LOG_ERROR("Can't open or create the file eulerianResults.txt.\n");
    LOG_INFO("Results weren't saved");
    return;
  }
  output_result(&result, file);
  fclose(file);
}

void deleteMatrix(Matrix *self){
  for (size_t i = 0; i < self->maxNodes; i++) {
    free(self->value[i]);
  }
  free(self->value);
  free(self);
}
