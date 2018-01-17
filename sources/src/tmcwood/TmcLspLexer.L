
%option prefix = "tmclsp_"
%option yylineno
%option never-interactive

%{
//! SCanner for lsp-file parser
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/

#include <stdio.h>
#ifndef LINUX_GPL
#include <io.h>
#endif
#include <string.h>
#include <stdlib.h>

#include <string>
#include <list>

#define YY_NEVER_INTERACTIVE	1

#include "tmcpar_tree.h"


#define MAX_SRC_STRING 10000 // maximal constant string supported
static char* get_string(short bGershaim);
static long ReturnLspToken(long TokVal);
static void dbgPrintLspToken(long TokVal);

#include "TmcLspParser.tab.hpp"

%}

D	[0-9]
S	[ \t]
NL	((\n)|(\r)|(\r\n))
SNL	({S}|{NL})
LPAR	"("
RPAR  ")"

GERSHAIM  [\"]
EXPON	([DdEe][+-]?{D}+)
NUM	(({D}+\.?{D}*{EXPON}?)|(\.{D}+{EXPON}?)|(0[xX][0-9a-fA-F]+))
GERESH  "'"
%%
{NUM} {  tmclsp_lval.num=atof(tmclsp_text); return ReturnLspToken( NUMBER);}
{GERESH} {
			tmclsp_lval.str=get_string(0); return ReturnLspToken( STRING);}
{GERSHAIM} {
			strcpy(tmclsp_lval.ident,get_string(1)); return ReturnLspToken( IDENT);}

"nil" { return ReturnLspToken( NIL);}
"const" { return ReturnLspToken( TCONST);}
"c"		{ return ReturnLspToken( COL);}
"l"		{ return ReturnLspToken( LINE);}
"type"		{ return ReturnLspToken( TYPE);}
"statement"		{ return ReturnLspToken( STATEMENT);}
"func"		{ return ReturnLspToken( FUNC);}
"params"		{ return ReturnLspToken( PARAMS);}
"tree"		{ return ReturnLspToken( TREE);}
"statements"		{ return ReturnLspToken( STATEMENTS);}
"usr_func"		{ return ReturnLspToken( USR_FUNC);}
"ident"		{ return ReturnLspToken( TIDENT);}
"fnc_def"		{ return ReturnLspToken( FNC_DEF);}
"results"		{ return ReturnLspToken( RESULTS);}
"name"		{ return ReturnLspToken( NAME);}
"stmnt"		{ return ReturnLspToken( STMNT);}
"val"		{ return ReturnLspToken( VAL);}
"list"		{ return ReturnLspToken( LIST);}
"par"		{ return ReturnLspToken( PAR);}
"no_op_cmd"		{ return ReturnLspToken( NO_OP_CMD);}
"cmd"		{ return ReturnLspToken( CMD);}
"decl_cmd"		{ return ReturnLspToken( DECL_CMD);}
"decl"		{ return ReturnLspToken( DECL);}
"declars"		{ return ReturnLspToken( DECLARS);}

"op"		{ return ReturnLspToken( OP);}
"s_assign"		{ return ReturnLspToken( S_ASSIGN);}
"lhs"		{ return ReturnLspToken( LHS);}
"rhs"		{ return ReturnLspToken( RHS);}
"colon_expr"		{ return ReturnLspToken( COLON_EXPR);}
"base"		{ return ReturnLspToken( BASE);}
"lim"		{ return ReturnLspToken( LIM);}
"inc"		{ return ReturnLspToken( INC);}
"indx_expr" {; return ReturnLspToken( INDX_EXPR);}
"fn_expr" { return ReturnLspToken( FN_EXPR);}


"args" { return ReturnLspToken( ARGS);}
"e" { return ReturnLspToken( INDEXED_EXPR);}
 
"argument" { return ReturnLspToken( ARGUMENT);}
"field" { return ReturnLspToken( FIELD);}
"bin_expr" { return ReturnLspToken( BIN_EXPR);}
"bool_expr" { return ReturnLspToken( BOOL_EXPR);}
"return" { return ReturnLspToken( RETURN);}
"if_clause" { return ReturnLspToken( IF_CLAUSE);}
"if_cmds" { return ReturnLspToken( IF_CMDS);}
"if_exp" { return ReturnLspToken( IF_EXP);}
"if" { return ReturnLspToken( IF);}
"break" { return ReturnLspToken( BREAK);}
"continue" { return ReturnLspToken( CONTINUE);}
"while" { return ReturnLspToken( WHILE);}
"w_exp" { return ReturnLspToken( W_EXP);}
"sw_exp" { return ReturnLspToken( SW_EXP);}
"switch" {return ReturnLspToken( SWITCH);}
"sw_cases" { return ReturnLspToken( SW_CASES);}
"sw_case" { return ReturnLspToken( SW_CASE);}
"case_label" { return ReturnLspToken( CASE_LABEL);}
"cell" { return ReturnLspToken( CELL);}
"matrix" { return ReturnLspToken( MATRIX);}
"rows" { return ReturnLspToken( ROWS);}
"argument_list" { return ReturnLspToken( ARGUMENT_LIST);}
"arguments" { return ReturnLspToken( ARGUMENTS);}
"lmodify_exp" { return ReturnLspToken( LMODIFY_EXP);}
"reval_exp" { return ReturnLspToken( REVAL_EXP);}
"for" { return ReturnLspToken( FOR);}
"pfor" { return ReturnLspToken( PFOR);}
"operand" { return ReturnLspToken( OPERAND);}
"un_expr" { return ReturnLspToken( UN_EXPR);}
"func_handle" { return ReturnLspToken( FUNC_HANDLE);}
"multi_assign" { return ReturnLspToken( MULTI_ASSIGN);}
"try" { return ReturnLspToken( TRY);}
"trycode" { return ReturnLspToken( TRYCODE);}
"catchcode" { return ReturnLspToken( CATCHCODE);}
"until" { return ReturnLspToken( UNTIL);}
"u_exp" { return ReturnLspToken( U_EXP);}

":" { return ReturnLspToken( MAGIC_COL);}

      

{LPAR} {  return ReturnLspToken( LPAREN); }
{RPAR} {  return ReturnLspToken( RPAREN); }
"=" { return ReturnLspToken( EQ);};
{SNL} {}
"." {  return ReturnLspToken( END_OF_INPUT);}
<<EOF>> {  return ReturnLspToken( END_OF_INPUT);}
. {}
%%
static char str_buffer[MAX_SRC_STRING];
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
void reset_lsp_lexer()
{
	tmclsp_lval.str = str_buffer;
	
  	  //YY_BUFFER_STATE old_buf = current_buffer ();
	  //YY_BUFFER_STATE new_buf = create_buffer (tmclsp_in);
	  //switch_to_buffer (new_buf);

  // Start off on the right foot.
  BEGIN (INITIAL);
	
  yyrestart (tmclsp_in);// switch scanner to tmc_in. Must be used to protect agains parse error on
  // the previous file that had not been read until EOF !!!!
	
	
}
void dbgPrintLspToken(long TokVal)
{
	fprintf(stderr,"%Tok=%d, l=%d,c=%d ",TokVal,(int)tmclsp_lineno,0);
	if (TokVal==STRING)
		fprintf(stderr,"%s\n",tmclsp_lval.str);
	else if (TokVal==IDENT)
		fprintf(stderr,"%s\n",tmclsp_lval.ident);
	else 
		fprintf(stderr,"\n");
}
void reset_lspparser (void)
{
  tmclsp_lineno=0;
  
  reset_lsp_lexer();
  
 // if (parsing_module)
  //{
	//  delete parsing_module;
	//  parsing_module=NULL;
  //}

/*
//HSKOST:
  input_line_number = 1;
  current_input_column = 1;

  	  YY_BUFFER_STATE old_buf = current_buffer ();
	  YY_BUFFER_STATE new_buf = create_buffer (tmclsp_in);
	  switch_to_buffer (new_buf);

  // Start off on the right foot.
  BEGIN (INITIAL);

  parser_end_of_input = false;
  end_tokens_expected = 0;
  yyrestart (stdin);
*/
}
void tmclsp_error(const char *)
{
printf("fatal syntax eggog line=%d\n",(int)tmclsp_lineno);
if (Compiler.bUseDumpFile) fprintf(dump_file,"fatal syntax eggog line=%d\n",(int)tmclsp_lineno);
fprintf(stderr,"fatal syntax eggog line=%d\n",(int)tmclsp_lineno);
throw(CCompilerExcpt());
}
int tmclsp_wrap (void)
{
  return 1;
}

long ReturnLspToken(long TokVal)
{
//dbgPrintLspToken(TokVal);
	return TokVal;
}
