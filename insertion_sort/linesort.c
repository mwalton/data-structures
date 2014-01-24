// $Id: linesort.c,v 1.18 2013-12-04 20:53:35-08 - - $
// Michael Walton (mwwalton@ucsc.edu)

#include "inssort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strstrcmp (const void *this, const void *that) {
  char **thisstr = (char**) this;
  char **thatstr = (char**) that;
  return strcmp (*thisstr, *thatstr);
}

void print_str(char **arr, size_t length) {
  for (int i = 0; i < (int)length; ++i) {
    printf("%s\n",arr[i]);
  }
}

int main(void) {
  char *array[1000];
  int i;

  for(i = 0; i < 1000; ++i) {
    char buffer[1000];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
    strtok(buffer, "\n");
    array[i] = malloc(strlen(buffer));
    strcpy(array[i],buffer);
  }

  //const size_t nelem = sizeof array / sizeof *array;
const size_t nelem = (size_t)i;
  //print_str (array, i);
  inssort (array, nelem, sizeof *array, strstrcmp);
  print_str (array, nelem);
  return 0;
}
