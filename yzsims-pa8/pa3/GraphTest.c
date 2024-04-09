// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Name: Yazmyn Sims
// ID: yzsims
// Title: GraphTest.c
// Description: test client for for Graph ADT (Programming Assignment 2)
//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[])
{
	//Create List
	List L = newList();	
	//create Graph with 6 vertiices
	Graph G = newGraph(6);
	addEdge(G, 1, 2);
	addEdge(G, 2, 3);
    	addEdge(G, 2, 4);
    	addEdge(G, 2, 5);
    	addEdge(G, 2, 6);
    	addEdge(G, 3, 4);
    	addEdge(G, 4, 5);
    	addEdge(G, 5, 6);

	printf("OG Graph:\n");
	printGraph(stdout,G);	

	//Use BFS with a source of 2
	DFS(G, L);	
	printf("\nDFS Graph:\n");
	printGraph(stdout, G);

	//Test Created Graphs
	printf("Graph Order: %d\n", getOrder(G));
	printf("Graph Size: %d\n", getSize(G));
	printf("Finish: %d\n", getFinish(G, 3));
	printf("Parent of 3: %d\n", getParent(G, 3));
	printf("Discover of 4: %d\n", getDiscover(G, 4));
	
	//free at the end
	freeGraph(&G);
	freeList(&L);
	printf((G == NULL)? "Graph is NULL\n" : "Graph NULL failed\n");

	//Transposed
	transpose(G);
	printf("\nTransposed Graph\n");
	printGraph(stdout,G);
}

//Output - - - - - - - - - - - - - - - - - 
/* 
 * OG Graph:
 * 1: 2 3 
 * 2: 4 5 6
 * 3: 1 4
 * 4: 2 3 5
 * 5: 2 4 6
 * 6: 2 5
 *
 * BFS Graph:
 * 1: 2 3
 * 2: 1 4 5 6
 * 3: 1 4
 * 5: 2 4 6
 * 6: 2 5
 * Graph Order: 6
 * Graph Size: 8
 * Source: 2
 * Parent of 3: 1
 * Distance of 4: 1
 * Path ??
 * 
 * Arc??
 *
 * NULL Graph:
 * 1:
 * 2:
 * 3:
 * 4:
 * 5:
 * 6:
 * "Graph is NULL"
 */

