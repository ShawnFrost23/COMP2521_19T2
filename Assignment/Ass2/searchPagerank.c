//implementation of searchPagerank.h
//Made by Arth Patel on 1st August 2019

#include "searchPagerank.h"

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <ctype.h>
#include <math.h>

//========= heading for helper functions go here =========
int fileNotInArray(char **array, char *word, int length);
void swapPageRank(double *pageR, int i, int j);
void swapFileName(char **fileArray, int i, int j);
void dropArray(char **array, int length);

//========= implementaion of helper functions =========
int fileNotInArray(char **array, char *word, int length) {
  int i = 0;
  while (i < length) {
    if (strcmp(word, array[i]) == 0) {
      return 1;
    }
    i += 1;
  }
  return 0;
}

void swapPageRank(double *pageR, int i, int j) {
  double tempPageRank;
  tempPageRank = pageR[j];
  pageR[j] = pageR[i];
  pageR[i] = tempPageRank;
}

void swapFileName(char **fileArray, int i, int j) {
  char *tempFileName;
  tempFileName = fileArray[j];
  fileArray[j] = fileArray[i];
  fileArray[i] = tempFileName;
}

void dropArray(char **array, int length) {
    int i = 0;
    while (i < length) {
        free(array[i]);
        i += 1;
    }
    free(array);
}

//========= Main function =========
int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Please enter search words\n");
    exit(0);
  }
  char **searchWords = NULL;
  int i = 1;
  int numWords = 0;
  //store our search words from command line to a searchWord array.
  while (i != argc) {
    searchWords = realloc(searchWords, (numWords + 1) * sizeof(char *));
    searchWords[numWords] = malloc(strlen(argv[i]) + 1);
    strcpy(searchWords[numWords++], argv[i]);
    i += 1;
  }

  char **foundURLs = NULL;
  int numURLs = 0;
  i = 0;
  int j = 0;
  char buffer[100];
  char newLine[100];
  FILE *wordListFile = fopen("invertedIndex.txt", "r");
  //scan the invertedIndex file for our search words.
  while (fscanf(wordListFile, "%s", buffer) != EOF && j < numWords) {
    //if a search word is present in the files
    //add all the urls the word is present in to our url array.
    i = 0;
    while (i < numWords) {
      if (strcmp(searchWords[i], buffer) == 0) {
        while (fscanf(wordListFile, "%s%[ \t\n]", buffer, newLine) == 2) {
          if (fileNotInArray(foundURLs, buffer, numURLs) == 0) {
            foundURLs = realloc(foundURLs, (numURLs + 1) * sizeof(char *));
            foundURLs[numURLs] = malloc(strlen(buffer) + 1);
            strcpy(foundURLs[numURLs++], buffer);
            if(strchr(newLine, '\n')){
              break;
            }
          }
        }
        j += 1;
      }
      i += 1;
    }
  }
  fclose(wordListFile);
  //check if the search words were actually there in the files.
  if (foundURLs == NULL) {
    printf("None of the search words matched in any file!\n" );
    exit(0);
  }
  //initialise page rank array for our found URLs.
  double *particularPRank = malloc(sizeof(double) * numURLs);
  particularPRank = getPageRanks(foundURLs, numURLs);

  //sort the array according to decreasing order of page rank.
  sortArray(foundURLs, particularPRank, numURLs);

  //print the out put to terminal.
  printToTerminal(foundURLs, numURLs);

  //free the allocated memory.
  free(particularPRank);

  dropArray(foundURLs, numURLs);

  dropArray(searchWords, numWords);

  return 0;
}

//========= implementaion of functions in pageRank.h =========
double *getPageRanks(char **array, int length) {
  double *returnArray = malloc(sizeof(double) * length);
  char buffer[100];
  char newLine[100];
  int i = 0, j = 0 ,count = 0;
  FILE *pageRankFile = fopen("pagerankList.txt", "r");
  //open the file and compare each word to the words in our array
  while (fscanf(pageRankFile,"%s", buffer) != EOF && j < length) {
    normalise(buffer);
    i = 0;
    while (i < length) {
      //if the words match then add them into our return array (pageRank).
      if(strcmp(array[i], buffer) == 0) {
        while (fscanf(pageRankFile, "%s%[ \t\n]", buffer, newLine) == 2) {
          if (strchr(newLine, '\n')) {
            returnArray[i] = atof(buffer);
            break;
          }
        }
        j += 1;
      }
      i += 1;
    }
  }
  fclose(pageRankFile);
  return returnArray;
}

void sortArray(char **urlArray, double *pageRankArray, int length) {
  int i = 0, j = 0;
  while (i < length) {
    j = 0;
    while (j < length) {
        if (pageRankArray[j] < pageRankArray[i]) {
          swapPageRank(pageRankArray, i, j);

          swapFileName(urlArray, i, j);

        }
      j += 1;
    }
    i += 1;
  }
}

void printToTerminal(char **array, int length) {
  int i = 0;
  while (i < length && i < 30) {
    printf("%s\n", array[i]);
    i += 1;
  }
}

void normalise(char *word) {
  int len = strlen(word);
  if (word[len - 1] == ',' || word[len - 1] == '.') {
    word[len - 1] = '\0';
  }
}
