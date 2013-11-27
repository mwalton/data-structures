%{
// $Id: scanner.l,v 1.1 2013-05-09 17:56:36-07 - - $

#include <stdlib.h>

#include "yyextern.h"

%}

%option 8bit
%option debug
%option ecs
%option interactive
%option nodefault
%option noyywrap
%option yylineno

WHITESPACE  ([ \t\n])
NUMBER      (_?[0-9]*)
OTHER       (.)

%%

{WHITESPACE}    { }
{NUMBER}        { return YYNUMBER; }
{OTHER}         { return *yytext; }

%%

void yycleanup (void) {
   yy_delete_buffer (YY_CURRENT_BUFFER);
}

