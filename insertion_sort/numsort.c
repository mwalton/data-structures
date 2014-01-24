// $Id: numsort.c,v 1.5 2013-12-04 20:54:34-08 - - $
// Michael Walton (mwwalton@ucsc.edu)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inssort.h"

int dblcmp(const void *a, const void *b) {
  if (*(double*)a > *(double*)b) return 1;
  else if (*(double*)a < *(double*)b) return -1;
  else return 0;
}

void print_num(double *arr, size_t length) {
  for (int i = 0; i < (int)length; ++i) {
    printf("%20.15g\n",arr[i]);
  }
}

int main(void) {
  double array[1000] = {0};
  int i;

  for(i = 0; i < 1000; ++i) {
    if (scanf("%lf",&array[i]) != 1) break;
  }

  const size_t len = (size_t)i;
  inssort(array, len, sizeof(array[0]), dblcmp);
  //qsort(array, len, sizeof(array[0]), dblcmp);
  print_num(array, len);
  return 0;
}
