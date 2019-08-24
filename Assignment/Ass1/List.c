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

CharList newCharList (void) {
	struct CharListRep *L = malloc (sizeof *L);
	if (L == NULL) err (EX_OSERR, "couldn't allocate CharList");
	L->first = NULL;
	L->last = NULL;
	return L;
}

struct CharListNode *newCharListNode (char *str) {
	struct CharListNode *n = malloc (sizeof *n);
	if (n == NULL) err (EX_OSERR, "couldn't allocate CharList node");
	n->data = malloc (sizeof strlen(str));
  strcpy(n->data, str);
	n->next = NULL;
	return n;
}

void CharListInsert (CharList L, char *str) {
	struct CharListNode *n = newCharListNode(str);
	if (L->first == NULL) { // when the list is empty.
		L->first = L->last = n;
	} else { // rest cases.
		L->last->next = n;
		L->last = n;
	}
}
