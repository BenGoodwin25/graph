#include <graph.h>
#include <menu.h>
#include <eulerian.h>

/*
int main() {
  Graph source = {0};
  load_graph(&source,"./mon.graph");
  Graph destination = {0};
  int errorCode = copyGraph(&source,&destination);
  LOG_INFO("Error code of copy : %d\n",errorCode);
  view_graph(&destination);
  Matrix m;
  create_matrix(&m,4,false);
  m.neighbour[2][2]=7;
  LOG_INFO("before delete : %zu\n",m.neighbour[2][2]);
  delete_matrix(&m);
  assert(m.neighbour[2][2] == -1);


  delete_graph(&source);
  delete_graph(&destination);

  return 0;
}
//*/

/*
int main() {
  Graph graph = {0};
  startMenu(&graph);
  return 0;
}
//*/

/*
int main() {
  Graph graph = {0};
  createExampleNonEulerian(&graph);
  Matrix *m0 = malloc(sizeof(Matrix));
  Matrix *m1 = malloc(sizeof(Matrix));
  create_matrix(m0, graph.nbMaxNodes, graph.isDirected);
  create_matrix(m1, graph.nbMaxNodes, graph.isDirected);
  Floyd_Warshall(&graph, m0, m1);
}
//*/

//*
int main() {
  Graph graph = {0};
  createExampleHalfEulerian(&graph);
  getEulerianCircuit(&graph, 1);
}
//*/
