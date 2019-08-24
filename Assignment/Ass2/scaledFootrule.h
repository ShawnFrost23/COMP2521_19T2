//.h file for scaledFootrule.c
//Made by Arth Patel on 3rd Auguest 2019

#include <stdio.h>

//sort a given array with given length.
void sortArray(int *array, int length);

//findPosition function makes an array with the position of the urls
//e.g.
//url2
//url3
//url1
//the postion inputs the postions of these into the given array
//position[3,1,2]
//As url1 has 3rd position, url2 has 1st position, and url3 has 2nd position
void findPosition(int *posArray, int *unsortedArray, int *allUrls, int totLen);

//compute the final postion array by using the scale footrule distance.
void getFinalPostions(int *array, int pos[100][100], int *numUrls, int num, int i, int length);
