#include <graph.h>


int main() {
  Graph source = {0};
  load_graph(&source,"./mon.graph");
  Graph destination = {0};
  int errorCode = copyGraph(&source,&destination);
  view_graph(&source);
  printf("Error code of copy : %d\n",errorCode);
  view_graph(&destination);


  Matrix m;
  create_matrix(&m,4,false);
  //m.neighbour[2][2]=7;
  delete_matrix(&m);
  //assert(m.neighbour[2][2] == 7);

  return errorCode;
}

