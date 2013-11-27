# $Id: Makefile,v 1.11 2013-10-16 13:15:08-07 - - $
# Michael Walton (mwwalton@ucsc.edu)

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
CSOURCES = nsort.c lsort.c
SOURCES  = ${CSOURCES} Makefile
EXECBINS = nsort   lsort
LISTING  = Listing.ps
SUBMIT   = submit cmps012b-wm.f13 lab6

all : ${EXECBINS}

% : %.c
	${GCC} $< -o $@

ci :
	cid + ${SOURCES}
	- checksource $<

clean :
	- rm -vf core

spotless : clean
	- rm -vf ${EXECBINS}

lis : ${CSOURCES} Makefile
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

