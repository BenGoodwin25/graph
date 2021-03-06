#include <menu.h>
#include <limits.h>

void flushReadBuffer() {
  int c = 0;
  while ((c = getchar()) != '\n' && c != EOF) { }
}

void printMainMenu(){
  printf("\n");
  printf("#  %d : Create Example Graph\n", CREATE_EXAMPLE_GRAPH);
  printf("#  %d : Create Graph\n", CREATE_GRAPH);
  printf("#  %d : Load Graph from file\n", LOAD_FROM_FILE);
  printf("#  %d : Display Graph\n", DISPLAY_GRAPH);
  printf("#  %d : Add Node\n", ADD_NODE);
  printf("#  %d : Add Edge\n", ADD_EDGE);
  printf("#  %d : Delete Node\n", DELETE_NODE);
  printf("#  %d : Delete Edge\n", DELETE_EDGE);
  printf("#  %d : Save Graph to file\n", SAVE_GRAPH);
  printf("#  %d : Delete Graph\n", DELETE_GRAPH);
  printf("#  %d : Quit (and delete Graph)\n", QUIT);
  printf("# ===============================\n");
  printf("#  %d : Compute Eulerian Circuit\n", COMPUTE_EULERIAN_CIRCUIT);
  printf("\n");
}

void startMenu(Graph *graph){
  int quit = 0;
  while(quit == 0){
    printMainMenu();
    quit = readInputMainMenu(graph);
  }
}

int readInputMainMenu(Graph *graph){
  char inputString[4];
  int choice = -1;
  printf("Choice ");
  readUserInput(inputString, 4);
  printf("\n");
  if(sscanf(inputString, "%d", &choice) == 1){
    switch(choice){
      case CREATE_EXAMPLE_GRAPH:
        readCreateExampleGraph(graph);
        break;
      case CREATE_GRAPH:
        readCreateGraph(graph);
        break;
      case LOAD_FROM_FILE:
        askFileLocation(graph);
        break;
      case DISPLAY_GRAPH:
        printf("# Graph :\n");
        view_graph(graph);
        printf("\n");
        break;
      case ADD_NODE:
        readNewNode(graph);
        break;
      case ADD_EDGE:
        readNewEdge(graph);
        break;
      case DELETE_NODE:
        readDeleteNode(graph);
        break;
      case DELETE_EDGE:
        readDeleteEdge(graph);
        break;
      case SAVE_GRAPH:
        askSaveLocation(graph);
        break;
      case DELETE_GRAPH:
        delete_graph(graph);
        printf("# Graph deleted!\n");
        break;
      case QUIT:
        delete_graph(graph);
        return 1;
        break;
      case COMPUTE_EULERIAN_CIRCUIT:
        if (graph->nbMaxNodes == 0) {
          printf("# Please, create a connected graph.\n");
          return 0;
        }
        readEulerianCircuit(graph);
        break;
      default:
        fputs("# Please make a choice between 0 and 11\n", stdout);
        break;
    }
  } else {
    fputs("# Please, enter a valide number\n", stdout);
  }
  return 0;
}

int readUserInput(char *dest, int length){
  char *backspacePos = NULL;
  printf("> ");
  if(fgets(dest, length, stdin) != NULL){
    backspacePos = strchr(dest, '\n');
    if(backspacePos != NULL){
      *backspacePos = '\0';
    } else {
      flushReadBuffer();
      dest[0] = '\0';
      LOG_WARN("Overflow, entry must be less than %d character long.\n", length-1);
      return 2;
    }
    return 0;
  } else {
    flushReadBuffer();
    return 1;
  }
}

void printExampleGraphList() {
  printf("# 1 : Non eulerian graph.\n");
  printf("# 2 : Half eulerian graph.\n");
  printf("# 3 : Eulerian graph.\n");
  printf("# 4 : Big non eulerian graph.\n");
}

void readCreateExampleGraph(Graph *graph) {
  int choice;
  char choiceInput[MAX_DIGIT_LENGTH];

  printf("# Enter a choice :\n");
  printExampleGraphList();
  while(readUserInput(choiceInput, MAX_DIGIT_LENGTH+1) != 0){}
  if(sscanf(choiceInput, "%d", &choice) == 1) {
    if (choice > 4 || choice < 0) {
      LOG_ERROR("Can't determine which default graph do you want to create.\n");
      return;
    }
    switch (choice) {
      case 1:
        createExampleNonEulerian(graph);
        break;
      case 2:
        createExampleHalfEulerian(graph);
        break;
      case 3:
        createExampleEulerian(graph);
        break;
      case 4:
        createExampleDoubleNonEulerian(graph);
      default:
        break;
    }
  } else {
    LOG_ERROR_INT_CONVERT();
  }
}

