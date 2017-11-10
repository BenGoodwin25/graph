#include <graph.h>

size_t copyGraph(Graph *source, Graph **destination){
  int error;
  error = save_graph(&source, "tmpGraph");
  error += load_graph(&destination,"tmpGraph");
  return error;
}

size_t Floyd_Warshall(Graph *g, Matrix **self, Matrix **predecessor){
  /*
  for each node z ∈ V do
    for each node x ∈ V do
      for each node y ∈ V do
        if M(x, z) 6= +∞ and M(z, y) 6= +∞ and M(x, z) + M(z, y) < M(x, y)
          M(x, y) ← M(x, z) + M(z, y);
          P rec(x, y) ← P rec(z, y);
      end for each
    end for each
  end for each
  */
  return 20;
}