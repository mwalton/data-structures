//$Id: inssort.h,v 1.3 2013-12-03 21:35:40-08 - - $
//Michael Walton (mwwalton@ucsc.edu)

#ifndef __INSSORT_H__
#define __INSSORT_H__

#include <stddef.h>

extern void inssort (void *base, size_t nelem, size_t size,
    int (*compar) (const void *, const void *));

#endif
