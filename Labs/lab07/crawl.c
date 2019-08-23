// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders
// <vince@kyllikki.org>

#include <ctype.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graph.h"
#include "html.h"
#include "set.h"
#include "stack.h"
#include "url_file.h"

#define BUFSIZE 1024

static void setFirstURL (char *, char *);

int main (int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int maxURLs;

	if (argc > 2) {
		strcpy (baseURL, argv[1]);
		setFirstURL (baseURL, firstURL);
		maxURLs = atoi (argv[2]);
		if (maxURLs < 40)
			maxURLs = 40;
	} else {
		fprintf (stderr, "Usage: %s BaseURL MaxURLs\n", argv[0]);
		exit (1);
	}

	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list

	// initialise Graph to hold up to maxURLs
	Graph newG = newGraph(maxURLs);
	Stack ToDoList = newStack();

	// initialise set of Seen URLs
	Set setOfSeenURLS = newSet();
	pushOnto(ToDoList, firstURL);
	// while (ToDo list not empty and Graph not filled) {
	while(!emptyStack(ToDoList) && nElems(setOfSeenURLS) < maxURLs) {
		char *link = popFrom(ToDoList);
		if (!(handle = url_fopen (firstURL, "r"))) {
			fprintf (stderr, "Couldn't open %s\n", next);
			exit (1);
		}
		while (!url_feof (handle)) {
			url_fgets (buffer, sizeof(buffer), handle);
			// fputs(buffer,stdout);
			int pos = 0;
			char result[BUFSIZE];
			memset (result, 0, BUFSIZE);
			while ((pos = GetNextURL(buffer, firstURL, result, pos)) > 0) {
				//check if the link is HTML
				//check that the last characters of link are ".html"
				int isHTML;
				char *suffix = ".html";
				isHTML = strcmp(result + strlen(result) - strlen(suffix), suffix) == 0;

				if(isHTML) {
					if (nVertices(newG) < maxURLs) {
						if (!isConnected(newG, link, result)) {
							addEdge(newG, link, result);
						}
					}
					if(!isElem(setOfSeenURLS, result)) {
						printf ("Found: '%s'\n", result);
						insertInto(setOfSeenURLS, result);
						pushOnto(ToDoList, result);
					}
				}
				memset (result, 0, BUFSIZE);
			}
		}
		url_fclose (handle);
		sleep (1);
	}
	showGraph(newG,1);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
static void setFirstURL (char *base, char *first)
{
	char *c;
	if ((c = strstr (base, "/index.html")) != NULL) {
		strcpy (first, base);
		*c = '\0';
	} else if (base[strlen (base) - 1] == '/') {
		strcpy (first, base);
		strcat (first, "index.html");
		base[strlen (base) - 1] = '\0';
	} else {
		strcpy (first, base);
		strcat (first, "/index.html");
	}
}
