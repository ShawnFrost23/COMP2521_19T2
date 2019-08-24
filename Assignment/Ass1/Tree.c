#include "invertedIndex.h"
#include "List.h"
#include "Tree.h"
#include "TfidfList.h"
#include "FileNameList.h"

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <ctype.h>
#include <math.h>

char *stringCopy(const char *str) {
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if(dup) {
        strcpy(dup, str);
    }
    return dup;
}

InvertedIndexBST newBSTNode (char *str, char *filename, double tf) {
	InvertedIndexBST new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate BST node");
	new->word = malloc (sizeof(strlen(str)+1));
	new->word = stringCopy(str);
	new->left = new->right = NULL;
  struct FileListNode *FileList = newFileList(filename, tf);
  new->fileList = FileList;
	return new;
}

InvertedIndexBST TreeInsert (InvertedIndexBST t, char *str, char *filename, double tf) {
  if (t == NULL) { // when the tree is empty.
    return newBSTNode(str, filename, tf);
  } else if (strcmp(str, t->word) > 0) { // when value greater than the node we are considering.
    t->right = TreeInsert(t->right, str, filename, tf);
  } else if (strcmp(str, t->word) < 0) { // when the value less than the node we are considering.
    t->left = TreeInsert(t->left, str, filename, tf);
  } else if (strcmp(str, t->word) == 0) { //if the word is already there.
		if (fileNamePresent(t->fileList, filename) == 1) { // if the current file is there in the File
			return t; 																			 // list of our word then return.
		} else {
			t->fileList = fileNameInsertInorder(t->fileList, filename, tf); // The file is not there in
		}																																	// FileList so insert in order.
		return t;
  }
  return t;
}

InvertedIndexBST TreeFind (InvertedIndexBST t, char *str) {
	if (t == NULL) { //When tree is empty.
		return NULL;
	} else if (strcmp(str, t->word) > 0) { // when value greater than the node we are considering.
		return TreeFind(t->right, str);
	} else if (strcmp(str, t->word) < 0) { // when the value less than the node we are considering.
		return TreeFind(t->left, str);
	} else if (strcmp(str, t->word) == 0) { // when the word is found.
		return t;
	}
	return NULL;
}

void printTree (InvertedIndexBST tree, FILE *filePtr) {
  if (tree == NULL) { // when tree is empty.
    return;
  }
  printTree(tree->left, filePtr);
  fprintf(filePtr, "%s ", tree->word);
  struct FileListNode *curr = tree->fileList;
  while(curr != NULL) { // iterate through the file list and print every file name there.
    fprintf(filePtr, "%s ", curr->filename);
    curr = curr->next;
  }
  fprintf(filePtr, "\n");
  printTree(tree->right, filePtr);
}
