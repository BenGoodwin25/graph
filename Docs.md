Chinese Postman :

- Enumerate all the possible pairwise matching of the odd degrees nodes
 
- Compute the shortest distance between any of the two nodes (e-g algo of Floyd Warshall)
 
- Compute the cost of each pairwise matching and return the best one
 
- Duplicate for each pair (x,y) of this best matching the edges that are on the shortest path from x to y
 
- Compute on Euleran circuit in the now Eulerian augmented Graph


/*
 * Function : function utility
 *
 * Param :
 *  param1 : param utility
 *  param2 : param utility
 *
 * Return :
 *  error code 0 : create correctly executed
 *  error code 1 : create couldn't be executed
 *  error code 20 : function not yet implemented
 */