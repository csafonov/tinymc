
%option prefix = "tmcpar_"
%option yylineno
%option never-interactive

%{
//! Scanner for m-file parser
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/

#include <stdio.h>
#ifndef LINUX_GPL
#include <io.h>
#else
//#define __cdecl 
#endif

#include <string.h>
#include <stdlib.h>

#include <string>
#include <list>

#define YY_NEVER_INTERACTIVE	1

#include "tmcpar_tree.h"
#include "tmcpar_utils.h"

#define MAX_SRC_STRING 10000 // maximal constant string supported
static char* get_string(short bGershaim);
static long ReturnLspToken(long TokVal);
static void dbgPrintLspToken(long TokVal);
void reset_tmcpar_lexer();



void yyunput_elipse_of_element_op(void);

#include "TmcParParser.tab.hpp"

char* alloc_string(long sz)
{
	char *c = (char*)malloc(sizeof(char)*sz);
	return c;
}


char* get_identifier();

// We have 2 states for GERESH treatment:
//  INITIAL:			treated as start of string
//  ExpectQuoteAsCTRANSPOSE:	treated as CTRANSPOSE (follows immediately NUMBER,NUMBER_IM,TRANSPOSE,CTRANSPOSE,],)

%}

%Start   ExpectQuoteAsCTRANSPOSE


D	[0-9]
S	[ \t]
NL	((\n)|(\r)|(\r\n))
SNL	({S}|{NL})
LPAR	"("
RPAR  ")"
LB	"["
RB  "]"
COMMA  ","
GERSHAIM  [\"]
EXPON	([DdEe][+-]?{D}+)
NUM	(({D}+\.?{D}*{EXPON}?)|(\.{D}+{EXPON}?)|(0[xX][0-9a-fA-F]+))
GERESH  "'"
IDENTIFIER [a-zA-Z][_a-zA-Z0-9]*

HSPACE [ \t]
HSPACES {HSPACE}+
NEWLINE \n|\r|\f
NEWLINES {NEWLINE}+


ELLIPSIS \.\.\.
CONTINUATION {ELLIPSIS}[^\n\r\f]*{NEWLINE}?

COMMENT \%[^\n\r\f]*{NEWLINE}?
IMAGINARYUNIT [ij]
%%


{HSPACES} {BEGIN(INITIAL);}

{CONTINUATION} {
				}
				
{NUM}{IMAGINARYUNIT} {BEGIN(ExpectQuoteAsCTRANSPOSE);
	*(yytext+yyleng-1) = '\0'; tmcpar_lval.num=atof(tmcpar_text);
	 yyinsert_comma_in_input(NUMBER_IM);
	 yyunput_elipse_of_element_op();
	 return ReturnLspToken( NUMBER_IM);
}

{NUM} {BEGIN(ExpectQuoteAsCTRANSPOSE);
  tmcpar_lval.num=atof(tmcpar_text);
	yyinsert_comma_in_input(NUMBER);
	yyunput_elipse_of_element_op();
	return ReturnLspToken( NUMBER);}
 
"return" { return ReturnLspToken( RETURN);}
"if" { return ReturnLspToken( IF);}
"elseif" { return ReturnLspToken( ELSEIF);}
"else" { return ReturnLspToken( ELSE);}
"break" { return ReturnLspToken( BREAK);}
"continue" { return ReturnLspToken( CONTINUE);}
"while" { return ReturnLspToken( WHILE);}
"switch" {return ReturnLspToken( SWITCH);}
"case" {return ReturnLspToken( CASE);}
"otherwise" {return ReturnLspToken( OTHERWISE);}
"for" { return ReturnLspToken( FOR);}
"try" { return ReturnLspToken( TRY);}
"catch" { return ReturnLspToken( CATCH);}
"function" { return ReturnLspToken( FUNCTION);}
"global" { return ReturnLspToken( GLOBAL);}
"endfunction" {  return ReturnLspToken( END_OF_INPUT); } // HAZARD: added for OCTAVE syntax support
"end" {
	if (get_indexdeep()>0)
	{
		return ReturnLspToken( MAGIC_END); //like x(end-1)
	}
	else
	{
		 unput(';');return ReturnLspToken( END); //like if .. end
	}
 }


<INITIAL>'[^'\n\r\f]*'/' {
							yymore();
							}
							
