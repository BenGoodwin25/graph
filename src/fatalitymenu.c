#include "fatalitymenu.h"

void flushReadBuffer() {
  int c = 0;
  while ((c = getchar()) != '\n' && c != EOF) { }
}

void printMainMenu(){
  printf("\n");
  printf("#  %d : Open Graph menu\n", GO_TO_GRAPH_MENU);
  printf("#  %d : Quit\n", QUIT);
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
      case GO_TO_GRAPH_MENU:
        goToGraphMenu();
        break;
      case QUIT:
        return 1;
      default:
        fputs("# Please make a choice between 0 and 10\n", stdout);
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

void goToGraphMenu(){
  // TODO:
}
