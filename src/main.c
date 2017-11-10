#include <graph.h>

int main() {
  Graph source = {0};
  load_graph(&source,"./mon.graph");
  Graph destination = {0};
  int errorCode = copyGraph(&source,&destination);
  view_graph(&source);
  printf("Error code of copy : %d\n",errorCode);
  view_graph(&destination);
  return errorCode;
}

