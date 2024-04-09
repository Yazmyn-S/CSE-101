// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Name: Yazmyn Sims
// ID: yzsims
// Title: Graph.c
// Description: contains the Graph ADT (Programming Assignment 3)
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

List* adjList;	//Arr of Lists whose ith elemenet contains the neighbors of vertex i
char* color;	//array of chars whose ith elemeent is the color of vertex i 
int* parent;	//array of ints whose ith element is the parent of vertex i 
int* discover;
int* finish;	 
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
	G->discover = calloc(n + 1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));
	//initialize integer values of graph	
	G->order = n;
	G->size = 0;
	
	//for every vertex (i) in the graph create the following
	for(int i = 1; i <= n; i++)
	{
		G->adjList[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
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
        	free((*pG)->discover);
		free((*pG)->finish);

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

int getFinish(Graph G, int u)	//returns finish time of vertex u
{
	//precondition
	assert(G != NULL);
	if (1 > u || u > getOrder(G))
	{
		printf("Error: Tried to call GetFinish on out of bound.");
		exit(EXIT_FAILURE);
	}	
	return G->finish[u];
}

int getParent(Graph G, int u)	//returns parent of vertex u in DFS tree or NIL if DFS hasn't been called
{
	assert(G != NULL);
	return G->parent[u];
}

int getDiscover(Graph G, int u)	//returns discvery time of vertex u
{
	assert(G != NULL);
	//precondition 
	if(1 > u || u > getOrder(G))
        {
                printf("Error: Tried to call getPath when u is greater than getOrder and less than 1");
                exit(EXIT_FAILURE);
        }
	return G->discover[u];
}

//Manipulation procedures - - - - - - - - - - - - - - - - - -
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
	for(moveFront(L); index(L) != -1; moveNext(L))
	{
		if (get(L) == v)
		{
			return;
		}
		if (get(L) > v)
		{
			insertBefore(L,v);
			 G->size += 1;
			return;
		}
	}
	G->size += 1;
	append(L,v);
	
	/*append(G->adjList[u],v);
	G->size += 1;*/
}

void Visit(Graph G, int i, int* time, List S)
{
	G->discover[i] = ++(*time);
	G->color[i] = 'g';
	List children = G->adjList[i];
	for(moveFront(children); index(children) != -1; moveNext(children))
	{
		int child = get(children); 
		if(G->color[child] == 'w')
		{
			G->parent[child] = i;
			Visit(G, child, time, S);
		}	
	}
	G->color[i] = 'b';
        G->finish[i] = ++(*time);
	prepend(S,i);
}

void DFS(Graph G, List S)	//runs DFS algorithm on G with source s, setting the color distance parent and source fields of G
{
	assert(G != NULL);
	
	//precondition
	if(length(S) != getOrder(G))						//List S is filled in FindComponents before you call DFS
	{
		printf("Error: tried to call DFS with an out of range List.");	//List S should have all vertices in it when passed in (in order)
		exit(EXIT_FAILURE);
	}
	//initialize
	for (int i = 1; i <= getOrder(G); i++)
	{
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->finish[i] = UNDEF;
		G->discover[i] = UNDEF;
	}
	int time = 0;
	//recursively visit white
	for (moveFront(S); index(S) >= 0; moveNext(S))	//start with the first thing in S
	{					//change order you visit through vertices
		int i = get(S);
		if (G->color[i] == 'w')
		{
			Visit(G,i,&time, S);
		}
	}
	for (int i = 1; i <= getOrder(G); i++)
	{
		deleteBack(S);
	}
}
//Other operations - - - - - - - - - - - - - - - - - - (x)
Graph transpose(Graph G)	//returns a reference to a new graph object representing the transpose of G
{
	Graph transposed = newGraph(getOrder(G));	//copy graph
	for (int i = 1; i <= getOrder(G); i++)
	{	
		List children = G->adjList[i];
		for(moveFront(children); index(children) != -1; moveNext(children))
		{	
			int child = get(children);
			addArc(transposed, child, i);
		}
	}
	return transposed;		//note may need to reverse parents (DON"T REVERSE PARENTS. Just the edges.) 
}
Graph copyGraph(Graph G)	//returns a reference to a new graph that is a copy of G
{
	assert(G != NULL);
	Graph copy = newGraph(getOrder(G));          //create new Graph called copy
     	for (int i = 1; i <=getOrder(G); i++)
	{	
		List children = G->adjList[i];
		for(moveFront(children); index(children) != -1; moveNext(children))
		{	
			int child = get(children); 	//do we need to copy color, etc??? (JUst copy edges.)
			addArc(G, i, child);
		}
	}	
	copy->size = G->size;
	return copy;
}
void printGraph(FILE* out, Graph G)	//prints adjacency list representation of G to file 
{
	assert(G != NULL);
	if (out != NULL && G != NULL) {
        	for (int i = 1; i <= getOrder(G); i++) {
            		fprintf(out, "%d: ", i);
            		printList(out, G->adjList[i]);
        	}
    	}
}
