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

TfIdfList newTfIdfList (void) {
	TfIdfList L = malloc (sizeof (*L));
	if (L == NULL) err (EX_OSERR, "couldn't allocate Tf-idf List.\n");
	L->next = NULL;
	L->filename = "";
	L->tfidf_sum = 0;
	return L;
}

struct TfIdfNode *newTfidfNode(char *filename, double tfidfVal) {
	struct TfIdfNode *n = malloc (sizeof *n);
	if (n == NULL) err (EX_OSERR, "couldn't allocate CharList node");
	n->filename = filename;
	n->tfidf_sum = tfidfVal;
	n->next = NULL;
	return n;
}

TfIdfList TfidfInsertInOrder(TfIdfList L, char *filename, double tfidfVal) {
	struct TfIdfNode *head = L;
	if (head == NULL) { // when list is empty.
    struct TfIdfNode *newNode = newTfidfNode(filename, tfidfVal);
		return newNode;
	}
	struct TfIdfNode *newNode = newTfidfNode(filename, tfidfVal);
	if (tfidfVal > head->tfidf_sum) { //if the tfidf Value is greater than that of the head.
		newNode->next = head;
		head = newNode;
		return newNode;
	}
	if (tfidfVal == head->tfidf_sum) { // if the tfidf value is equal to that of head.
		if (strcmp(filename, head->filename) <= 0) { // if the file name comes before the head's filename.
			newNode->next = head;
			head = newNode;
			return newNode;
		} else { // if the file name comes after the head's filename.
			newNode->next = head->next;
			head->next = newNode;
			return head;
		}
	}
	struct TfIdfNode *curr = head;
	while (curr->next != NULL && curr->next->tfidf_sum > tfidfVal) { // iterate through to find node.
		 curr = curr->next;
	}
  if (curr->next != NULL) {
    if (curr->next->tfidf_sum == tfidfVal) { // when the tfidf value is equal for consecutive nodes.
  		if (strcmp(filename,  curr->next->filename) <= 0) {
  			newNode->next = curr->next;
  			curr->next = newNode;
  			return L;
  		} else {
				while (curr->next != NULL && curr->next->tfidf_sum == tfidfVal
					&& strcmp(filename,  curr->next->filename) > 0) {
					curr = curr->next;
				}
  			newNode->next = curr->next;
  			curr->next = newNode;
  			return L;
  		}
  	}
  }
	newNode->next = curr->next;
	curr->next = newNode;
  return L;
}

TfIdfList TfidfListFind(TfIdfList L, char *filename) {
  if (L == NULL) { // when the list is empty.
    return NULL;
  } else if (strcmp(filename, L->filename) == 0) { //when the filename is found.
    return L;
  }
	return TfidfListFind(L->next, filename);

}

TfIdfList TfidfListInsert(TfIdfList L, char *filename, double tfidfVal) {
  struct TfIdfNode *head = L;
  if (head == NULL) { // when this list is empty.
    struct TfIdfNode *newNode = newTfidfNode(filename, tfidfVal);
    return newNode;
  }
  if (fileNameInList(L, filename) == 1) { // if the filename is already in the list then add
																					// coresponding tfidf to the sum.
    TfIdfList foundNode = TfidfListFind(L, filename);
    foundNode->tfidf_sum += tfidfVal;
  } else { // if not there then insert in order.
    L = TfidfInsertInOrder(L, filename, tfidfVal);
  }
  return L;
}

int fileNameInList(TfIdfList L, char *filename) {
	if (L == NULL) { // when the file list is empty.
		return 0;
	} if (strcmp(L->filename, filename) == 0) { //file found
		return 1;
	}
	return fileNameInList(L->next, filename);
}