<INITIAL>'[^'\r\f\n]*' {

		register int i, size;
		char* modified;
		const int length = yyleng-2;
		for (size = 0, i = 1;
		i <= length; size++, i++)
		if (*(yytext+i) == '\'')
		i++;
		modified = alloc_string(size+1);
		*(modified+size) = '\0';
		for (size = 0, i = 1;
		i <= length; size++, i++)
		{
		*(modified+size) = *(yytext+i);
		if (*(yytext+i) == '\'')
		i++;
		}
		tmcpar_lval.str = modified;

	yyinsert_comma_in_input(STRING);

	return ReturnLspToken( STRING);
}

{IDENTIFIER} {
 BEGIN(ExpectQuoteAsCTRANSPOSE);
 get_identifier();
 //tmcpar_lval.str
 yyinsert_comma_in_input(IDENT);
 return ReturnLspToken( IDENT);}

\.'			 {BEGIN(ExpectQuoteAsCTRANSPOSE);
			  tmcpar_lval.int_value = TRANSPOSE; return ReturnLspToken( TRANSPOSE ); }
			  
<ExpectQuoteAsCTRANSPOSE>'   {
			tmcpar_lval.int_value = CTRANSPOSE; return ReturnLspToken( CTRANSPOSE );  }
			
			
<INITIAL>'	 {
			 tmcpar_lval.int_value = LEXERROR; return ReturnLspToken( LEXERROR );  }


"+"          {BEGIN(INITIAL); tmcpar_lval.int_value = PLUS; return ReturnLspToken( PLUS ); }
"-"          {BEGIN(INITIAL); tmcpar_lval.int_value = MINUS; return ReturnLspToken( MINUS ); }
".*"          {BEGIN(INITIAL); tmcpar_lval.int_value = EMUL; return ReturnLspToken( EMUL ); }
"*"          {BEGIN(INITIAL); tmcpar_lval.int_value = MUL; return ReturnLspToken( MUL ); }
"&&"         {BEGIN(INITIAL); tmcpar_lval.int_value = BOOL_AND; return ReturnLspToken( BOOL_AND ); }
"||"         {BEGIN(INITIAL); tmcpar_lval.int_value = BOOL_OR; return ReturnLspToken( BOOL_OR ); }
"&"          {BEGIN(INITIAL); tmcpar_lval.int_value = AND; return ReturnLspToken( AND ); }
"|"          {BEGIN(INITIAL); tmcpar_lval.int_value = OR; return ReturnLspToken( OR ); }
"./"          {BEGIN(INITIAL); tmcpar_lval.int_value = EDIV; return ReturnLspToken( EDIV ); }
"/"          {BEGIN(INITIAL); tmcpar_lval.int_value = DIV; return ReturnLspToken( DIV ); }
".^"          {BEGIN(INITIAL); tmcpar_lval.int_value = EPOW; return ReturnLspToken( EPOW ); }
"^"          {BEGIN(INITIAL); tmcpar_lval.int_value = POW; return ReturnLspToken( POW ); }
\.\\          {BEGIN(INITIAL); tmcpar_lval.int_value = ELDIV; return ReturnLspToken( ELDIV ); }
\\          {BEGIN(INITIAL); tmcpar_lval.int_value = LDIV; return ReturnLspToken( LDIV ); }
">="         {BEGIN(INITIAL); tmcpar_lval.int_value = GE; return ReturnLspToken( GE ); }
"<="         {BEGIN(INITIAL); tmcpar_lval.int_value = LE; return ReturnLspToken( LE ); }
"=="         {BEGIN(INITIAL); tmcpar_lval.int_value = EQL; return ReturnLspToken( EQL ); }
"~="         {BEGIN(INITIAL); tmcpar_lval.int_value = NE; return ReturnLspToken( NE ); }
"<"          {BEGIN(INITIAL); tmcpar_lval.int_value = LT; return ReturnLspToken( LT ); }
">"          {BEGIN(INITIAL); tmcpar_lval.int_value = GT; return ReturnLspToken( GT ); }

