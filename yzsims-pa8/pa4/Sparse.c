#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Matrix.h"

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
        int n, a, b;

//initialize
	int row, column;
  	double value;
  	Matrix A, B;
  	int line = 0;

  	fscanf(inFile, "%d %d %d\n", &n, &a, &b);
  	A = newMatrix(n);
  	B = newMatrix(n);
  	while (!feof(inFile)) {
    		fscanf(inFile, "%d %d %lf", &row, &column, &value);
    		line += 1;
    		if (line <= a) {
      			printf("row %d\n size %d\n", row, n);
			printMatrix(stdout, A);
			changeEntry(A, row, column, value);
    		}else {
      			changeEntry(B, row, column, value);
    			}
  		}
//Print Everything
  	fprintf(outputFile, "A has %d non-zero entries:\n", NNZ(A));
  	printMatrix(outputFile, A);
  	fprintf(outputFile, "\nB has %d non-zero entries:\n", NNZ(B));
  	printMatrix(outputFile, B);
  
  	fprintf(outputFile, "\n(1.5)*A =\n");
  	Matrix SM = scalarMult(1.5, A);
  	printMatrix(outputFile, SM);

  	fprintf(outputFile, "\nA+B =\n");
  	Matrix sumAB = sum(A, B);
  	printMatrix(outputFile, sumAB);

  	fprintf(outputFile, "\nA+A =\n");
	Matrix sumAA = sum(A, A);	//error here
  	printMatrix(outputFile, sumAA);

  	fprintf(outputFile, "\nB-A =\n");
  	Matrix diffBA = diff(B, A);	//error here
  	printMatrix(outputFile, diffBA);

  	fprintf(outputFile, "\nA-A =\n");
  	Matrix diffAA = diff(A, A);	//error here
  	printMatrix(outputFile, diffAA);

  	fprintf(outputFile, "\nTranspose(A) =\n");
  	Matrix T = transpose(A);
  	printMatrix(outputFile, T);

  	fprintf(outputFile, "\nA*B =\n");
  	Matrix prodAB = product(A, B);
 	printMatrix(outputFile, prodAB);
  
  	fprintf(outputFile, "\nB*B =\n");
  	Matrix prodBB = product(B, B);
  	printMatrix(outputFile, prodBB);
//Close Files
  	fclose(inFile);
  	fclose(outputFile);
//Free Everythung
	freeMatrix(&A);
  	freeMatrix(&B);
  	freeMatrix(&SM);
  	freeMatrix(&sumAB);
  	freeMatrix(&sumAA);	//free
	freeMatrix(&diffBA);	//free
  	freeMatrix(&diffAA);	//free
 	freeMatrix(&T);
  	freeMatrix(&prodAB);
  	freeMatrix(&prodBB);
	return 0;
}
