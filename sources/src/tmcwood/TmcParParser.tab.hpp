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

#ifndef YY_TMCPAR_TMCPARPARSER_TAB_HPP_INCLUDED
# define YY_TMCPAR_TMCPARPARSER_TAB_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int tmcpar_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENT = 258,
     NUMBER = 259,
     NUMBER_IM = 260,
     STRING = 261,
     PLUS = 262,
     MINUS = 263,
     MUL = 264,
     EMUL = 265,
     AND = 266,
     OR = 267,
     DIV = 268,
     EDIV = 269,
     POW = 270,
     EPOW = 271,
     LDIV = 272,
     ELDIV = 273,
     LE = 274,
     LT = 275,
     GE = 276,
     GT = 277,
     NE = 278,
     EQL = 279,
     BOOL_AND = 280,
     BOOL_OR = 281,
     TRANSPOSE = 282,
     CTRANSPOSE = 283,
     NOT = 284,
     ASG = 285,
     LPAREN = 286,
     RPAREN = 287,
     LC = 288,
     RC = 289,
     LBRA = 290,
     RBRA = 291,
     SM = 292,
     CM = 293,
     LINE = 294,
     COMAT = 295,
     COLON = 296,
     ELLIP = 297,
     MAGIC_END = 298,
     LEXERROR = 299,
     UNARYMINUS = 300,
     UNARYPLUS = 301,
     UNARYNOT = 302,
     END_OF_INPUT = 303,
     NO_OP_CMD = 304,
     RETURN = 305,
     BREAK = 306,
     CONTINUE = 307,
     IF = 308,
     ELSEIF = 309,
     ELSE = 310,
     END = 311,
     WHILE = 312,
     SWITCH = 313,
     CASE = 314,
     OTHERWISE = 315,
     FOR = 316,
     FUNC_HANDLE = 317,
     TRY = 318,
     CATCH = 319,
     FUNCTION = 320,
     GLOBAL = 321
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 24 "TmcParParser.y"

	char   *str;
	double num;
	LSP_IDENT   ident;
	struct tree_const_val *lsp_const_val;
	long int_value;
	
	short lsp_delimiter;
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
#line 178 "TmcParParser.tab.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE tmcpar_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int tmcpar_parse (void *YYPARSE_PARAM);
#else
int tmcpar_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int tmcpar_parse (void);
#else
int tmcpar_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_TMCPAR_TMCPARPARSER_TAB_HPP_INCLUDED  */
