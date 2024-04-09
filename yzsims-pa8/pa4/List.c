// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Name: Yazmyn Sims
// ID: yzsims
// Title: List.c
// Description: contains the List ADT (Programming Assignment 1)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -                               
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include <string.h>
// List - - - - - - - - - - - - - - - - - - - - - - - - - - - - - (X) 
//private Node type
typedef struct NodeObj* Node;

//private NodeObj type
typedef struct NodeObj{
	ListElement data;
	Node next;
	Node prev;
} NodeObj;

//private ListObj type
typedef struct ListObj
{
	Node front;
	Node back;
	Node curr;
	int length;
	int index;
} ListObj;

// Constructors & Destructors - - - - - - - - - - - - - - - - - - - (X)
// NewNode: returns reference to new Node object. INitializes next and data fields
Node newNode(ListElement data)
{
	Node N = malloc (sizeof(NodeObj));
	assert(N != NULL);

	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

//freeNode(): frees memory pointed to by *pN sets *pN to NULL
void freeNode(Node* pN)
{
	if (pN != NULL && *pN != NULL)
	{
		free(*pN);
		*pN = NULL;
	}
}

// newList(): returns reference to new empty List object 
List newList(void)
{
	List L = malloc(sizeof(ListObj));	//allocate memory space for List
	assert(L != NULL);		//Make sure L isn't NULL
	L->front = NULL;
	L->back = NULL;
	L->curr = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

//freeList(): frees all heap associated List pL and sets *pL to NULL
void freeList(List *pL)
{
	if(pL!=NULL && *pL!=NULL){
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

// Access Functios - - - - - - - - - - - - - - - - - - - - - - - - -
int length(List L)             // Returns the number of elements in L.
{
	assert(L != NULL);
	return(L->length);
}
int index(List L)              // Returns index of cursor element if defined, -1 otherwise.
{
	assert(L != NULL);
	return(L->index);
}
void* front(List L)              // Returns front element of L. Pre: length()>0
{
	//Check Precondition
	assert(L != NULL);
	if(length(L)<=0)
	{
		printf("List Error: calling front() on empty List reference\n");
		exit(EXIT_FAILURE);        
	}
	
	return(L->front->data);
}

void* back(List L)               // Returns back element of L. Pre: length()>0
{
	//Check Precondition
	assert(L != NULL);
        if(length(L)<=0)
        {
                printf("List Error: calling back() on empty List reference\n");
                exit(EXIT_FAILURE);
        }
	return(L->back->data);
}
void* get(List L)                // Returns cursor element of L. Pre: length()>0, index()>=0
{
	//Check Precondition
	assert(L != NULL);
        if(length(L)<=0)
        {
                printf("List Error: calling get() on empty List reference\n");
		exit(EXIT_FAILURE);
        }
	if(index(L) < 0)
	{
		printf("List Error: calling get() on undefined List reference\n");
		exit(EXIT_FAILURE);
	}
	return(L->curr->data);
}

//Manipulation procedures - - - - - - - - - - - - - - - - - - - - - - - - - -
void clear(List L) //resets L to original empty state
{
	assert(L != NULL);              //Make sure L isn't NULL
	while(length(L) > 0)
	{
		deleteFront(L);
	}
}

void set(List L, void* x) //OVerwrites the cursor element's data with x
{			//Pre: length() > 0, index() > 0
	//Precondition
	assert(L != NULL);
        if(length(L)<=0)
        {
                printf("List Error: calling set() on empty List reference\n");
                exit(EXIT_FAILURE);
        }
        if(index(L) < 0)
        {
                printf("List Error: calling set() on empty List reference\n");
                exit(EXIT_FAILURE);
        }
	
	L->curr->data = x;
}

void moveFront(List L) //If L is not empty, sets cursor under the front element
{
	assert(L != NULL);
	if (length(L)>0)
	{
		L->curr = L->front;
		L->index = 0;
	}
}

void moveBack(List L)
{
	assert(L != NULL);
	if (length(L)>0)
	{
		L->curr = L->back;
		L->index = length(L)-1; 
	}
}
void movePrev(List L)
{
	assert(L != NULL);
	if(index(L) >=0)	
	{
		L->curr = L->curr->prev;		
		L->index--;
	}	
}

void moveNext(List L)
{
	assert(L != NULL);
	if(index(L) >=0)
	{
		if(L->curr == L->back)
		{
			L->curr = NULL;
			L->index = -1;
		}
		else
		{
			L->curr = L->curr->next;
			L->index++;
		}
	}
}

void prepend(List L, void* x)
{
	assert(L != NULL);
	
	Node N = malloc(sizeof(NodeObj));
	N->data = x;
	N->prev = NULL;
	N->next = NULL;

	if (length(L) == 0)
	{
		L->front = N;
		L->back = N;
	}
	else 
	{
		N->next = L->front;
		L->front->prev = N;	//Come back 
		L->front = N;		//Ask about index
		
	}
	if (L->index != -1){L->index += 1;}	//ADDS CORRECTION (1)
	L->length++;
}

void append(List L, void* x)
{
	assert(L != NULL);

        Node N = malloc(sizeof(NodeObj));
        N->data = x;
        N->prev = NULL;
        N->next = NULL;

        if (length(L) == 0)
        {
                L->front = N;
                L->back = N;
        }
        else
        {
                N->prev = L->back;
                L->back->next = N;     //Come back
                L->back = N;

        }
        L->length++;

}

void insertBefore(List L, void* x)
{
	assert(L != NULL);
        if(length(L)<=0)
        {
                printf("List Error: calling insertBefore() on empty List reference\n");
                exit(EXIT_FAILURE);
        }
        if(index(L) < 0)
        {
                printf("List Error: calling insertBefore() on empty List reference\n");                
		exit(EXIT_FAILURE);
        }
	 
        Node N = malloc(sizeof(NodeObj));       //Create new Node
        N->data = x;
        N->prev = L->curr->prev;
        N->next= L-> curr;
	L->length += 1;	L->index += 1;	//ADDS A CORRECTION (2)
	if (L->curr->prev)
	{
		L->curr->prev->next = N;
	}
	else
	{
		L->front = N;
	}
	L->curr->prev = N;                    //REVIEW
	
}

void insertAfter(List L, void* x)
{
	assert(L != NULL);
        if(length(L)<=0)
        {
                printf("List Error: calling insertBefore() on empty List reference\n");
                exit(EXIT_FAILURE);
        }
        if(index(L) < 0)
        {
                printf("List Error: calling insertBefore() on empty List reference\n");
                exit(EXIT_FAILURE);
        }

        Node N = malloc(sizeof(NodeObj));       //Create new Node
        N->data = x;
        N->prev = L->curr;			
        N->next = L->curr->next; L->length += 1;
        if (L->curr->next)
        {
                L->curr->next->prev = N;
        }
        else
        {
                L->back = N;
        }
        L->curr->next = N;
}

void deleteFront(List L)
{
	assert(L != NULL);
	if(length(L)==0)
	{
		printf("List Error: calling insertBefore() on empty List reference\n");
		exit(EXIT_FAILURE);
	}

	if (length(L) > 0) {
		Node N = L->front;

		if (length(L) > 1) {
			L->front = N->next;
			L->front->prev = NULL;
		} else {
			L->front = L->back = NULL;
		}

		if (index(L) == 0) {
			L->curr = NULL;
			L->index = -1;
		} else if (index(L) > 0) {
			L->index--;
		}

		free(N);
		L->length--;
	}
}

void deleteBack(List L)
{
	assert(L != NULL);
	if(length(L)==0)
	{
		printf("List Error: calling insertBefore() on empty List reference\n");
		exit(EXIT_FAILURE);
	}

	if (length(L) > 0) {
		Node N = L->back;

		if (length(L) > 1) {
			L->back = N->prev;
			L->back->next = NULL;
		} else {
			L->front = L->back = NULL;
		}

		if (index(L) == length(L) - 1) {
			L->curr = NULL;
			L->index = -1;
		}

		free(N);
		L->length--;
	}
}

void delete(List L)
{
	assert(L != NULL);
        if(length(L)==0)
        {
                printf("List Error: calling insertBefore() on empty List reference\n");
                exit(EXIT_FAILURE);
        }
        if(index(L) < 0)
        {
                printf("List Error: calling insertBefore() on empty List reference\n");
                exit(EXIT_FAILURE);
        }
	Node beforeDeletion = L->curr-> prev;	//You can rename Nodes
	Node afterDeletion = L->curr->next;
	
	if(beforeDeletion != NULL)
	{
		beforeDeletion->next = afterDeletion;
	}
	else
	{
		L->front = afterDeletion;
	}
	
	if(afterDeletion != NULL)
	{
		afterDeletion->prev = beforeDeletion;
	}
	else
	{
		L->back = beforeDeletion;
	}
	L->length--;
	L->index = -1;
	free(L->curr);	//ADDS A CORRECTION (3)
	L->curr = NULL;	 
}
