#include "invertedIndex.h"
#include "List.h"
#include "Tree.h"
#include "TfidfList.h"
#include "FileNameList.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

struct FileListNode *newFileList (char *filename, double tf) {
  struct FileListNode *L = malloc (sizeof *L);
  if (L == NULL) err (EX_OSERR, "couldn't allocate CharList");
  L->next = NULL;
  L->filename = malloc(sizeof(strlen(filename)));
  strcpy(L->filename, filename);
  L->tf = tf;
  return L;
}

double numberofNodes(FileList L) {
	if (L == NULL) {
		return 0;
	}
	return 1 + numberofNodes(L->next);
}

int fileNamePresent(FileList L, char *str) {
	if (L == NULL) { // base case.
		return 0;
	} if (strcmp(L->filename, str) == 0) { // when the filename is found.
		return 1;
	}
	return fileNamePresent(L->next, str); // recursive case.
}

FileList fileNameInsertInorder(FileList L, char *filename, double tf) {
  struct FileListNode *head = L;
  if (head == NULL) { // if the list is empty.
    struct FileListNode *newNode = newFileList(filename, tf);
    return newNode;
  }
  struct FileListNode *newNode = newFileList(filename, tf);
  if (strcmp(head->filename, filename) > 0) { // if new node comes before the head.
    newNode->next = head;
    head = newNode;
    return newNode;
  }
  //rest cases.
  struct FileListNode *curr = head;
  while (curr->next != NULL && strcmp(curr->next->filename, filename) < 0) {
    curr = curr->next;
  }
  newNode->next = curr->next;
  curr->next = newNode;
  return L;
}

double totalWordsInFile(char *filename) {
  FILE *filePtr = fopen(filename, "r");
  if (filePtr == NULL) {
    printf("The file didn't open\n");
    exit(0);
  }
  char word[100];
  double count = 0;
  while(fscanf(filePtr, "%s", word) != EOF) {
    count += 1;
  }
  fclose(filePtr);
  return count;
}

double countParticularWord(char *str, char *filename) {
  FILE *filePtr = fopen(filename, "r");
  if (filePtr == NULL) {
    printf("The file didn't open\n");
    exit(0);
  }
  char word[100];
  double count = 0;
  while (fscanf(filePtr, "%s", word) == 1) {
    normaliseWord(word);
    if (strcmp(str, word) == 0) {
      count += 1;
    }
  }
  fclose(filePtr);
  return count;
}
