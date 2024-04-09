// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Name: Yazmyn Sims
// ID: yzsims
// Title: Matrix.c
// Description: contains the Matrix ADT (Programming Assignment 4)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
//Matrix - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -(x)
typedef struct MatrixObj {
	List* row;
        int entry_count;
	int size;
} MatrixObj;

//Entry- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -(x)
typedef struct EntryObj {
        double data;
        int col;
} EntryObj;
// Constructors - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -(x)
Entry newEntry(int column, double data)
{
	Entry E = calloc(1,sizeof(EntryObj));
	assert (E != NULL);
	E->col = column;
	E->data = data;
	
	return E;
}

Matrix newMatrix(int n) {			 //Returns a reference to a new nXn Matrix object in the zero state.
// Allocate memory for the matrix data (array of arrays)
	Matrix M = malloc(sizeof(MatrixObj));
        M->row = calloc(n+1, sizeof(List));
        assert(M != NULL);
// Initialize matrix elements to zero
	for(int i = 1; i <= n; i++)
	{
		M->row[i] = newList();
	}
        M->size = n;
	M->entry_count = 0;
	return M;
}

//Destructor - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -(x)
void freeEntry(Entry* pE)
{
	if(pE != NULL && *pE != NULL)
	{
		free(*pE);
		*pE = NULL;
	}
}

void freeMatrix(Matrix* pM)	//Frees heap memory associated with *pM, sets *pM to NULL.
{
//Free memory for all matrix data in matrix 
	if (pM != NULL && *pM != NULL) {
		for (int i = 1; i <= size((*pM)); i++) {
			List L = (*pM)->row[i];
			for(moveFront(L); index(L) > -1; moveNext(L))
			{
				Entry x = get(L);
				freeEntry(&x);
			}
			freeList(&(*pM)->row[i]);
		}
//free everything else
		free((*pM)->row);		
//Free Matrix and set to NULL
		free(*pM);
		*pM = NULL;
	}
}
// Access functions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - (x)
int size(Matrix M) 		//Return the size of square Matrix M.
{
	assert(M != NULL);
	return M->size;
}
int NNZ(Matrix M)		// Return the number of non-zero elements in M.
{
	assert(M != NULL);
	return M->entry_count;	
}
int equals(Matrix A, Matrix B)	//Return true (1) if matrices A and B are equal, false (0) otherwise.
{
	assert(A != NULL);
	assert(B != NULL);
	if(size(A) != size(B) || A->entry_count != B->entry_count)
	{
		return 0;
	}
	Matrix CA = copy(A);
	Matrix CB = copy(B);
//iterate through rows	
	for(int y = 1; y <= size(CA); y++)
	{
		if(length(CA->row[y]) == 0 || length(CB->row[y]) == 0){
			if(length(CA->row[y]) != 0 || length(CB->row[y]) != 0){
				return 0;
			}
		}
		else{
			moveFront(CA->row[y]);
			moveFront(CB->row[y]);
			if (length(CA->row[y]) != length(CB->row[y])){return 0;}
		}
//iterate through the entries
		Entry CA_entry, CB_entry;
		
		for(int j = 1; j <= length(CA->row[j]); j++)
		{
			CA_entry = get(CA->row[j]);
			CB_entry = get(CB->row[j]);
		}
		if(CB_entry->data != CA_entry->data)
		{
			return 0;
		}
	}
	freeMatrix(&CA);
	freeMatrix(&CB);
	return 1;
}

// Manipulation procedures - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - (x)
void makeZero(Matrix M) 	//Re-sets M to the zero Matrix state
{
	assert(M != NULL);
// Iterate through each element and set it to zero
	if (size(M) == 0){return;}
	for(int x = 1; x <= size(M); x++)
	{
        	clear(M ->row[x]);
    	}

	// make the entries 0
	M->entry_count = 0;

}

