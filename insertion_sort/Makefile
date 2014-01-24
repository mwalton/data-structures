# $Id: Makefile,v 1.5 2013-05-01 13:21:00-07 - - $
# Michael Walton (mwwalton@ucsc.edu)

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
GRIND     = valgrind --leak-check=full

CSOURCE   = inssort.c linesort.c numsort.c
CHEADER   = inssort.h
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = linesort numsort
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE}
SUBMITS   = ${CHEADER} ${CSOURCE} ${MKFILE} README
OUTPUT    = output*.lis
PROJECT   = cmps012b-wm.w13 lab9

all : linesort numsort

linesort : linesort.o inssort.o
	${GCC} -o linesort inssort.c linesort.c

numsort : numsort.o inssort.o
	${GCC} -o numsort inssort.c numsort.c

%.o : %.c
	cid + $<
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES} test*.data

lis : ${SOURCES} test
	mkpspdf ${LISTING} ${LISTSRC} ${OUTPUT}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core ${OUTPUT}

submit : ${SUBMITS}
	submit ${PROJECT} ${SUBMITS}
	
spotless : clean
	- rm ${EXECBIN} ${LISTING} ${LISTING:.ps=.pdf}

again :
	gmake spotless deps ci all lis

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif

