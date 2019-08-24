//implementation of scaledFootrule.h
//Made by Arth Patel on 3rd August 2019

#include "scaledFootrule.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//========= Global Variables =========
double finScaleF = 100;
int finPos[100];

//========= heading for helper functions go here =========
void swapPositions(int *array, int i, int j);

//========= implementaion of helper functions =========
void swapPositions(int *array, int i, int j) {
  int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}
//========= Main function =========
int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Supply atleast 2 arguments: file1.txt, file2.txt and so on\n");
    exit(0);
  }
  int i = 1;
  char **rankFiles = NULL;
  int numFiles = 0;
  while (i < argc) {
    rankFiles = realloc(rankFiles, (numFiles + 1) * sizeof(char *));
    rankFiles[numFiles] = malloc(strlen(argv[i] + 1));
    strcpy(rankFiles[numFiles++], argv[i]);
    i += 1;
  }

  //a 2D matrix to store url suffix for all the files.
  //eg: matrix[1][] will be all the urls in the second file.
  int matrix[numFiles][100];
  //the number of urls in each of the files given to us.
  int numUrls[100] = {0};
  //the maximum urls out of all the files given to us.
  int totalURLS = 0;
  int allUrls[100] = {0};
  int position[100][100];
  char buffer[1000];
  i = 0;
  while (i < numFiles) {
    FILE *rankFilePtr = fopen(rankFiles[i], "r");
    int j = 0, k = 0;
    while (fscanf(rankFilePtr, "%s", buffer) != EOF) {
      char *tokenNum = strtok(buffer, "url");
      matrix[i][j] = atoi(tokenNum);
      int flag = 0;
      k = 0;
      while (k < totalURLS) {
        if (allUrls[k] == atoi(tokenNum)) {
          flag = 1;
          break;
        }
        k += 1;
      }
      if (!flag) {
        allUrls[totalURLS] = atoi(tokenNum);
        totalURLS += 1;
      }
      j += 1;
      numUrls[i] += 1;
    }
    fclose(rankFilePtr);
    i += 1;
  }
  printf("total %d\n", totalURLS);
  sortArray(allUrls, totalURLS);

  i = 0;
  while (i < numFiles) {
    findPosition(position[i], matrix[i], allUrls, totalURLS);
    i += 1;
  }

  int ordPosArray[totalURLS];
  i = 0;
  while (i < totalURLS) {
    ordPosArray[i] = i + 1;
    i += 1;
  }
  getFinalPostions(ordPosArray, position, numUrls, numFiles, 0, totalURLS);
  int printArray[totalURLS];
  i = 0;
  while (i < totalURLS) {
    int finPosition = finPos[i] - 1;
    printArray[finPosition] = allUrls[i];
    i += 1;
  }

  printf("%lf\n", finScaleF);
  i = 0;
  while (i < totalURLS) {
    char placeholder[20];
		sprintf(placeholder,"url%d",printArray[i]);
		printf("%s\n", placeholder);
    i += 1;
  }
  return 0;
}

//========= implementaion of functions in scaledFootrule.h =========
void sortArray(int *array, int length) {
  int i = 0, j = 0;
  while (i < length) {
    j = i + 1;
    while (j < length) {
      if (array[i] > array[j]) {
        swapPositions(array, i, j);
      }
      j += 1;
    }
    i += 1;
  }
}

void findPosition(int *posArray, int *unsortedArray, int *allUrls, int totLen) {
  int i = 0, j = 0;
  int pos = 0;
  while (i < totLen) {
    j = 0;
    while (j < totLen) {
      if (allUrls[i] == unsortedArray[j]) {
        posArray[pos++] = j + 1;
        break;
      }
      j += 1;
    }
    i += 1;
  }
}

void getFinalPostions(int *array, int pos[100][100], int *numUrls, int num, int i, int length) {
  int j = 0, k = 0, l = 0;
	double temp = 0;
  if (i == length){
  l = 0;
	while(l < num) {
    j = 0;
		while (j < numUrls[l]) {
			temp += fabs(((double)pos[l][j]/(double)numUrls[l]) - ((double)array[j]/(double)length));
      j += 1;
		}
    l += 1;
	}
 	if(temp < finScaleF) {
 		finScaleF = temp;
    k = 0;
 		while(k < length) {
 				finPos[k] = array[k];
        k += 1;
 		}
 	}
	return;
  }
  j = i;
	while(j < length) {
 		swapPositions(array,i,j);
		getFinalPostions(array, pos, numUrls, num, i+1, length);
    j += 1;
	}
	return;
}
