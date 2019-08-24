#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <ctype.h>
#include <math.h>

// make a new node containing a value
InvertedIndexBST newBSTNode (char *str, char *filename, double tf);

//Insert a given string in the tree.
InvertedIndexBST TreeInsert(InvertedIndexBST t, char *str, char *filename, double tf);

//FInd a given string in the tree.
InvertedIndexBST TreeFind(InvertedIndexBST t, char *str);

//Prints the elemtents of BST in a particular file.
void printTree(InvertedIndexBST tree, FILE *filePtr);
