/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_TMCLSP_TMCLSPPARSER_TAB_HPP_INCLUDED
# define YY_TMCLSP_TMCLSPPARSER_TAB_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int tmclsp_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENT = 258,
     NUMBER = 259,
     STRING = 260,
     NIL = 261,
     LPAREN = 262,
     RPAREN = 263,
     EQ = 264,
     TCONST = 265,
     COL = 266,
     LINE = 267,
     TYPE = 268,
     STATEMENT = 269,
     FUNC = 270,
     USR_FUNC = 271,
     FNC_DEF = 272,
     PARAMS = 273,
     TREE = 274,
     STATEMENTS = 275,
     TIDENT = 276,
     RESULTS = 277,
     NAME = 278,
     STMNT = 279,
     VAL = 280,
     LIST = 281,
     PAR = 282,
     END_OF_INPUT = 283,
     NO_OP_CMD = 284,
     CMD = 285,
     DECL_CMD = 286,
     DECL = 287,
     DECLARS = 288,
     OP = 289,
     S_ASSIGN = 290,
     LHS = 291,
     RHS = 292,
     COLON_EXPR = 293,
     BASE = 294,
     LIM = 295,
     INC = 296,
     MULTI_ASSIGN = 297,
     OPERAND = 298,
     UN_EXPR = 299,
     INDX_EXPR = 300,
     FN_EXPR = 301,
     ARGS = 302,
     INDEXED_EXPR = 303,
     ARGUMENT = 304,
     FIELD = 305,
     BIN_EXPR = 306,
     BOOL_EXPR = 307,
     RETURN = 308,
     BREAK = 309,
     CONTINUE = 310,
     IF = 311,
     IF_EXP = 312,
     IF_CLAUSE = 313,
     IF_CMDS = 314,
     WHILE = 315,
     W_EXP = 316,
     SW_EXP = 317,
     SWITCH = 318,
     SW_CASES = 319,
     SW_CASE = 320,
     CASE_LABEL = 321,
     CELL = 322,
     MATRIX = 323,
     ROWS = 324,
     ARGUMENT_LIST = 325,
     ARGUMENTS = 326,
     LMODIFY_EXP = 327,
     REVAL_EXP = 328,
     FOR = 329,
     PFOR = 330,
     FUNC_HANDLE = 331,
     TRY = 332,
     TRYCODE = 333,
     CATCHCODE = 334,
     UNTIL = 335,
     U_EXP = 336,
     MAGIC_COL = 337
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 31 "TmcLspParser.Y"

	char   *str;
	double num;
	LSP_IDENT   ident;
	struct tree_const_val *lsp_const_val;

// expressions
	class T_ident *lsp_ident_val;
	class T_const   *lsp_constant_val;
	class T_expr_bin *lsp_binary_expression_val;
	class T_expr_bool *lsp_boolean_expression_val;
	class T_expr_unar *lsp_unary_expression_val;
	class T_expr_gen *lsp_expression_val;
	class T_expr_col *lsp_colon_expression_val;
	class L_args *lsp_argument_list_val;
	class tree_matrix *lsp_list_of_argument_list_val;
	class tree_matrix   *lsp_cell_val;
	class T_expr_index	*lsp_index_expression_val;
	class T_expr_assign_one *lsp_simple_assignment_val;
	class T_expr_assign_many *lsp_multi_assignment_val;
	class T_expr_func *lsp_fcn_handle_val;
// statements
	class T_stmnt_gen *lsp_statement_val;
//	class generic_tree *lsp_t_generic_val;
	class T_cmd_gen *lsp_command_val;
// commands
	class T_cmd_ctrl_return*	lsp_return_command_val;
	class T_cmd_decl_gen*	lsp_T_cmd_decl_gen_val;
	class T_cmd_ctrl_label*	lsp_T_cmd_ctrl_label_val;
	class T_ctrl_cmd_if*		lsp_T_ctrl_cmd_if_val;
	class T_ctrl_cmd_while*	lsp_T_ctrl_cmd_while_val;
	class T_ctrl_cmd_continue* lsp_T_ctrl_cmd_continue_val;
	class T_ctrl_cmd_break*	lsp_T_ctrl_cmd_break_val;
	class T_ctrl_cmd_switch*	lsp_T_ctrl_cmd_switch_val;
	class T_ctrl_cmd_try_catch*		lsp_tree_try_command_val;
	class T_ctrl_cmd_for*		lsp_T_ctrl_cmd_for_val;
	class T_func_hdr*    lsp_T_func_hdr_val;
	
// used in declarations	
	class L_vardecl*  lsp_L_vardecl_val;	
// used in if command
	class T_if_block*		lsp_T_if_block_val;
	class LT_if_blocks* lsp_LT_if_blocks_val; // list of clauses
// used in if,while,switch and for
	class L_stmnt_gen* lsp_L_stmnt_gen_val;
// used in switch
	class LT_sw_cases* lsp_LT_sw_cases_val;
	class T_sw_case*		 lsp_T_sw_case_val;
// used in function def
	class T_func_block*    lsp_T_func_block_val;
	


/* Line 2058 of yacc.c  */
#line 193 "TmcLspParser.tab.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE tmclsp_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int tmclsp_parse (void *YYPARSE_PARAM);
#else
int tmclsp_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int tmclsp_parse (void);
#else
int tmclsp_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_TMCLSP_TMCLSPPARSER_TAB_HPP_INCLUDED  */
