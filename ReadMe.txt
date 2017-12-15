makefile :
This file is used to build libs and main program.

mon.graph :
test file for opening and saving graph.

src/main.c :
Source file contaning the main function. It starts the menu.

src/menu.c include/menu.h :
Source files containing all functions to interact with the menu and call further libgraph's functions.

src/libgraph/graph.c include/graph.h :
Source files that contains graph's relative functions.

src/liblist/list.c include/list.h :
Source files that contains list's relative functions.

include/log.h :
Header file that contains small logs definitions.

src/matrix.c include/matrix.h :
Source files containing the matrix structure and the relatives functions

src/aulerian.c include/eulerian.h :
Source files that contains eulerian functions

src/eulerianlist.c include/eulerianlist.h :
Source files that contains structure for pairwise lists and there functions

include/eulerianpath.h :
Header file holding structure for the eulerian trail.

Build and Run :
make && ./bin/menu

More Informations :
This project contains multiple functions on graph such as :
- computing an Eulerian trail on an eulerian or half eulerian graph
- purpose a Chinese Postman trail with pairwise matching
- let you choose the heuristic to apply to compute the optimal pairwise matching
- create dot files while computing the eulerian trail to get a nice representation of graphs
- purpose multiple example graph on the option 0 of the main menu
