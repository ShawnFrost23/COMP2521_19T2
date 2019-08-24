//invertedIndex.h....implementation
//Made by Arth Patel on 2nd of July, 2019.
//Assignment 1 COMP2521

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

// Some functions in the Tree.c, List.c, FileNameList.c and TfidfList.c are taken reference from
// lectures and weekly labs and modified as per usaage.
// The trim function for trimming trailing and leading white spaces is takes reference from
// GeeksForGeeks and StackOverflow.

//=======Helper functions heading go here=======
char *trim(char *str);
int hasPunctuation(char *str);

//=======================Helper functions=======================
//trims the trailing and leading white space for a given string
char *trim(char *str) {
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if (str == NULL) {
			return NULL;
		}
    if (str[0] == '\0') {
			return str;
		}

    len = strlen(str);
    endp = str + len;

    // Move the front and back pointers to address the first non-whitespace
    // characters from each end.

    while (isspace((unsigned char) *frontp)) {
			++frontp;
		}

		if (endp != frontp) {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if (str + len - 1 != endp) {
			*(endp + 1) = '\0';
		} else if (frontp != str &&  endp == frontp) {
			*str = '\0';
		}

    // Shift the string so that it starts at str so that if it's dynamically
    // allocated, we can still free it on the returned pointer.  Note the reuse
    // of endp to mean the front of the string buffer now.
    endp = str;
    if (frontp != str) {
            while (*frontp) {
							*endp++ = *frontp++;
						}
            *endp = '\0';
    }
    return str;
}

//retruns 1 if the string ends with the given punctuations, 0 other wise
int hasPunctuation(char *str) {
  int len = strlen(str);
  if (str[len-1] == '.' || str[len-1] == ',' || str[len-1] == ';' || str[len-1] == '?') {
    return 1;
  }
  return 0;
}

//=======================invertedIndex.h functions=======================
//======================Part I functions======================
char * normaliseWord(char *str) {
  //case for empty string
  if (str[0] == '\0') {
    return str;
  }
  trim(str);
  int i = 0;
	int len = strlen(str);
  while (i < len) { //change the characters to lower case.
   str[i] = tolower(str[i]);
		i += 1;
  }
  if (hasPunctuation(str) == 1) { // remove punctuation according to the given description.
    str[len-1] = '\0';
  }
  return str;
}

InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
  FILE *filePtr = fopen(collectionFilename, "r"); //open the collection file.
  if (filePtr == NULL) {
    printf("Error with the file.");
    exit(0);
  }
  CharList nameOfFiles = newCharList();
  char filename[100];
  while (fscanf(filePtr, "%s", filename) != EOF) { // store the name of files in the collection file
		CharListInsert(nameOfFiles, filename);         // into a linked list.
  }
  fclose(filePtr);
  struct CharListNode *curr = nameOfFiles->first;
  InvertedIndexBST returnTree = NULL;
  while(curr != NULL) { // open each of the files in a linked list.
    FILE *filePtr2 = fopen(curr->data, "r");
		if (filePtr2 == NULL) {
      printf("Error with the file.");
      exit(0);
    }
		double totalWords = totalWordsInFile(curr->data); // count total words for it.
    char buffer[100];
    while (fscanf(filePtr2, "%s" ,buffer) != EOF) { //read every word in the file.
      normaliseWord(buffer);
			double particularWord = countParticularWord(buffer, curr->data); // count the particular word.
			double tf = (particularWord / totalWords);
      returnTree = TreeInsert(returnTree, buffer, curr->data, tf); //insert the word into our tree.

    }
		fclose(filePtr2);
    curr = curr->next;
  }
   return returnTree;
}

void printInvertedIndex(InvertedIndexBST tree) {
	FILE *fileOutput = fopen("invertedIndex.txt", "w");
	printTree(tree, fileOutput);
	fclose(fileOutput);
}

//======================Part II functions======================

TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord , int D) {
  TfIdfList returnList = NULL;
	if (TreeFind(tree, searchWord) == NULL) {
	 	return returnList;
	}
	InvertedIndexBST foundNode = TreeFind(tree,searchWord); //find the node with the search word.
	double documentsPresentIn = numberofNodes(foundNode->fileList); // count the number of documents
	double quotient = D / documentsPresentIn;                       // the search word is present in.
	double idfVal = log10(quotient);
	struct FileListNode *curr = foundNode->fileList;
	while (curr != NULL) { // for each file in the file list of the search word do.
		double tfidfVal = (idfVal * (curr->tf));
		returnList = TfidfInsertInOrder(returnList, curr->filename, tfidfVal); // insert the filename
		curr = curr->next;                                                     // with coresponding tfidf
	}                                                                        // in the list.
	return returnList;
}

TfIdfList retrieve(InvertedIndexBST tree, char* searchWords[] , int D) {
	TfIdfList returnList = NULL;
	returnList = calculateTfIdf(tree, searchWords[0], D); // calculate tfidf for the first word and
	int i = 1;                                            // return a list.
	while (searchWords[i] != NULL) { // for every word after the first word do:
		InvertedIndexBST foundNode = TreeFind(tree, searchWords[i]);
		double documentsPresentIn = numberofNodes(foundNode->fileList);
		double quotient = D / documentsPresentIn;
		double idfVal = log10(quotient);
		struct FileListNode *curr = foundNode->fileList;
		while (curr != NULL) { // for every file the word is present in insert it into the list or
                            // increase the sum.
			double tfidfVal = (idfVal * (curr->tf));
			returnList = TfidfListInsert(returnList, curr->filename, tfidfVal);
			curr = curr->next;
		}
		i += 1;
	}
	return returnList;
}