//Changes the ithA_entry
void changeEntry(Matrix M, int i, int j, double x)	//Time: O(a)
{
//Precondition Check
	assert(M != NULL);
	if ( i < 1 || i > size(M))
	{
		printf("Error: tried to call change Entry on out of range i\n");
		exit(EXIT_FAILURE);
	}

	if ( j < 1 || j > size(M))
	{
		printf("Error: tried to call change Entry on out of range j\n");
		exit(EXIT_FAILURE);
	}
//Change the value at the specified position
	Entry E = newEntry(j, x);
  	Entry curr;
  	List R = M->row[i];

  	if (length(R) == 0) {
    		if (x != 0) {
      			append(R, E);
      			M->entry_count++;
    		} else {
      			freeEntry(&E);
      			return;
    		}
  	} else {
    		moveFront(R);
    		while (index(R) >= 0) {
      			curr = get(R);
	        	if (j > curr->col) {
		        	moveNext(R);
      			} else {
        			break;
      			}
    		}
    		if (index(R) == -1) {
      			if (x != 0) {
        			append(R, E);
       				M->entry_count++;  
      			} else {
        			freeEntry(&E);
      			}
    		} else if (j < ((Entry)get(R))->col) {
      			if (x != 0) {
        			insertBefore(R, E);
        			M->entry_count++;
      			} else {
        			freeEntry(&E);
      			}
    		} else {
      			if (x != 0) {
        			freeEntry(&curr);
        			set(R, E);
      			} else {
        			freeEntry(&curr);
        			delete(R);
        			M->entry_count--;
      			}
    		}
  		List R = M->row[i];
  		Entry E = newEntry(j, x);
		if (x == 0) {
    		freeEntry(&E);
  	}

  	if (length(R) == 0 && x != 0) {
    		append(R, E);
    		M->entry_count++;
  	} else {
    		moveFront(R);
    		while (index(R) >= 0) {
      			Entry T = get(R);
      			if (T->col < j) {
        			if (T == back(R) && x != 0) {
          				insertAfter(R, E);
          				M->entry_count++;
        			} else {
          				moveNext(R);
          				continue;
       				}
      			} else if (T->col == j) {
        			if (x == 0) {
          				freeEntry(&T);
          				delete(R);
          				M->entry_count--;
        			} else {
          				freeEntry(&T);
          				set(R, E);
        			}
      			} else if (T->col > j && x != 0) {
        			insertBefore(R, E);
        			M->entry_count++;
      			}
      			break;
    		}
  	}
}
}
// Matrix Arithmetic operations - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Matrix copy(Matrix A) // Returns a reference to a new Matrix object having the same entries as A.
{			//Time: O(n+a)	n = # rows, a&b = #nonzero entris in A and B
	assert(A != NULL);
	Matrix copy = newMatrix(size(A));
  	for (int i = 1; i <= size(A); i++) {
   		List rowC = A->row[i];
    		moveFront(rowC);
    		if (length(rowC) >= 0) {
      			while (index(rowC) >= 0) {
       				Entry E = get(rowC);
        			changeEntry(copy, i, E->col, E->data);
        			moveNext(rowC);
      			}
    		}
  	}
  return copy;
}
Matrix transpose(Matrix A) // Returns a reference to a new Matrix object representing the transpose of
{				//Time: O(n+a)
	assert(A != NULL);
// Create a new matrix with the number of columns and rows swapped
	Matrix T = newMatrix(size(A));
  	for (int i = 1; i <= size(A); i++) {
    		List rowT = A->row[i];
   		moveFront(rowT);
    		if (length(rowT) >= 0) {
      			while (index(rowT) >= 0) {
        			Entry E = get(rowT);
        			changeEntry(T, E->col, i, E->data);
        			moveNext(rowT);
      			}
    		}
  	}
  	return T;
}
Matrix scalarMult(double x, Matrix A) // Returns a reference to a new Matrix object representing xA.
{					//Time: O(n+a)
	assert(A != NULL);
	Matrix xA = newMatrix(size(A));
  	for (int i = 1; i <= size(A); i++) {
    		List Row = A->row[i];
    		moveFront(Row);
    		if (length(Row) >= 0) {
      			while (index(Row) >= 0) {
        			Entry E = get(Row);
        			changeEntry(xA, i, E->col, x*E->data);
        			moveNext(Row);
      			}
    		}
  	}
  	return xA;
}

