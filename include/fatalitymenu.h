#ifndef MENU_H
#define MENU_H

#define MAX_PATH_LENGTH 256
#define MAX_DIGIT_LENGTH 10

#define LOG_ERROR_INT_CONVERT() LOG_ERROR("Can't convert your entry to a valid number\n")

#define GO_TO_GRAPH_MENU 0
#define QUIT 1

#include <libGraph.h>

// Main menu
void printMainMenu();
void startMenu(Graph *graph);
int readInputMainMenu(Graph *graph);

// common functions
int readUserInput(char *dest, int length);
void flushReadBuffer();

// read user inputs for action on graph
void goToGraphMenu();

#endif
