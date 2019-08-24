#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <ctype.h>
#include <math.h>

//create a new FIle list node.
struct FileListNode *newFileList (char *filename, double tf);

// return the numer of nodes in the given list.
double numberofNodes(FileList L);

//returns 1 if the file list contains a particular file name or 0 otherwise.
int fileNamePresent(FileList L, char *str);

//Inserts in the file list in order.
FileList fileNameInsertInorder(FileList L, char *filename, double tf);

// returns the number of  a particular word (str) in a given file.
double countParticularWord(char *str, char *filename);

//returns the total words in a file.
double totalWordsInFile(char *filename);