//Helper function needed for sum
List sumList(List A, List B) {
	List sum = newList();
	Entry new;
  	if (length(A) == 0 && length(B) == 0) {
    		return sum;
  	}
  	if (length(A) == 0) {
    		moveFront(B);
    		while (index(B) >= 0) {
      			new = get(B);
      			Entry newE = newEntry(new->col, new->data);
      			append(sum, newE);
      			moveNext(B);
    		}
    	return sum;
  	}
  	if (length(B) == 0) {
    		moveFront(A);
    		while (index(A) >= 0) {
      			new = get(A);
      			Entry newE = newEntry(new->col, new->data);
      			append(sum, newE);
      			moveNext(A);
    		}
    	return sum;
  	}

 	moveFront(A);
  	moveFront(B);
  	while (index(A) >= 0 && index(B) >= 0) {
    		Entry a = get(A);
    		Entry b = get(B);
    		if (a->col == b->col) {
      			if ((a->data + b->data) != 0) {
        			new = newEntry(a->col, a->data+b->data);
        			append(sum, new);
        			moveNext(A);
        			moveNext(B);
      			} else { 
        			moveNext(A);
        			moveNext(B);
      			}
    		} else {
      			while (b->col < a->col) {
        			new = newEntry(b->col, b->data);
        			append(sum, new);
        			moveNext(B);
        			if (index(B) == -1) {
          				break;
        			}
        			b = get(B);
      			}
      			while (a->col < b->col) {
        			new = newEntry(a->col, a->data);
        			append(sum, new);
        			moveNext(A);
        			if (index(A) == -1) {
          				break;
        			}
        			a = get(A);
      			}
    		}
    		if (index(B) == -1) {
      			while (index(A) >= 0) {
        			a = get(A);
        			new = newEntry(a->col, a->data);
        			append(sum, new);
        			moveNext(A);
      			}
    		}
    		if (index(A) == -1) {
      			while (index(B) >= 0) {
        			b = get(B);
        			new = newEntry(b->col, b->data);
        			append(sum, new);
        			moveNext(B);
      			}
    		}
  	}
  	return sum;
}
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B)		//Time: O(n+a+b)
{
	assert(A != NULL);
	assert(B != NULL);
	if (size(A)!= size(B))
	{
		printf("Error: called sum on Matrices of different size");
		exit(EXIT_FAILURE);
	}
	if (equals(A, B)) {
    		Matrix eqm = scalarMult(2, A);
    		return eqm;
  	}
  	Matrix sum = newMatrix(size(A));
  	for (int i = 1; i <= size(A); i++) {
    		freeList(&(sum->row[i]));
    		List list_sum = sumList(A->row[i], B->row[i]);
   		sum->row[i] = list_sum;
    		sum->entry_count += length(list_sum);
  	}
  	return sum;
}

// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B)		//Time: O(n+a+b)
{
	assert(A != NULL);
	assert(B != NULL);
	if (size(A) != size(B))
	{
		printf("Error: tried to call diff on matrices of different size.");
	}
	if (size(A) != size(B)) {
    		printf("Matrix Error: Matrices A and B are of different dimensions.\n");
    		exit(EXIT_FAILURE);
  	}
  	Matrix negB = scalarMult(-1, B);
  	Matrix diff = sum(A, negB);
  	freeMatrix(&negB);
  	return diff;
}

//Product Helper Function - - - - - - - - - - - - - - - - - - - - - - - - - - - -
double vectorDot(List P, List Q)        //returns vector dot product of 2 matrix rows (P and Q)
//Use this and transpose to implment product
{
	assert(P != NULL);
	assert(Q != NULL);

	double sum = 0;
	moveFront(P);
	moveFront(Q);
	while (index(P) != -1 || index(Q) != -1)
	{
		if(((Entry)get(P))->col == ((Entry)get(Q))->col)
		{
			sum = sum + ((Entry)get(P))->data * ((Entry)get(Q))->data;
			moveNext(P);
			moveNext(Q);
		}
		else if (((Entry)get(P))->col < ((Entry)get(Q))->col){
	
			moveNext(P);
		}
		else 
		{
			moveNext(Q);
		}
	}
	return sum;
}

// Returns a reference to a new Matrix object representing AB
//pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B)	//Time: O(n^2+a*b)
{
	//precondition chceck
	assert(A != NULL);
	assert(B!= NULL);
	if (size(A) != size(B))
	{
	printf("Error: Tried to call rpoduct on matrices of different sizes");
	exit(EXIT_FAILURE);
	}
	Matrix NewM = newMatrix(size(A));
	Matrix Transpose = transpose(B);
	double val = 0;
	for (int i = 0; i <= size(A); i++)
	{
		if (length(A->row[i]) == 0)
			continue;
		else{
			for (int j = 0; j < size(B); j++)
			{
				if (length(Transpose->row[j]) == 0)
				{
					continue;
				}
				else
				{
					val = vectorDot(A->row[j], Transpose->row[j]);
					changeEntry(NewM, i, j, val);
				}
			}	
		}	
	}
	freeMatrix(&Transpose);
	return NewM;
}
//Prints a string representation of Matrix M to filestream out. Zero rows are not printed. Each non-zero row is represented as one line consisting of the row number, followed by a colon, a space, then a space separated list of pairs "(col, val)" giving the column numbers and non-zero values in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M)
{
	//precondition check
	if (M == NULL) {
        	fprintf(stderr, "Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        	exit(EXIT_FAILURE);
    	}
	for (int i = 1; i <= M->size; i++) {
    		List R = M->row[i];
    		if (length(R) == 0) {
      			continue;
    		}
    		fprintf(out, "%d: ", i);
    		for (moveFront(R); index(R) >= 0; moveNext(R)) {
      			Entry E = get(R); 
      			fprintf(out, "(%d, %0.1f) ", E->col, E->data); 
    		}
    		fprintf(out, "\n");
  	}
}

