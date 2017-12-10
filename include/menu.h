#ifndef LIB_MENU_H
#define LIB_MENU_H

#include <graph.h>
#include <eulerian.h>

#define MAX_PATH_LENGTH 256
#define MAX_DIGIT_LENGTH 10

#define LOG_ERROR_INT_CONVERT() LOG_ERROR("Can't convert your entry to a valid number\n")

/* constants for user choice */
#define CREATE_EXAMPLE_GRAPH 0
#define CREATE_GRAPH 1
#define LOAD_FROM_FILE 2
#define DISPLAY_GRAPH 3
#define ADD_NODE 4
#define ADD_EDGE 5
#define DELETE_NODE 6
#define DELETE_EDGE 7
#define SAVE_GRAPH 8
#define DELETE_GRAPH 9
#define QUIT 10
#define COMPUTE_EULERIAN_CIRCUIT 11

/*************/
/* Main menu */
/*************/

/*
 * Function : Print the main menu in the terminal
 */
void printMainMenu();

/*
 * Function : Start the main menu and loop while the user didn't choice to quit
 *
 * Param :
 *  grap : the graph that will be manipulated
 */
void startMenu(Graph *graph);

/*
 * Function : Ask the user for action and read his input
 *
 * Param :
 *  graph : the graph to manipulate
 *
 * Return :
 *  code 0 : continue the programm
 *  code 1 : quit
 */
int readInputMainMenu(Graph *graph);

/********************/
/* common functions */
/********************/

/*
 * Function : Read the user input with some security checks
 *
 * Param :
 *  dest : the destination to store the user input
 *  length : the maximum char that the user can input
 *
 * Return :
 *  code 0 : the function successfully exited, the user input is in dest
 *  code 1 : can't read input from the terminal
 *  code 2 : Buffer overflow
 */
int readUserInput(char *dest, int length);

/*
 * Function : clear the input buffer
 */
void flushReadBuffer();

/****************************************/
/* read user inputs for action on graph */
/****************************************/

/*
 * Function : print all available example graph
 */
void printExampleGraphList();

/*
 * Function : ask the user for the example graph to create
 *
 * Param :
 *  graph : the structure where the example graph will be stored
 */
void readCreateExampleGraph(Graph *graph);

/*
 * Function : ask the user for informations to create a graph
 *
 * Param :
 *  graph : the structure where the created graph will be stored
 */
void readCreateGraph(Graph *graph);

/*
 * Function : ask the user the filename of the saved graph
 *
 * Param :
 *  graph : the structure that will store the loaded graph
 */
void askFileLocation(Graph *graph);

/*
 * Function : ask the user for the filename to store the given graph
 *
 * Param :
 *  graph : the graph to save in the file
 */
void askSaveLocation(Graph *graph);

/*
 * Function : ask the user for informations to add a node to the graph
 *
 * Param :
 *  graph : the graph that will contain the new node
 */
void readNewNode(Graph *graph);

/*
 * Function : ask the user for informations to create a new edge in the graph
 *
 * Param :
 *  graph : the graph where the new edge will be stored
 */
void readNewEdge(Graph *graph);

/*
 * Function : ask the user for informations to delete a node from the given graph
 *
 * Param :
 *  graph : the graph where the node will be deleted
 */
void readDeleteNode(Graph *graph);

/*
 * Function : ask the user for informations to delete an edge from the given graph
 *
 * Param :
 *  graph : the graph where the edge will be deleted
 */
void readDeleteEdge(Graph *graph);

/*****************************************/
/* read user inputs for eulerian circuit */
/*****************************************/

/*
 * Function : ask the user for informations to compute the eulerian trail in a given graph
 *
 * Param :
 *  graph : the graph on which to compute the eulerian trail
 */
void readEulerianCircuit(Graph *graph);

/*
 * Function : print choices for the heuristic choice if the graph isn't (half)eulerian
 *
 * Param :
 *  source : the source graph to duplicate
 *  destination : the destination graph to duplicate
 *
 * Return :
 *  error code 0 : copy correctly executed
 */
void printHeuristicChoice();

#endif
