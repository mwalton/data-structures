// $Id: inssort.c,v 1.7 2013-12-04 20:02:17-08 - - $
// Michael Walton (mwwalton@ucsc.edu)

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include "inssort.h"

void inssort (void *base, size_t nelem, size_t size,
    int (*compar) (const void *, const void *)) {
  for (int sorted = 1; sorted < (int)nelem; ++sorted) {
    int slot = sorted;
    void *copy = malloc(size);
    memcpy(copy, (char *)(base + slot * size), size);

    for (; slot > 0; --slot) {
      int cmp = compar(copy, (char*)(base + (slot - 1) * size));
      if (cmp > 0) break;
      memcpy((char*)(base + slot * size),
          (char*)(base + (slot - 1) * size), size);
    }
    memcpy((char*)(base + slot * size), copy, size);
  }
}
