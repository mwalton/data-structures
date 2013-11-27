// $Id: yyextern.h,v 1.1 2013-05-09 17:56:36-07 - - $

#ifndef __YYEXTERN_H__
#define __YYEXTERN_H__

//
// DESCRIPTION
//    Definitions of external names used by flex-generated code.
//

#include <stdio.h>

// Returned by yylex() at end of file
#define YYEOF 0

// Returned by yylex() when yytext points at a number.
#define YYNUMBER 256

// File currently being read
extern FILE *yyin;

// Pointer to the string that was found
extern char *yytext;

// yylex's verbose tracing flag
extern int yy_flex_debug;

// Read next word from opened file yyin
extern int yylex (void);

// Line number within the current file
extern int yylineno;

// Cleans up flex's buffers when done
extern void yycleanup (void);

#endif

