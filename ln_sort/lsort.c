// $Id: lsort.c,v 1.1 2011-04-29 19:46:42-07 - - $
// Michael Walton (mwwalton@ucsc.edu)

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int exit_status = EXIT_SUCCESS;

typedef struct node node;
struct node {
  char *item;
  node *link;
};

void emptyList(node *head) {
  while (head != NULL) {
    node *old = head;
    head = head->link;
    free (old);
  }
} 

int main (int argc, char **argv) {
  //(void) argc; // : unused parameter 'argc'
  char *progname = basename (argv[0]);
  char buffer[82];
  node *head = NULL;
  bool debugMode = false;
  //sprintf (err_buf_fmt, "%%%lds", sizeof err_buffer - 1);
  //printf ("err_buf_fmt = \"%s\"\n", err_buf_fmt);
  if (argc > 1) {
    if (strcmp(argv[1], "-d") == 0) debugMode = true;
    else {
      printf("%s: Invalid argument\n", progname);
      exit_status = EXIT_FAILURE;
    }
  } 
  if (argc > 2) {
    printf("%s:Too many arguments \n", progname);
    exit_status = EXIT_FAILURE;
  }

  int linenr;
  for (linenr = 1; ; ++linenr) {

    // Read a line of input and check to see if it ends with
    // a newline character.  Print a message if not.

    char *gotline = fgets (buffer, sizeof buffer, stdin);
    if (gotline == NULL) break;

    char *nlpos = strchr (buffer, '\n');
    if (nlpos != NULL) {
      *nlpos = '\0';
    }else {
      fprintf (stderr, "%s: %d: unterminated line: %s\n",
          progname, linenr, buffer);
    };
    /*if (scancount == EOF) {
      for (node *curr = head; curr != NULL; curr = curr->link) {
      printf ("%24.15g\n", curr->item);
      if (debugMode) {
      printf ("%p -> struct node {item= %.15g, link= %p}\n",
      curr, curr->item, curr->link);
      }
      }*/
    //insertascending
    node *prev = NULL;
    node *curr = head;

    // Find the insertion position.
    while (curr != NULL) {
      if (strcmp(curr->item, buffer) > 0) break;
      prev = curr;
      curr = curr->link;
    }

    // Do the insertion.
    node *tmp = malloc (sizeof (struct node));
    tmp->item = strdup (buffer);
    assert (tmp->item != NULL);
    tmp->link = curr;
    if (prev == NULL) head = tmp;
    else prev->link = tmp;
  };

  for (node *curr = head; curr != NULL; curr = curr->link) {
    printf ("%s\n", curr->item);
    if (debugMode) {
      printf ("%p -> struct node {item= %s, link= %p}\n",
          curr, curr->item, curr->link);
    }
  }

  while (head != NULL) {
    node *old = head;
    head = head->link;
    free (old);
  }
  return exit_status;
  }

