// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Name: Yazmyn Sims
// ID: yzsims
// Title: ListTest.c 
// Description: test clieny for for List ADT (Programming Assignment 1)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"


int main(int argc, char* argv[])
{
	//Create some tests Lists
	int i;
	List N = NULL;					//NULL List
	List E = newList();				//Empty List (this should test for length and index)
	List F [] = newList();				//Full List
	List F2 = [] = newList();			//Used to test equal
	List F3 = [] = newList();			//Used to test equal

	for (i = 1, i<= 20; i++)
	{
		prepend(F,i);
		append(F2,i);
		append(N,i);
		prepend(N,i);
	}
	//Run every functions with every type of List
	prepend(List N, int x);
      

        append(List N, int x);
         printList(N);
        append(List E, int x);
        append(List F, int x);
/*
        insertBefore(List N, int x)
         printList(N);;
        insertBefore(List E, int x);
        insertBefore(List F, int x);

        insertAfter(List N, int x);
         printList(N);
        insertAfter(List E, int x);
        insertAfter(List F, int x);

		             
	 printList(newList);	//Not sure what the List is called here???	

	freeList(List N* pL);        // Frees all heap memory associated with *pL, sets *pL to NULL.
	 printList(N);
	free List(List E* pL);
	free List(List F*, pL);
	
	length(List N);
	 printList(N);
	length(List E);
	length(List F);

	index(List N);
	 printList(N); 
	index(List E);
	index(List F);

	front(List N);
	 printList(N);
	front(List E);
	front(List F);
	
	back(List N); 
	 printList(N);
	back(List E); 
	back(List F); 
	
	get(List N); 
	 printList(N);
	get(List E); 
	get(List F); 

	equals(List F, List F2);
	equals(List F2, List F3);
	equals(List F, List E);
	equals(List F, List N);
	 printList(N);	

	clear(List N);
	 printList(N);
	clear(List E);
	clear(List F);
	
	
	
	set(List N, int x);
	 printList(N);
	set(List E, int x);
	set(List F, int x);

	moveFront(List N);
	 printList(N); 
	moveFront(List E); 
	moveFront(List F); 

	moveBack(List N);
	 printList(N); 
	moveBack(List E); 
	moveBack(List F); 

	movePrev(List N);
	 printList(N); 
	movePrev(List E); 
	movePrev(List F); 

	moveNext(List N);
	 printList(N);
	moveNext(List E);
	moveNext(List F);

	deleteFront(List N);
	 printList(N);
	deleteFront(List E);
	deleteFront(List F);

	deleteBack(List N);
	 printList(N);
	deleteBack(List E);
	deleteBack(List F);

	delete(List N);
	 printList(N);
	delete(List E);
	delete(List F);

	copyList(List N);
	 printList(N);
	copyList(List E);
	copyList(List F);
		
	concatList(List F, List F3);
	concatList(List F, List E);
	concatList(List F, List N);
	 printList(N);
*/		
/*Output Should be the following:	
*	[]
*	NULL Test (I used assert for NULL so I don't think it prints anyhing) 
*	
*
*	N
*
*
*	N
*
*
*	N
*	
*	
*	N
*
*
*	N
*
*
*	
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*/	

}
