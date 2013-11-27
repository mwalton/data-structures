// $Id: nsort.c,v 1.1 2011-04-29 19:46:42-07 - - $
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
  double item;
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
  char err_buffer [256];
  char err_buf_fmt[16];
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

  for (;;) {
    double number;
    int scancount = scanf ("%lg", &number);

    if (scancount == EOF) {
      for (node *curr = head; curr != NULL; curr = curr->link) {
        printf ("%24.15g\n", curr->item);
        if (debugMode) {
          printf ("%p -> struct node {item= %.15g, link= %p}\n",
              curr, curr->item, curr->link);
        }
      }
      break;
    }else if (scancount == 1) {
      //insertascending
      node *prev = NULL;
      node *curr = head;

      // Find the insertion position.
      while (curr != NULL) {
        if (curr->item > number) break;
        prev = curr;
        curr = curr->link;
      }

      // Do the insertion.
      node *tmp = malloc (sizeof (struct node));
      tmp->item = number;
      tmp->link = curr;
      if (prev == NULL) head = tmp;
      else prev->link = tmp;
    }else {
      scancount = scanf (err_buf_fmt, err_buffer);
      assert (scancount == 1);
      printf ("%s: bad number \"%s\"\n", progname, err_buffer);
      exit_status = EXIT_FAILURE;
    };
  };

  while (head != NULL) {
    node *old = head;
    head = head->link;
    free (old);
  }
  return exit_status;
}