"~"          {BEGIN(INITIAL); tmcpar_lval.int_value = NOT; return ReturnLspToken( NOT ); }
"="          {BEGIN(INITIAL); tmcpar_lval.int_value = ASG; return ReturnLspToken( ASG ); }
"("          {BEGIN(INITIAL); return ReturnLspToken( LPAREN ); }
")"          { BEGIN(ExpectQuoteAsCTRANSPOSE); 
					return ReturnLspToken( RPAREN ); }
"{"          {BEGIN(INITIAL); return ReturnLspToken( LC ); }
"}"          { BEGIN(ExpectQuoteAsCTRANSPOSE);
				    return ReturnLspToken( RC ); }
"["          {BEGIN(INITIAL); return ReturnLspToken( LBRA ); }
"]"          { BEGIN(ExpectQuoteAsCTRANSPOSE);
				    return ReturnLspToken( RBRA ); }
","          { BEGIN(INITIAL);return ReturnLspToken( CM ); }
";"          { BEGIN(INITIAL);return ReturnLspToken( SM ); }
"@"          {BEGIN(INITIAL); return ReturnLspToken( COMAT ); }
":"          {BEGIN(INITIAL); return ReturnLspToken( COLON ); }
"."          { return ReturnLspToken( ELLIP ); }

{HSPACES}\.' { return ReturnLspToken( LEXERROR ); }


{NEWLINES}   {BEGIN(INITIAL);
 return ReturnLspToken( LINE ); }

{COMMENT} { BEGIN(INITIAL);
return ReturnLspToken( LINE ); }


{SNL} {}
<<EOF>> {
  // add a LINE at the end of the file to avoid commands without delimiter
  if (lexer_at_end_file)
     return ReturnLspToken( END_OF_INPUT);
  else
    {
     lexer_at_end_file++;
     return ReturnLspToken( LINE);
    }
  }
. {}
%%

//<S>";"          { return ReturnLspToken( SM ); }
//<S>{COMMENT_START}          {
//					BEGIN COM;
//				}
//<COM>{NL}       {
//					 BEGIN S;
//				}

//E.g.:
//BEGIN(ExpectQuoteAsCTRANSPOSE);*(yytext+yyleng-1) = ’\0’;yylval.imaginaryQ =atof(yytext);Return("IMAGINARY", IMAGINARY);


char str_buffer[MAX_SRC_STRING];
char* get_string(short bGershaim)
{
  int k=0;
  int c;
  char delim = bGershaim ? '\"' : '\'';
  str_buffer[k++]=delim;
  str_buffer[1]=0;
  while ((c = yyinput ()) != EOF)
  {
	
	
	str_buffer[k++]=c;
	//if ((bGershaim==0) && (c==  '\"'))
	//{ // translate " -> ""
	//	str_buffer[k++]='\"';
	//}
	
	
	if (c==delim)
	{
	
		// check if we have twice '
		c=yyinput();
		if (c != delim)
		{
			unput(c);
			str_buffer[k]=0;
			if (k>0)
				str_buffer[k-1]=0;
				//str_buffer[k++]=0;
			return &str_buffer[1];
		}
		else
		{
		// go to the next letter
		}
	}
  }
  return &str_buffer[1];
}

char str_buffer2[MAX_SRC_STRING];

char* get_identifier()
{
//yyleng is length
//yytext is src
  strcpy(&tmcpar_lval.ident[0],yytext);
  return &tmcpar_lval.ident[0];
}

