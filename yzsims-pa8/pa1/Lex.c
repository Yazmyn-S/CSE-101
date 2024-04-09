// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Name: Yazmyn Sims
// ID: yzsims
// Title: Lex.c
// Description: Implements the List ADT to indirectly sort an array (Programming Assignment 1)
//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LINE_LENGTH 1024

// Function prototypes
int getFileLineCount(FILE* file);
void readLinesToArray(FILE* file, char** lines, int numLines);
List buildIndexList(char** lines, int numLines);
void writeListToFile(FILE* outFile, List indexList, char** lines, int numLines);

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
	// Count the number of lines in the input file
	int numLines = getFileLineCount(inFile);
	
	// Allocate memory for an array of strings to hold the lines
	char** lines = (char**)malloc(numLines * sizeof(char*));
	
	if (lines == NULL) {
                perror("Error allocating memory for lines array");
                fclose(inFile);
                exit(EXIT_FAILURE);
        }
	
	for (int i = 0; i < numLines; i++)
	{
		lines[i] = (char *)malloc(MAX_LINE_LENGTH+1);
	}

	// Read lines from the input file into the array
	readLinesToArray(inFile, lines, numLines);
	// Close the input file
	fclose(inFile);
  
	// Build an index list using the List ADT
	List indexList = buildIndexList(lines, numLines);
	// Open output file for writin
	FILE* outFile = fopen(argv[2], "w");
	if (outFile == NULL) {
		perror("Error opening output file");
    		free(lines);
    		freeList(&indexList);
    		exit(EXIT_FAILURE);
	}
	// Write the alphabetized lines to the output file
	writeListToFile(outFile, indexList, lines, numLines);
	// Close the output file
	fclose(outFile);
	// Free allocated memory
	for(int i = 0; i < numLines; i++){free(lines[i]);}	//ADDS A CORRECTION (4)	
	free(lines);
	freeList(&indexList);

	return 0;
}

int getFileLineCount(FILE* file) {
	int count = 0;
	char buffer[MAX_LINE_LENGTH];
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		count++;
	}

	// Reset file position indicator to the beginning
	rewind(file);
	return count;
}

void readLinesToArray(FILE* file, char** lines, int numLine) {
	char buffer[MAX_LINE_LENGTH];
        int i = 0;
	while (i < numLine && fgets(buffer, sizeof(buffer), file) != NULL) {

		// Remove newline character from the end
		buffer[strcspn(buffer, "\n")] = '\0';

		// Allocate memory for the lines
		strcpy(lines[i], buffer);
		if (lines[i] == NULL) {
			perror("Error allocating memory for line");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

List buildIndexList(char** lines, int numLines) {
    List indexList = newList();
    for (int i = 0; i < numLines; i++) {
        moveFront(indexList);
        while (index(indexList) >= 0 && strcmp(lines[i], lines[get(indexList)]) > 0) {
            moveNext(indexList);
        }
        if (index(indexList) >= 0) {
            insertBefore(indexList, i);
        } else {
            append(indexList, i);
        }
    }
    return indexList;
}

void writeListToFile(FILE* outFile, List indexList, char** lines, int numLines) {
    moveFront(indexList);
    while (index(indexList) >= 0) {
        fprintf(outFile, "%s\n", lines[get(indexList)]);
        moveNext(indexList);
    }
}