void readCreateGraph(Graph *graph){
  int maxNodes;
  char maxNodeInput[MAX_DIGIT_LENGTH];
  char directedInput[2];
  bool isDirected;

  if(graph->nbMaxNodes > 0){
    delete_graph(graph);
  }

  printf("# Enter the maximum number of nodes :\n");
  while(readUserInput(maxNodeInput, MAX_DIGIT_LENGTH+1) != 0){}
  if(sscanf(maxNodeInput, "%d", &maxNodes) == 1){
    printf("# Is the graph symmetric ? (y/n)\n");
    while(readUserInput(directedInput, 3)!=0){}
    if(directedInput[0] == 'y'){
      isDirected = true;
    } else if(directedInput[0] == 'n') {
      isDirected = false;
    } else {
        LOG_ERROR("Can't determine by your entry if it's directed or not.\n");
        return;
    }
    if(create_graph(graph, maxNodes, isDirected) == 0){
      printf("# Graph succefully created!\n");
    } else {
      LOG_ERROR("Error while creating the graph.\n");
      printf("# Graph wasn't created.\n");
    }
  } else {
    LOG_ERROR_INT_CONVERT();
  }
}

void askFileLocation(Graph *graph){
  char filePathInput[MAX_PATH_LENGTH];
  int error = -1;
  while(error != 0){
    printf("# Which file should be loaded ?\n");
    error = readUserInput(filePathInput, MAX_PATH_LENGTH+1);
  }
  if(load_graph(graph, filePathInput) == 0){
    printf("# Graph successfully loaded\n");
  }
}

void askSaveLocation(Graph *graph){
  char filePathInput[MAX_PATH_LENGTH];
  int error = -1;
  while(error != 0){
    printf("# Where graph should be saved ?\n");
    error = readUserInput(filePathInput, MAX_PATH_LENGTH+1);
  }
  if(save_graph(graph, filePathInput) == 0){
    printf("# Graph successfully saved\n");
  } else {
    printf("# Graph wasn't saved\n");
  }
}

void readNewNode(Graph *graph){
  char nodeNameInput[MAX_DIGIT_LENGTH];
  int nodeName = -1;
  int error = -1;
  while(error != 0){
    printf("# Enter the name of the node :\n");
    error = readUserInput(nodeNameInput, MAX_DIGIT_LENGTH+1);
  }
  if(sscanf(nodeNameInput, "%d", &nodeName) != 1){
    LOG_ERROR_INT_CONVERT();
    printf("# Can't create Node\n");
    return;
  }
  if(add_node(graph, nodeName) == 0){
    printf("# Node successfully added\n");
  } else {
    printf("# Node wasn't added\n");
  }
}

void readNewEdge(Graph *graph){
  char userInput[MAX_DIGIT_LENGTH];
  int fromNode = -1;
  int toNode = -1;
  int edgeName = -1;
  char symmetricInput[2];
  bool isSymmetric = false;

  printf("# Enter the start point of the edge :\n");
  readUserInput(userInput, MAX_DIGIT_LENGTH+1);
  if(sscanf(userInput, "%d", &fromNode) != 1){
    LOG_ERROR_INT_CONVERT();
    printf("# Can't create the edge\n");
    return;
  }
  printf("# Enter the end point of the edge :\n");
  readUserInput(userInput, MAX_DIGIT_LENGTH+1);
  if(sscanf(userInput, "%d", &toNode) != 1){
    LOG_ERROR_INT_CONVERT();
    printf("# Can't create the edge\n");
    return;
  }
  printf("# Enter the edge name :\n");
  readUserInput(userInput, MAX_DIGIT_LENGTH+1);
  if(sscanf(userInput, "%d", &edgeName) != 1){
    LOG_ERROR_INT_CONVERT();
    printf("# Can't create the edge\n");
    return;
  }
  if(graph->isDirected) {
    printf("# Is the edge symmetric ? (y/n)\n");
    readUserInput(symmetricInput, 3);
    if(symmetricInput[0] == 'y'){
      isSymmetric = true;
    } else if(symmetricInput[0] == 'n') {
      isSymmetric = false;
    } else {
        LOG_ERROR("Can't determine by your entry if it's symmetric or not.\n");
        printf("# Edge wasn't added\n");
        return;
    }
  }
  if(add_edge(graph, fromNode, toNode, edgeName, 0, isSymmetric) == 0) {
    printf("# Edge successfully added\n");
  } else {
    printf("# Edge wasn't added\n");
  }
}

