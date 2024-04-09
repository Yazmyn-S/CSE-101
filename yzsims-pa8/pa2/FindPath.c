// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Name: Yazmyn Sims
// ID: yzsims
// Title: FindPath.c
// Description: Implements the Graph ADT to find the shortest path between 2 vertices (Programming Assignment 2)
//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

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
	
	int n;
	fscanf(inFile, "%d", &n);
// Create a new graph
	Graph G = newGraph(n);
//initialize vertex u and vertex v and read them from the inputFile
	int u, v;
	fscanf(inFile, "%d %d", &u, &v);

// Read and store the graph from the inputFile
	while (u != 0 && v != 0) {
		addEdge(G, u, v);
    		fscanf(inFile, "%d %d", &u, &v);
	}

// Print the adjacency list representation of the graph
	printGraph(outputFile, G);
// Read source-destination pairs and perform BFS (REVIEW THIS CHUNK?????????)
	 while (fscanf(inFile, "%d %d", &u, &v) == 2 && u != 0 && v != 0) {
                fprintf(outputFile, "\n");
                BFS(G, u);
		if (getDist(G, v) == INF) {
                        fprintf(outputFile, "The distance from %d to %d is infinity\n", u, v);
                	fprintf(outputFile, "No %d-%d path exists\n", u, v);
		}
                else
                {
                        fprintf(outputFile, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
                	fprintf(outputFile, "A shortest %d-%d path is: ", u, v);
			List path = newList();
			getPath(path, G, v);
                        printList(outputFile, path);
                        freeList(&path);
                }
        //printf("1");
	//return 0;
	}
	/*
	while (fscanf(inFile, "%d %d", &u, &v) == 1 && u != 0 && v != 0) {
		fprintf(outputFile, "\n");
		BFS(G, u);
		if (getDist(G, v) == INF) {
			fprintf(outputFile, "No %d-%d path exists\n", u, v);
			fprintf(outputFile, "The distance from %d to %d is infinity\n", u, v);		
		}
		else 
		{
			fprintf(outputFile, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
                	fprintf(outputFile, "A shortest %d-%d path is: ", u, v);
			List path = newList();
			getPath(path, G, v);
			printList(outputFile, path);
			freeList(&path);
		}
	}*/

//Close input file for reading 
	fclose(inFile);
	fclose(outputFile);

//free Graph
	freeGraph(&G);
	return 0;	
}
