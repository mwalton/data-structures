# $Id: Makefile,v 1.3 2013-11-06 15:14:45-08 - - $
# Michael Walton (mwwalton@ucsc.edu)
# Brandon Butler (bpbutler@ucsc.edu)

JAVASRC    = bitreecalc.java bitree.java linked_stack.java \
             symbol_table.java auxlib.java
SOURCES    = ${JAVASRC} Makefile README
MAINCLASS  = bitreecalc
CLASSES    = ${JAVASRC:.java=.class}
JARCLASSES = ${CLASSES} linked_stack\$$node.class
JARFILE    = bitreecalc
LISTING    = Listing.ps
SUBMITDIR  = cmps012b-wm.f13 asg3

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	javac $<

clean :
	- rm ${JARCLASSES} Manifest

spotless : clean
	- rm ${JARFILE}

ci : ${SOURCES}
	- checksource ${SOURCES}
	cid + ${SOURCES}

lis : ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}
	testsubmit ${SUBMITDIR} ${SOURCES}

again :
	gmake --no-print-directory spotless ci all lis