void reset_tmcpar_lexer()
{
	tmcpar_lval.str = str_buffer;
	
  	  //YY_BUFFER_STATE old_buf = current_buffer ();
	  //YY_BUFFER_STATE new_buf = create_buffer (tmc_in);
	  //switch_to_buffer (new_buf);

  // Start off on the right foot.
  BEGIN (INITIAL);
	
  yyrestart (tmc_in);// switch scanner to tmc_in. Must be used to protect agains parse error on
  // the previous file that had not been read until EOF !!!!
	
  lexer_indexdeep=0;
  lexer_at_end_file=0;
}
////////// LEXER UTILS ///////////////
void yyunput_elipse_of_element_op(void)
{
 //   3.*y must be like 3 .* y and not like 3. * y   
 int latest;
 int current;
 
 latest = *(yytext+yyleng-1);
 if (latest != '.')
 {
		return;
 }
 
 current = yyinput();
 {
	if (current=='/' || current=='*' || current=='\\' || current=='^' )
	{
		unput(current);
		unput('.');	// HAZARD_TODO: put warning here
	}
	else
	{
		unput(current);
	}
 }
}


#define LD LBRA

void yyinsert_comma_in_input(const int lastToken)
{//HAZARD: check for '{' and '.'
int count, current, next;

if (lastToken==END)
{
    unput(';');
	return;
}

if (!(BracketDelimiter == LBRA || BracketDelimiter == LD))
return;
for (count = 1; ; count++)
{
current = yyinput();
if (current != ' ' && current != '\t')
break;
}
if (current == ',' || current == ';' || current == ']' ||
current == '*' || current == '^' || current == ':' ||
current == '<' || current == '>' || current == '=' ||
current == '&' || current == '|' ||
current == '/' || current == '\\' ||
current == '\n' || current == '\r' || current == '\f' ||
current == '%' || current == '.' || //HSKOST added '.' for  fields
(current == '\'' && count == 1))
{
unput(current);
return;
}
if ((current == '(' ||current == '{' || current == '.') &&
(BracketDelimiter == LD ||
(lastToken == IDENT && count == 1)))
{
unput(current);
return;
}
if (isalpha(current) &&
(lastToken == NUMBER || lastToken == NUMBER_IM) && count == 1)
{
unput(current);
return;
}
next = yyinput();
++count;
if (current == '.' &&
(next == '\'' || next == '*' || next == '^' ||
next == '/' || next == '\\' || next == '.'))
{
unput(next);
unput('.');
if (next == '\'' && count > 2)
unput(' ');
return;
}
if (current == '~' && next == '=')
{
unput('=');
unput('~');
return;
}
if (current == '+' || current == '-')
{
if (count == 2 || next == ' ' || next == '\t')
{
unput(next);
unput(current);
return;
}
}
unput(next);
unput(current);
unput(',');
}
//////
int  tmc_parse(void)
{
	tmcpar_parse();
	return 1;
}
void  reset_parser(void)
{
	tmcpar_lineno=1;tmcpar_colno=0;
	tmcpar_parsing_module=NULL; // tree result of the parsing
	reset_tmcpar_lexer();
}
void tmcpar_error(const char *)
{
	printf("%s(%d) : error P0001: fatal syntax error\n",curr_fcn_file_full_name.c_str(),(int)tmcpar_lineno);
if (Compiler.bUseDumpFile) fprintf(dump_file,"%s(%d) : error P0001: fatal syntax error\n",curr_fcn_file_full_name.c_str(),(int)tmcpar_lineno);
fprintf(stderr,"%s(%d) : error P0001: fatal syntax error\n",curr_fcn_file_full_name.c_str(),(int)tmcpar_lineno);
throw(CCompilerExcpt());
}
int tmcpar_wrap (void)
{
  return 1;
}
void dbgPrintLspToken(long TokVal)
{
	fprintf(stderr,"Tok=%d, l=%d,c=%d,int_value=%d ",TokVal,(int)tmcpar_lineno,0,tmcpar_lval.int_value);
	if (TokVal==STRING)
		fprintf(stderr,"%s\n",tmcpar_lval.str);
	else if (TokVal==IDENT)
		fprintf(stderr,"%s\n",tmcpar_lval.ident);
	else 
		fprintf(stderr,"\n");
}
long ReturnLspToken(long TokVal)
{
#ifdef _DEBUG
	dbgPrintLspToken(TokVal);
#endif
	return TokVal;
}
