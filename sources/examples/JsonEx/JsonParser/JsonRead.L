
%option prefix = "Json_"
%option yylineno

%{
// flex file: JsonRead.l
#include "JsonRead.tab.h"
#include <string.h>

extern void yyerror(const char * message);
#define ECHO fwrite( yytext, yyleng, 1, yyout )

%}

%option noyywrap
EXP ([Ee][-+]?[0-9]+)

%%
 
 
"{" { ECHO; return LCURLY; }
"}" { ECHO; return RCURLY; }
"[" { ECHO; return LBRAC; }
"]" { ECHO; return RBRAC; }
"," { ECHO; return COMMA; }
":" { ECHO; return COLON; }
"true" { ECHO; return VTRUE; }
"false" { ECHO; return VFALSE; }
"null" { ECHO; return VNULL; }
"inf" { ECHO; return VINF; }
"-inf" { ECHO; return VMINF; }

[ \t\r\n]+ { /* eat whitespace */ }
\"[^"]*\" { Json_lval.string = strdup(yytext); ECHO; return STRING; }
[0-9]+\.?[0-9]*{EXP}? { ECHO; Json_lval.decimal = atof(yytext); return DECIMAL; }

%%
