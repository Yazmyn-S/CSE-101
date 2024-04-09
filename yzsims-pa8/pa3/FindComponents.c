// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Name: Yazmyn Sims
// ID: yzsims
// Title: FindComponent.c
// Description: Implements the Graph ADT to find strong components of Graph G (Programming Assignment 3)
//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LENGTH 300

int main(int argc, char* argv[]) {
//Check command line arguments
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        	exit(EXIT_FAILURE);
	}

// Open input file for reading
	FILE* inFile = fopen(argv[1], "r");
	if (inFile == NULL) {
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}

// Open the output file for writing
	FILE *outputFile = fopen(argv[2], "w");
	if (outputFile == NULL) {
		fprintf(stderr, "Error: Unable to open output file %s\n", argv[2]);
		fclose(inFile);  // Close the input file before exiting
		exit(EXIT_FAILURE);
	}
	fprintf(outputFile, "1");
	int n;
	fscanf(inFile, "%d", &n);

// Create a new graph
	Graph G = newGraph(n);

//initialize vertex u and vertex v and read them from the inputFile
	int u, v;
	fscanf(inFile, "%d %d", &u, &v);

//Print Adjacency List
	 while (u != 0 && v != 0) {
        	addArc(G, u, v);
        	fscanf(inFile, "%d %d", &u, &v);
    	}
	fprintf(outputFile, "Adjacency list representation of G:\n");
    	printGraph(outputFile, G);

//Create List that's length will equal GetOrder(G)
	List newL = newList();
	int num_arcs = getOrder(G);		//Example:
	for (int i = 1; i <= num_arcs; i++)	//Graph has 8 vertices
	{	
		append(newL, i);		//newL (1,2,3,4,5,6,7,8)
	}
	DFS(G, newL);				//runs DFS on List vertices in order
	Graph T = transpose(G);			// get Graph Transpose
	DFS (T, newL);				// runs DFS on list backwards

	int count = 0;

//Count number of strong components
	for(int i = 1; i <= getOrder(G); i++)
	{
		if(getParent(T,i) == NIL)
		{
			count++;
		}
	printf("parent of %d is %d\n", i, getParent(T, i));
	}
	fprintf(outputFile, "G contains %d strongly conected components:\n", count);

// temp list will hold 1 set of strong components at a time, clearing between each one
List Temp = newList();
for (int i = 1; i <= getOrder(G); i++)
{
	int current_parent = 0;
	int current = 0;
 	fprintf(outputFile, "Component %d: ", i);
	
	/*do{
		printList(stdout, newL);
		moveBack(newL);
		current = get(newL);
		current_parent = getParent(T,i);	
		prepend(Temp, current);
		deleteBack(newL);
	}while(current_parent != NIL);
	printList(outputFile, Temp);
	clear(Temp);
	*/	
}

//Close input file for reading 
	fclose(inFile);
	fclose(outputFile);

//free Graph
	freeGraph(&T);
	freeGraph(&G);
	freeList(&newL);
	freeList(&Temp);
	return 0;
}