void readDeleteNode(Graph *graph) {
  char nodeNameInput[MAX_DIGIT_LENGTH];
  int nodeName = -1;
  int error = -1;
  while(error != 0){
    printf("# Enter the name of the node to delete :\n");
    error = readUserInput(nodeNameInput, MAX_DIGIT_LENGTH+1);
  }
  if(sscanf(nodeNameInput, "%d", &nodeName) != 1){
    LOG_ERROR_INT_CONVERT();
    printf("# Can't delete Node\n");
    return;
  }
  if(remove_node(graph, nodeName) == 0){
    printf("# Node successfully deleted\n");
  } else {
    printf("# Graph wasn't modified\n");
  }
}

void readDeleteEdge(Graph *graph){
  char edgeNameInput[MAX_DIGIT_LENGTH];
  int edgeName = -1;
  int error = -1;
  while(error != 0){
    printf("# Enter the name of the edge to delete :\n");
    error = readUserInput(edgeNameInput, MAX_DIGIT_LENGTH+1);
  }
  if(sscanf(edgeNameInput, "%d", &edgeName) != 1){
    LOG_ERROR_INT_CONVERT();
    printf("# Can't delete Edge\n");
    return;
  }
  if(remove_edge(graph, edgeName) == 0){
    printf("# Edge successfully deleted\n");
  } else {
    printf("# Graph wasn't modified\n");
  }
}

void readEulerianCircuit(Graph *graph) {
  char heuristicInput[MAX_DIGIT_LENGTH];
  char nbPassInput[MAX_DIGIT_LENGTH];
  int heuristic = INT_MAX;
  size_t nbPass = 0;
  int error = -1;
  size_t result = 10;
  isEulerian(graph, &result);
  switch (result) {
    case GRAPH_EULERIAN:
      printf("# The graph is eulerian.\n");
      break;
    case GRAPH_HALF_EULERIAN:
      printf("# The graph is half eulerian.\n");
      break;
    case GRAPH_NON_EULERIAN: {
        printf("# The graph isn't eulerian.\n");
        while(error != 0) {
          printHeuristicChoice();
          error = readUserInput(heuristicInput, MAX_DIGIT_LENGTH+1);
        }
        if(sscanf(heuristicInput, "%d", &heuristic) != 1){
          LOG_ERROR_INT_CONVERT();
          printf("# Can't determine which heuristic to use.\n");
          return;
        }
        if (heuristic == HEURISTIC_MULTIPLE_RANDOM || heuristic == HEURISTIC_ALL) {
          error = -1;
          while(error != 0) {
            printf("# How many pass do you want to apply for multiple random heuristic ?\n");
            error = readUserInput(nbPassInput, MAX_DIGIT_LENGTH+1);
          }
          if(sscanf(nbPassInput, "%zu", &nbPass) != 1){
            LOG_ERROR_INT_CONVERT();
            printf("# Can't determine how much pass you want to apply.\n");
            return;
          }
        }
      }
      break;
    default:
      break;
  }
  getEulerianCircuit(graph, heuristic, result, nbPass);
}

void printHeuristicChoice() {
  printf("# Which heuristic do you want to use ?\n");
  printf("# %d : Use successfully each heuristic.\n", HEURISTIC_ALL);
  printf("# %d : Simple pass random heuristic.\n", HEURISTIC_SIMPLE_RANDOM);
  printf("# %d : Multiple pass random heuristic.\n", HEURISTIC_MULTIPLE_RANDOM);
  printf("# %d : Reject max heuristic.\n", HEURISTIC_EXCLUDE_MAX);
  printf("# %d : No heuristic (Warning : it can takes a lot of time).\n", HEURISTIC_NONE);
}
