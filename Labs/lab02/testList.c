// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLList.h"

void testInsertBefore(DLList L);
void testInsertAfter(DLList L);
void testDelete(DLList L);

int main (void)
{
	printf("\n");
	printf("To create a list give some input followed by pressing return.\n");
	printf("Each time you press return you are creating a new node in the list.\n");
	printf("Press 'control' + 'd' once you have finished entering input\n");
	printf("Input: \n");
	DLList myList = getDLList (stdin);
	putDLList (stdout, myList);
	assert (validDLList (myList));

	printf("\n");
	testInsertBefore(myList);

	printf("\n");
	testInsertAfter(myList);

	printf("\n");
	testDelete(myList);

	printf("\n");
	printf("Freeing myList....\n");
	freeDLList (myList);

	printf("=========== Exit Successful ===========");
	printf("\n");
	return EXIT_SUCCESS;
}

void testInsertBefore(DLList L)
{
	printf("======== Testing Insert Before Function ========\n");

	printf("Insert numbers 1 - 5 into the list, one before another.\n");
	printf("\n");

	printf("The list is currently pointing at: %s\n", DLListCurrent(L));
	printf("The list currently has Length: %zu\n", DLListLength(L));
	printf("\n");

	printf("We expect the output to look like this: \n");
	printf("5\n4\n3\n2\n1\n%s\n", DLListCurrent(L));
	printf("\n");

	printf("The list currently looks like this: \n");
	putDLList(stdout, L);
	printf("\n");

	int i = 1;
	while (i <= 5) {
		char input[100];
		sprintf(input, "%d", i);
		DLListBefore(L, input);
		i++;
	}

	printf("After inserting the numbers in ascending order our list now looks like this: \n");
	putDLList(stdout, L);

	printf("\n");
	printf("Now our list has Length: %zu\n", DLListLength(L));
	printf("\n");
	assert(validDLList(L));

	printf("======== Test Completed ========\n");
}

void testInsertAfter(DLList L)
{
	printf("======== Testing Insert After Function ========\n");

	printf("Insert numbers 1 - 5 into the list, one after another.\n");
	printf("\n");

	printf("The list is currently pointing at: %s\n", DLListCurrent(L));
	printf("The list currently has Length: %zu\n", DLListLength(L));
	printf("\n");

	printf("We expect the output to look like this: \n");
	printf("%s\n1\n2\n3\n4\n5\n....\n", DLListCurrent(L));
	printf("\n");

	printf("The list currently looks like this: \n");
	putDLList(stdout, L);
	printf("\n");

	int i = 1;
	while (i <= 5) {
		char input[100];
		sprintf(input, "%d", i);
		DLListAfter(L, input);
		i++;
	}

	printf("After inserting the numbers, one after another, our list now looks like this: \n");
	putDLList(stdout, L);

	printf("\n");
	printf("Now our list has Length: %zu\n", DLListLength(L));

	assert(validDLList(L));

	printf("======== Test Completed ========\n");
}

void testDelete(DLList L)
{
	printf("======== Testing the Delete Function ========\n");
	printf("\n");

	printf("The list is currently pointing at: %s\n", DLListCurrent(L));
	printf("The list currently has Length: %zu\n", DLListLength(L));
	assert(validDLList(L));
	printf("\n");

	printf("The list currently looks like this: \n");
	putDLList(stdout, L);
	printf("\n");

	DLListMoveTo(L, 1);
	assert(validDLList(L));
	printf("Deleting the first node.. %s\n", DLListCurrent(L));
	DLListDelete(L);
	assert(validDLList(L));
	printf("\n");

	printf("Now our list looks like this: \n");
	putDLList(stdout, L);
	printf("\n");

	printf("\n");
	printf("Now our list has Length: %zu\n", DLListLength(L));
	printf("\n");

	DLListMoveTo(L, DLListLength(L) + 1);
	printf("Deleting the last node: %s\n", DLListCurrent(L));
	printf("\n");
  DLListDelete(L);
	assert(validDLList(L));


	printf("Now our list looks like this: \n");
	putDLList(stdout, L);
	printf("\n");

	printf("Now our list has Length: %zu\n", DLListLength(L));
	printf("\n");

	assert(validDLList(L));
	printf("======== Test Completed ========\n");
}
