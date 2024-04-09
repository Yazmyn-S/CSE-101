// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Name: Yazmyn Sims
// ID: yzsims
// Title: Graph.c
// Description: contains the Graph ADT (Programming Assignment 2)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Graph.h"
#include "List.h"
#include <string.h>
// Graph - - - - - - - - - - - - - - - - - - - - - - - - - - - - - (x)
//private GraphObj type
typedef struct GraphObj
{
int order;	//number of vertices
int size;	//number of edges
int source;	//label of the vertex that was most recently used as a source

List* adjList;	//Arr of Lists whose ith elemenet contains the neighbors of vertex i
char* color;	//array of chars whose ith elemeent is the color of vertex i 
int* parent;	//array of ints whose ith element is the parent of vertex i 
int* distance;	//array of ints whose ith element is the distance from the most recent source to vertex i 
} GraphObj;

// Constructors-Destructors - - - - - - - - - - - - - - - - - - - - - (x)
Graph newGraph(int n)	//returns Graph pointing to a newly created GraphObjr epresenting a graph having n vertices and no edges
{
	//Create and allocate memory for graph
	Graph G = malloc(sizeof(GraphObj));

	//Create and allocate memory for all parts of the grpah
	G->adjList = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(char));
	G->parent = calloc(n + 1, sizeof(int));
	G->distance = calloc(n + 1, sizeof(int));
	
	//initialize integer values of graph	
	G->order = n;
	G->size = 0;
	G->source = NIL;
	
	//for every vertex (i) in the graph create the following
	for(int i = 1; i <= n; i++)
	{
		G->adjList[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	return G;	//return Graph
}

void freeGraph(Graph* pG)	//frees all heap memory associated with Graph *pG then sets *pG to NULL
{
	//Make sure the graph exists
	if (pG != NULL && *pG != NULL) {
 
	       	//for every vertex (i) in Graph call freeList on all adjLists 
		for (int i = 1; i <= (*pG)->order; i++) {
            		freeList(&((*pG)->adjList[i]));
        	}
		//free all part of Graph
		free((*pG)->adjList);
        	free((*pG)->color);
        	free((*pG)->parent);
        	free((*pG)->distance);

        	//free the Graph itself and NULL it
		free(*pG);
        	*pG = NULL;
    }
}

//Access functions - - - - - - - - - - - - - - - - - - (x)
int getOrder(Graph G)	//returns order
{
	assert(G != NULL);
	return G->order;
}

int getSize(Graph G)	//returns size
{
	assert(G != NULL);
	return G->size;
}

int getSource(Graph G)	//returns source vertex mostly recently used in function BFS or NIL if BFS not yet called
{
	assert(G != NULL);	
	return G->source;
}

int getParent(Graph G, int u)	//returns parent of vertex u in BFS treeor NIL if BFS hasn't been called
{
	assert(G != NULL);
	//precondition
	if(1 > u || u > getOrder(G))
        {
                printf("Error: Tried to call getPath when u is greater than getOrder and less than 1");
                exit(EXIT_FAILURE);
        }
	//subtracts index by 1
	return G->parent[u]; 	//[]returns value at that index of an array, ->returns value at theat inde of a struct
}

int getDist(Graph G, int u)	//returns distance from most recent BFS source to vertex u or INF if BFS not yet called
{
	assert(G != NULL);
	//precondition 
	if(1 > u || u > getOrder(G))
        {
                printf("Error: Tried to call getPath when u is greater than getOrder and less than 1");
                exit(EXIT_FAILURE);
        }
	return G->distance[u];
}

void getPath(List L, Graph G, int u)	//appends to the List the vertices of a shortest path in G from source to u or appends NIL if no path exits  
{
	assert(G != NULL);
	//Precondition:
	if (getSource(G) == NIL)
	{
		printf("Error: Tried to call getPath when BFS hasn't been called.");
		exit(EXIT_FAILURE);
	}
	if(0 > u || u > getOrder(G))
	{
		printf("Error: Tried to call getPath when u is greater than getOrder and less than 1");
		exit(EXIT_FAILURE);
	}
	
	//Output
	if (u == NIL)
	{
		return;
	}
	if (G->color[u] == 'w')
	{
		append(L,NIL);
		return;
	}
	getPath(L, G, G->parent[u]);
	append(L,u);
	
	/*while (u != NIL)
	{
		prepend(L, u);
		u = G->parent[u];
	}*/
}

//Manipulation procedures - - - - - - - - - - - - - - - - - -
void makeNull(Graph G)	//deletes all edges of G (restores orginal state)
{
	assert(G != NULL);
	for (int i = 1; i <= getOrder(G); i++)
	{
		clear(G->adjList[i]);
		//G->color[i] = 'w'; 	//changed?
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	G->size = 0;
	//G->source = NIL;	
}

void addEdge(Graph G, int u, int v)	//inserts edge joining u and v
{					//u is added to v's adjacency list and vise versa (must maintain sorted order)
	assert(G != NULL);
	//precondtion:
        if(1 > u || u > getOrder(G) || 1 > v || v > getOrder(G))
        {
	         printf("Error tried to call addArc when either int u or v are out of range 1 to getOrder(G).");
	         exit(EXIT_FAILURE);
	}
	addArc(G,u,v);
	addArc(G,v,u);
	G->size -= 1;
}

void addArc(Graph G, int u, int v) //inserts a new directed edge from u to v
{				   // v is added to u's adjacency list only

	assert(G != NULL);
	//precondtion:
	if(1 > u || u > getOrder(G) || 1 > v || v > getOrder(G))
	{
		printf("Error tried to call addArc when either int u or v are out of range 1 to getOrder(G).");
		exit(EXIT_FAILURE);
	}
	List L = G->adjList[u];
	moveFront(L);
	while (index(L) != -1)
	{
		if (get(L) > v)
		{
			insertBefore(L,v);
			return;
		}
		moveNext(L);
	}
	append(L,v);
	G->size += 1;
	
	/*append(G->adjList[u],v);
	G->size += 1;*/
}

void BFS(Graph G, int s)	//runs BFS algorithm on G with source s, setting the color distance parent and source fields of G
{
	assert(G != NULL);
	//precondition
	if(1 > s || s > getOrder(G))
	{
		printf("Error: tried to call GFS with an out of range source.");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i < getOrder(G); i++)
	{
		G->color[i] = 'w';
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = 'g';
	G->distance[s] = 0;
	List q = newList();
	append(q,s);
	while (length(q) != 0)
	{
		int x = back(q);
		deleteBack(q);
		for(moveFront(G->adjList[x]); index(G->adjList[x]) != -1; moveNext(G->adjList[x] ))
		{
			int y = get(G->adjList[x]);
			if(G->color[y] == 'w')
			{
				G->color[y] = 'g';
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				prepend(q,y);
			}
		}
		G->color[x] = 'b';
	}
	G->source = s;
	freeList(&q);
}
//Other operations - - - - - - - - - - - - - - - - - - (x)
void printGraph(FILE* out, Graph G)	//prints adjacency list representation of G to file 
{
	assert(G != NULL);
	if (out != NULL && G != NULL) {
        	for (int i = 1; i <= getOrder(G); i++) {
            		fprintf(out, "%d:", i);
            		printList(out, G->adjList[i]);
        	}
    	}
}
