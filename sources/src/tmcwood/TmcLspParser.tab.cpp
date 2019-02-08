/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         tmclsp_parse
#define yylex           tmclsp_lex
#define yyerror         tmclsp_error
#define yylval          tmclsp_lval
#define yychar          tmclsp_char
#define yydebug         tmclsp_debug
#define yynerrs         tmclsp_nerrs

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 2 "TmcLspParser.y"

//! Gramma for lsp-file parser
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


#include "tmcpar_tree.h"
#include "tmcpar_utils.h"


/* Line 371 of yacc.c  */
#line 100 "TmcLspParser.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "TmcLspParser.tab.hpp".  */
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
/* Line 387 of yacc.c  */
#line 31 "TmcLspParser.y"

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
	


/* Line 387 of yacc.c  */
#line 279 "TmcLspParser.tab.cpp"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 307 "TmcLspParser.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   566

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNRULES -- Number of states.  */
#define YYNSTATES  555

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   337

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    26,    44,    68,    83,
      98,   100,   102,   104,   106,   108,   110,   112,   114,   116,
     118,   120,   122,   124,   128,   130,   132,   134,   136,   138,
     140,   142,   144,   146,   148,   155,   157,   159,   162,   164,
     171,   177,   179,   182,   184,   199,   217,   219,   224,   226,
     228,   232,   239,   241,   265,   289,   310,   312,   314,   335,
     342,   344,   347,   368,   392,   416,   437,   452,   467,   482,
     489,   491,   494,   496,   505,   517,   529,   541,   559,   574,
     589,   596,   598,   601,   603,   621,   639,   657,   664,   666,
     669,   671,   689,   691,   712
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      84,     0,    -1,    85,    28,    -1,    86,    -1,    85,    86,
      -1,     7,    19,     9,    14,    12,     9,     4,    11,     9,
       4,    24,     9,    87,     8,    -1,     7,    19,     9,    17,
      12,     9,     4,    11,     9,     4,    23,     9,     3,    15,
       9,    88,     8,    -1,     7,    19,     9,    16,    12,     9,
       4,    11,     9,     4,    23,     9,     3,    18,     9,    93,
      22,     9,    93,    20,     9,    95,     8,    -1,     7,    19,
       9,    14,    12,     9,     4,    11,     9,     4,    24,     9,
      90,     8,    -1,     7,    19,     9,    14,    12,     9,     4,
      11,     9,     4,    24,     9,    92,     8,    -1,    97,    -1,
      91,    -1,    98,    -1,   104,    -1,   102,    -1,   105,    -1,
     110,    -1,   111,    -1,   112,    -1,   113,    -1,   114,    -1,
     115,    -1,   103,    -1,     7,     6,     8,    -1,   119,    -1,
     122,    -1,   123,    -1,   124,    -1,   128,    -1,   121,    -1,
     120,    -1,   129,    -1,   134,    -1,   135,    -1,     7,    26,
       9,    27,    94,     8,    -1,    91,    -1,    97,    -1,    94,
      97,    -1,     6,    -1,     7,    26,     9,    14,    96,     8,
      -1,     7,    26,     9,    14,     8,    -1,    89,    -1,    96,
      89,    -1,     6,    -1,     7,    19,     9,    21,    12,     9,
       4,    11,     9,     4,    23,     9,     3,     8,    -1,     7,
      19,     9,    10,    12,     9,     4,    11,     9,     4,    13,
       9,     3,    25,     9,    99,     8,    -1,     4,    -1,     7,
       4,     4,     8,    -1,     5,    -1,    91,    -1,     7,    82,
       8,    -1,     7,    26,     9,    32,   101,     8,    -1,    94,
      -1,     7,    19,     9,    35,    12,     9,     4,    11,     9,
       4,    13,     9,     4,    34,     9,     3,    36,     9,    90,
      37,     9,    90,     8,    -1,     7,    19,     9,    42,    12,
       9,     4,    11,     9,     4,    13,     9,     4,    34,     9,
       3,    36,     9,   118,    37,     9,    90,     8,    -1,     7,
      19,     9,    38,    12,     9,     4,    11,     9,     4,    39,
       9,    90,    40,     9,    90,    41,     9,    90,     8,    -1,
     106,    -1,   109,    -1,     7,    19,     9,    45,    12,     9,
       4,    11,     9,     4,    13,     9,     3,    47,     9,   107,
      48,     9,    90,     8,    -1,     7,    26,     9,    49,   108,
       8,    -1,    90,    -1,   108,    90,    -1,     7,    19,     9,
      46,    12,     9,     4,    11,     9,     4,    13,     9,     3,
      50,     9,     3,    48,     9,    90,     8,    -1,     7,    19,
       9,    51,    12,     9,     4,    11,     9,     4,    13,     9,
       4,    34,     9,     3,    36,     9,    90,    37,     9,    90,
       8,    -1,     7,    19,     9,    52,    12,     9,     4,    11,
       9,     4,    13,     9,     4,    34,     9,     3,    36,     9,
      90,    37,     9,    90,     8,    -1,     7,    19,     9,    44,
      12,     9,     4,    11,     9,     4,    13,     9,     4,    34,
       9,     3,    43,     9,    90,     8,    -1,     7,    19,     9,
      67,    12,     9,     4,    11,     9,     4,    69,     9,   116,
       8,    -1,     7,    19,     9,    68,    12,     9,     4,    11,
       9,     4,    69,     9,   116,     8,    -1,     7,    19,     9,
      76,    12,     9,     4,    11,     9,     4,    23,     9,     3,
       8,    -1,     7,    26,     9,    70,   117,     8,    -1,   118,
      -1,   117,   118,    -1,    91,    -1,     7,    19,     9,    70,
      71,     9,   107,     8,    -1,     7,    19,     9,    53,    12,
       9,     4,    11,     9,     4,     8,    -1,     7,    19,     9,
      54,    12,     9,     4,    11,     9,     4,     8,    -1,     7,
      19,     9,    55,    12,     9,     4,    11,     9,     4,     8,
      -1,     7,    19,     9,    31,    12,     9,     4,    11,     9,
       4,    32,     9,     3,    33,     9,   100,     8,    -1,     7,
      19,     9,    29,    12,     9,     4,    11,     9,     4,    30,
       9,     3,     8,    -1,     7,    19,     9,    56,    12,     9,
       4,    11,     9,     4,    59,     9,   125,     8,    -1,     7,
      26,     9,    58,   126,     8,    -1,   127,    -1,   126,   127,
      -1,    91,    -1,     7,    19,     9,    58,    12,     9,     4,
      11,     9,     4,    57,     9,    90,    20,     9,    95,     8,
      -1,     7,    19,     9,    60,    12,     9,     4,    11,     9,
       4,    61,     9,    90,    20,     9,    95,     8,    -1,     7,
      19,     9,    63,    12,     9,     4,    11,     9,     4,    62,
       9,    90,    64,     9,   130,     8,    -1,     7,    26,     9,
      65,   131,     8,    -1,   132,    -1,   131,   132,    -1,    91,
      -1,     7,    19,     9,    65,    12,     9,     4,    11,     9,
       4,    66,     9,   133,    20,     9,    95,     8,    -1,    90,
      -1,     7,    19,     9,    74,    12,     9,     4,    11,     9,
       4,    72,     9,    90,    73,     9,    90,    20,     9,    95,
       8,    -1,     7,    19,     9,    77,    12,     9,     4,    11,
       9,     4,    78,     9,    95,    79,     9,    95,     8,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   157,   157,   166,   170,   187,   193,   199,   205,   209,
     215,   219,   223,   227,   231,   235,   239,   243,   247,   251,
     255,   259,   263,   268,   272,   276,   280,   284,   288,   292,
     296,   300,   304,   312,   334,   338,   344,   348,   352,   357,
     361,   366,   370,   374,   379,   384,   390,   394,   398,   402,
     407,   412,   418,   424,   429,   434,   440,   444,   449,   454,
     459,   463,   468,   474,   480,   486,   491,   496,   502,   507,
     512,   516,   520,   525,   531,   536,   541,   546,   551,   556,
     561,   567,   571,   575,   581,   587,   595,   601,   607,   611,
     615,   620,   625,   630,   640
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "NUMBER", "STRING", "NIL",
  "LPAREN", "RPAREN", "EQ", "TCONST", "COL", "LINE", "TYPE", "STATEMENT",
  "FUNC", "USR_FUNC", "FNC_DEF", "PARAMS", "TREE", "STATEMENTS", "TIDENT",
  "RESULTS", "NAME", "STMNT", "VAL", "LIST", "PAR", "END_OF_INPUT",
  "NO_OP_CMD", "CMD", "DECL_CMD", "DECL", "DECLARS", "OP", "S_ASSIGN",
  "LHS", "RHS", "COLON_EXPR", "BASE", "LIM", "INC", "MULTI_ASSIGN",
  "OPERAND", "UN_EXPR", "INDX_EXPR", "FN_EXPR", "ARGS", "INDEXED_EXPR",
  "ARGUMENT", "FIELD", "BIN_EXPR", "BOOL_EXPR", "RETURN", "BREAK",
  "CONTINUE", "IF", "IF_EXP", "IF_CLAUSE", "IF_CMDS", "WHILE", "W_EXP",
  "SW_EXP", "SWITCH", "SW_CASES", "SW_CASE", "CASE_LABEL", "CELL",
  "MATRIX", "ROWS", "ARGUMENT_LIST", "ARGUMENTS", "LMODIFY_EXP",
  "REVAL_EXP", "FOR", "PFOR", "FUNC_HANDLE", "TRY", "TRYCODE", "CATCHCODE",
  "UNTIL", "U_EXP", "MAGIC_COL", "$accept", "module", "list_function",
  "func_def_statement", "fnc_def", "T_func_block", "statement",
  "expression", "nil", "command", "t_list_par", "list_par",
  "t_list_statement", "list_statement", "ident", "const", "variant_val",
  "t_list_decl", "list_ident", "s_assign", "multi_assign", "colon_expr",
  "indx_expr", "by_index", "t_list_argument", "list_argument", "by_field",
  "bin_expr", "bool_expr", "un_expr", "cell", "matrix", "fcn_handle",
  "t_list_of_argument_list", "list_of_argument_list", "argument_list",
  "return", "break", "continue", "decl_cmd", "no_op_cmd", "if",
  "t_if_clause", "list_if_clause", "if_clause", "while", "switch",
  "t_switch_case", "list_switch_case", "switch_case", "case_label", "for",
  "try", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    85,    85,    86,    87,    88,    89,    89,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    93,    93,    94,    94,    94,    95,
      95,    96,    96,    96,    97,    98,    99,    99,    99,    99,
      99,   100,   101,   102,   103,   104,   105,   105,   106,   107,
     108,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   117,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   126,   126,   127,   128,   129,   130,   131,   131,
     131,   132,   133,   134,   135
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,    14,    17,    23,    14,    14,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     1,     1,     2,     1,     6,
       5,     1,     2,     1,    14,    17,     1,     4,     1,     1,
       3,     6,     1,    23,    23,    20,     1,     1,    20,     6,
       1,     2,    20,    23,    23,    20,    14,    14,    14,     6,
       1,     2,     1,     8,    11,    11,    11,    17,    14,    14,
       6,     1,     2,     1,    17,    17,    17,     6,     1,     2,
       1,    17,     1,    20,    17
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     0,     1,     2,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,     0,     0,     0,     0,    23,
       0,     0,     0,     0,    38,     0,     0,    36,     0,     0,
      34,    37,     0,     0,     0,     0,     0,     0,     7,     0,
       0,     0,     0,     0,    43,     0,    40,    41,     0,     0,
       0,    39,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,     0,     0,     0,     0,     0,     0,
       0,    11,     0,    10,    12,    14,    22,    13,    15,    56,
      57,    16,    17,    18,    19,    20,    21,    24,    30,    29,
      25,    26,    27,    28,    31,    32,    33,     0,     8,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    74,    75,    76,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    79,     0,     0,     0,    66,    67,     0,    68,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,    48,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    77,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    83,     0,    81,    85,     0,
      86,     0,    72,     0,    70,     0,    94,     0,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    80,    82,     0,     0,     0,    69,    71,     0,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    52,     0,     0,    55,     0,    65,
      60,     0,    58,    62,     0,     0,     0,     0,    90,     0,
      88,     0,    93,    51,     0,     0,    59,    61,     0,     0,
       0,     0,     0,    87,    89,     0,     0,     0,     0,     0,
       0,     0,     0,    53,    54,    63,    64,     0,     0,     0,
       0,     0,    73,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
      84,     0,     0,     0,    91
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    20,    37,    87,   110,   111,   112,
      55,    66,    75,    88,   113,   114,   401,   403,   485,   115,
     116,   117,   118,   119,   409,   491,   120,   121,   122,   123,
     124,   125,   126,   353,   443,   444,   127,   128,   129,   130,
     131,   132,   349,   436,   437,   133,   134,   416,   499,   500,
     549,   135,   136
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -418
static const yytype_int16 yypact[] =
{
      20,    21,    16,     1,  -418,    10,  -418,  -418,  -418,    46,
      34,    53,    63,    58,    69,    71,    57,    85,    78,    73,
      90,    91,  -418,    82,    89,    95,   101,    96,    97,   104,
      86,   102,   107,    98,   103,   108,   105,   106,   111,  -418,
     100,   109,   113,   119,   114,   117,   124,    94,   120,   127,
     115,   126,   134,    -3,  -418,   121,   136,   133,   137,  -418,
     118,   134,    15,   128,  -418,   130,    43,  -418,   138,   141,
    -418,  -418,   144,   131,   129,   145,   142,   148,  -418,   149,
     146,   155,    36,   150,  -418,   143,  -418,  -418,    45,   154,
     156,  -418,  -418,   160,   152,   147,   157,   158,   159,   168,
     169,   166,   164,  -418,   167,   173,   163,   170,   171,     6,
     172,  -418,   174,  -418,  -418,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,   175,  -418,  -418,
       3,   176,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   203,   204,   205,   206,   207,   209,   210,
     212,   213,   214,   216,   217,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   177,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   325,
     326,   327,   328,   324,   153,   229,   329,   301,   330,   331,
     332,   333,   334,   335,   341,   342,   343,   200,   201,   202,
     302,   303,   304,   336,   277,   344,   345,   347,   348,   349,
     351,   353,   354,   355,   357,   358,  -418,  -418,  -418,   359,
     360,   361,   364,   365,   366,   368,   369,   338,   376,   377,
     378,   374,   379,   380,   382,   383,   384,   385,   386,   374,
     374,   387,   387,   374,   388,   144,   362,   389,   230,   231,
       9,   350,   305,   367,   352,   346,   370,   371,   372,   392,
     375,   339,   381,   394,   398,   337,   400,   340,   402,  -418,
     403,   404,   405,   406,   407,   408,   409,   411,   412,   413,
     415,  -418,   416,   417,   418,  -418,  -418,   419,  -418,   421,
      32,   424,   429,    51,   374,   430,   431,   428,   433,   434,
     435,   278,   144,   432,   373,   374,   144,  -418,  -418,     0,
    -418,   436,   414,   437,   356,   401,   410,   420,   422,   393,
     399,   423,   425,   442,   443,   426,   445,   447,   438,   448,
     446,   449,  -418,   451,  -418,   453,   455,   456,   457,   458,
     459,   460,   461,   462,    11,  -418,    66,  -418,  -418,   463,
    -418,    12,  -418,    76,  -418,   464,  -418,   466,  -418,   444,
     374,   374,   468,   374,   211,   374,   374,   374,   374,   469,
     465,  -418,  -418,   390,   470,   467,  -418,  -418,   144,  -418,
      15,   440,   472,   450,   473,   374,   474,   475,   452,   454,
     427,   481,   439,   482,   485,   486,   484,  -418,   487,  -418,
    -418,    80,  -418,  -418,   488,   489,   483,    14,  -418,    83,
    -418,   441,  -418,  -418,   374,   374,  -418,  -418,   374,   374,
     490,   491,   492,  -418,  -418,   493,   495,   496,   497,   498,
     503,   471,   428,  -418,  -418,  -418,  -418,   499,   501,   500,
     505,   506,  -418,   512,   513,   476,   507,   510,   511,   374,
     517,   502,   477,   514,   515,   144,   374,   518,  -418,   508,
    -418,   516,   144,   519,  -418
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -418,  -418,  -418,   526,  -418,  -418,   478,  -319,   -52,  -418,
     479,  -137,  -328,  -418,   -61,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -188,  -418,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,   215,  -418,  -417,  -418,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -101,  -418,  -418,  -418,  -418,  -161,
    -418,  -418,  -418
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      54,    67,   341,    56,   420,    71,    56,   357,     1,    54,
     350,   351,    56,   141,   355,    56,     6,    56,    56,     9,
      56,    64,    65,    57,    76,   137,   467,     1,   362,     7,
     459,   464,   142,   511,   143,   473,   397,   398,   144,   399,
       5,   145,    84,    85,    86,   146,    11,   147,   148,   149,
      65,    70,    85,    91,   150,   151,   152,   153,   154,   155,
      10,   141,    12,   156,   414,   405,   157,    13,   419,    14,
     158,   159,    76,   460,   461,    16,   418,   160,    15,   161,
     162,    17,   421,   465,   466,    19,   144,   340,   506,   145,
     512,   513,    21,   146,    18,   147,   148,   149,    22,    24,
      23,    25,   150,   151,    26,    27,    29,    28,    30,    31,
      33,    32,    35,    34,    39,    36,    41,    48,   158,   159,
      40,    42,    43,    44,    38,    45,    46,   161,    47,    49,
      50,   471,   472,    51,   474,    52,   476,   477,   478,   479,
     483,    53,    60,    58,    59,    62,    61,    72,    68,    69,
      73,    74,    76,    78,    79,    77,   490,    80,    81,    83,
      82,    89,    90,    93,    95,    94,    96,    99,   100,    98,
      97,   101,   507,   102,   103,   104,   105,   106,   109,   108,
     138,   207,   139,   296,   140,   516,   517,   107,   163,   518,
     519,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   547,   190,   191,
     541,   192,   193,   194,   553,   195,   196,   548,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   309,
     475,   297,   310,   360,   311,   361,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   400,   291,
     292,   293,   294,   484,   529,   462,   413,   295,   514,   364,
     299,   336,   298,   300,   301,   302,   303,   304,   305,   306,
     307,   308,     0,   317,   318,   316,   319,   320,   321,   315,
     322,   435,   323,   324,   325,   442,   326,   327,   328,   329,
     330,   312,   313,   331,   332,   333,   314,   334,   335,   337,
     338,   340,   339,   342,   343,   344,   345,   358,   346,   347,
     363,   356,   425,   348,   352,   372,   367,   359,   370,   366,
     371,   365,   375,   373,   368,   369,   376,   374,   378,    67,
     377,   380,   381,   382,   383,   384,   385,   386,   387,   379,
     388,   389,   390,    71,   391,   392,   393,   394,   395,   498,
     396,   402,   404,   406,   407,   408,   410,   411,   412,   415,
     423,   430,   426,   417,   422,   424,   427,   431,   429,   434,
     447,   438,   439,   440,   441,   481,   446,   448,   445,   432,
     449,   433,   450,   428,   451,   452,   453,   454,   455,   456,
     457,   458,   463,   468,   469,   465,   470,   486,   480,   482,
     487,   489,   492,   493,   459,   496,   464,   488,   497,   494,
     502,   495,    65,   504,   503,   510,   505,   508,   509,   520,
     521,     0,   522,   523,   524,   525,   526,   527,   532,   501,
     530,   511,   515,   531,   533,   534,   535,   536,   538,   539,
     540,   542,   543,   545,   546,   552,   550,   554,   551,     8,
       0,     0,     0,   537,     0,     0,   528,     0,     0,     0,
      63,     0,     0,   544,     0,     0,     0,   354,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    92
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-418)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      52,    62,   321,     6,     4,    66,     6,   335,     7,    61,
     329,   330,     6,    10,   333,     6,     0,     6,     6,     9,
       6,     6,     7,    26,    21,    19,   443,     7,    19,    28,
      19,    19,    29,    19,    31,   452,     4,     5,    35,     7,
      19,    38,     6,     7,     8,    42,    12,    44,    45,    46,
       7,     8,     7,     8,    51,    52,    53,    54,    55,    56,
      14,    10,     9,    60,   392,   384,    63,     4,   396,    11,
      67,    68,    21,     7,     8,     4,   395,    74,     9,    76,
      77,    24,    82,     7,     8,     7,    35,     7,     8,    38,
       7,     8,    19,    42,     9,    44,    45,    46,     8,    17,
       9,    12,    51,    52,     9,     4,     9,    11,     4,    23,
       3,     9,     9,    15,     8,     7,    16,    23,    67,    68,
       9,    12,     9,     4,    19,    11,     9,    76,     4,     9,
       3,   450,   451,    18,   453,     9,   455,   456,   457,   458,
     468,     7,     9,    22,     8,    27,     9,     9,    20,    19,
       9,     7,    21,     8,    12,    26,   475,     9,     9,     4,
      14,    11,    19,     9,     4,     9,    14,     9,     9,    12,
      23,     3,   491,     4,     8,    11,     9,     4,     7,     9,
       8,     4,     8,    30,     9,   504,   505,    24,    12,   508,
     509,    12,    12,    12,    12,    12,    12,    12,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    12,    12,
      12,    12,     9,     9,     9,     9,     9,   545,     9,     9,
     539,     9,     9,     9,   552,     9,     9,   546,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    59,
      49,    32,    61,    33,    62,    34,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    11,    11,    11,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   380,     4,
       4,     4,     4,   470,   522,   436,    58,    13,   499,    34,
      39,     3,    13,    13,    13,    13,    13,    13,    13,     8,
       8,     8,    -1,     9,     9,    78,     9,     9,     9,    23,
       9,   413,     9,     9,     9,   417,     9,     9,     9,     9,
       9,    69,    69,     9,     9,     9,    72,     9,     9,     3,
       3,     7,     4,     4,     4,     3,     3,    25,     4,     4,
      40,     3,    36,     7,     7,    20,    50,     8,    26,    47,
       8,    34,     8,    64,    34,    34,     8,    26,     8,   470,
      73,     9,     9,     9,     9,     9,     9,     9,     9,    79,
       9,     9,     9,   484,     9,     9,     9,     9,     9,   481,
       9,     7,     3,     3,     3,     7,     3,     3,     3,     7,
      26,    48,    41,    70,     8,     8,    36,    48,    26,     7,
       4,     8,    26,     8,     7,    65,     8,     8,    20,    36,
       9,    36,     9,    43,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     8,     7,    32,    37,     9,     9,
       8,     8,     8,     8,    19,    58,    19,    37,     7,    37,
       8,    37,     7,     9,     8,    12,     9,     9,     9,     9,
       9,    -1,     9,     8,     8,     8,     8,     4,     8,    70,
      11,    19,    71,    12,     9,     9,     4,     4,    11,     9,
       9,     4,    20,     9,     9,     9,     8,     8,    20,     3,
      -1,    -1,    -1,    57,    -1,    -1,    65,    -1,    -1,    -1,
      61,    -1,    -1,    66,    -1,    -1,    -1,   332,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    84,    85,    86,    19,     0,    28,    86,     9,
      14,    12,     9,     4,    11,     9,     4,    24,     9,     7,
      87,    19,     8,     9,    17,    12,     9,     4,    11,     9,
       4,    23,     9,     3,    15,     9,     7,    88,    19,     8,
       9,    16,    12,     9,     4,    11,     9,     4,    23,     9,
       3,    18,     9,     7,    91,    93,     6,    26,    22,     8,
       9,     9,    27,    93,     6,     7,    94,    97,    20,    19,
       8,    97,     9,     9,     7,    95,    21,    26,     8,    12,
       9,     9,    14,     4,     6,     7,     8,    89,    96,    11,
      19,     8,    89,     9,     9,     4,    14,    23,    12,     9,
       9,     3,     4,     8,    11,     9,     4,    24,     9,     7,
      90,    91,    92,    97,    98,   102,   103,   104,   105,   106,
     109,   110,   111,   112,   113,   114,   115,   119,   120,   121,
     122,   123,   124,   128,   129,   134,   135,    19,     8,     8,
       9,    10,    29,    31,    35,    38,    42,    44,    45,    46,
      51,    52,    53,    54,    55,    56,    60,    63,    67,    68,
      74,    76,    77,    12,    12,    12,    12,    12,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    12,    12,
      12,    12,    12,    12,    12,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    11,
      11,    11,    11,    11,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    11,    11,    11,    11,    11,
      11,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,    13,    30,    32,    13,    39,
      13,    13,    13,    13,    13,    13,     8,     8,     8,    59,
      61,    62,    69,    69,    72,    23,    78,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     3,     3,     3,     4,
       7,    90,     4,     4,     3,     3,     4,     4,     7,   125,
      90,    90,     7,   116,   116,    90,     3,    95,    25,     8,
      33,    34,    19,    40,    34,    34,    47,    50,    34,    34,
      26,     8,    20,    64,    26,     8,     8,    73,     8,    79,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     4,     5,     7,
      91,    99,     7,   100,     3,    90,     3,     3,     7,   107,
       3,     3,     3,    58,    95,     7,   130,    70,    90,    95,
       4,    82,     8,    26,     8,    36,    41,    36,    43,    26,
      48,    48,    36,    36,     7,    91,   126,   127,     8,    26,
       8,     7,    91,   117,   118,    20,     8,     4,     8,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,    19,
       7,     8,   127,     9,    19,     7,     8,   118,     9,     8,
      32,    90,    90,   118,    90,    49,    90,    90,    90,    90,
       9,    65,     9,    95,    94,   101,    37,     8,    37,     8,
      90,   108,     8,     8,    37,    37,    58,     7,    91,   131,
     132,    70,     8,     8,     9,     9,     8,    90,     9,     9,
      12,    19,     7,     8,   132,    71,    90,    90,    90,    90,
       9,     9,     9,     8,     8,     8,     8,     4,    65,   107,
      11,    12,     8,     9,     9,     4,     4,    57,    11,     9,
       9,    90,     4,    20,    66,     9,     9,    95,    90,   133,
       8,    20,     9,    95,     8
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 158 "TmcLspParser.y"
    {
			(yyval.lsp_L_stmnt_gen_val)=(yyvsp[(1) - (2)].lsp_L_stmnt_gen_val);
			tmcpar_parsing_module = (yyval.lsp_L_stmnt_gen_val);
			YYACCEPT;
		}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 167 "TmcLspParser.y"
    {
            (yyval.lsp_L_stmnt_gen_val) = create_module((yyvsp[(1) - (1)].lsp_T_func_hdr_val));
        }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 171 "TmcLspParser.y"
    {
            (yyval.lsp_L_stmnt_gen_val) = append_to_module((yyvsp[(1) - (2)].lsp_L_stmnt_gen_val),(yyvsp[(2) - (2)].lsp_T_func_hdr_val));
        }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 188 "TmcLspParser.y"
    {
			(yyval.lsp_T_func_hdr_val)=(yyvsp[(13) - (14)].lsp_T_func_hdr_val);
		}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 194 "TmcLspParser.y"
    {
							(yyval.lsp_T_func_hdr_val) = create_func_def_statement((yyvsp[(16) - (17)].lsp_T_func_block_val),(int)(yyvsp[(7) - (17)].num),(int)(yyvsp[(10) - (17)].num));
					}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 200 "TmcLspParser.y"
    {
						(yyval.lsp_T_func_block_val) = create_func_body((yyvsp[(13) - (23)].ident),(yyvsp[(16) - (23)].lsp_L_vardecl_val),(yyvsp[(19) - (23)].lsp_L_vardecl_val),(yyvsp[(22) - (23)].lsp_L_stmnt_gen_val),(int)(yyvsp[(7) - (23)].num),(int)(yyvsp[(10) - (23)].num));
					}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 206 "TmcLspParser.y"
    {
                    (yyval.lsp_statement_val) = create_expression((yyvsp[(13) - (14)].lsp_expression_val),(int)(yyvsp[(7) - (14)].num),(int)(yyvsp[(10) - (14)].num));
                   }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 210 "TmcLspParser.y"
    {
                    (yyval.lsp_statement_val) = create_command((yyvsp[(13) - (14)].lsp_command_val),(int)(yyvsp[(7) - (14)].num),(int)(yyvsp[(10) - (14)].num));
                   }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 216 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_ident_val);
					}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 220 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)0;
					}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 224 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_constant_val);
					}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 228 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_colon_expression_val);
				}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 232 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_simple_assignment_val);
				}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 236 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_index_expression_val);
					}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 240 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_binary_expression_val);
					}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 244 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_boolean_expression_val);
					}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 248 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_unary_expression_val);
					}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 252 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_cell_val);
					}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 256 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_list_of_argument_list_val);
					}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 260 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_fcn_handle_val);
					}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 264 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_multi_assignment_val);
					}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 273 "TmcLspParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_return_command_val);
					}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 277 "TmcLspParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_cmd_decl_gen_val);
					}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 281 "TmcLspParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_cmd_ctrl_label_val);
					}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 285 "TmcLspParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_if_val);
					}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 289 "TmcLspParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_while_val);
					}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 293 "TmcLspParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_continue_val);
					}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 297 "TmcLspParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_break_val);
					}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 301 "TmcLspParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_switch_val);
					}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 305 "TmcLspParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_for_val);
					}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 313 "TmcLspParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_tree_try_command_val);
					}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 335 "TmcLspParser.y"
    {
					(yyval.lsp_L_vardecl_val)=(yyvsp[(5) - (6)].lsp_L_vardecl_val);
					}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 339 "TmcLspParser.y"
    {
					(yyval.lsp_L_vardecl_val)=0;
					}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 345 "TmcLspParser.y"
    {
					(yyval.lsp_L_vardecl_val) = create_list_ident((yyvsp[(1) - (1)].lsp_ident_val));
					}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 349 "TmcLspParser.y"
    {
                   	(yyval.lsp_L_vardecl_val) = append_to_list_ident((yyvsp[(1) - (2)].lsp_L_vardecl_val),(yyvsp[(2) - (2)].lsp_ident_val));
					}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 353 "TmcLspParser.y"
    {
                   	(yyval.lsp_L_vardecl_val) = create_list_ident_empty();
					}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 358 "TmcLspParser.y"
    {
					 (yyval.lsp_L_stmnt_gen_val) = (yyvsp[(5) - (6)].lsp_L_stmnt_gen_val);
					 }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 362 "TmcLspParser.y"
    {
					(yyval.lsp_L_stmnt_gen_val) = create_statement_list_empty();
					}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 367 "TmcLspParser.y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = create_statement_list((yyvsp[(1) - (1)].lsp_statement_val));
                   }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 371 "TmcLspParser.y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = append_to_statement_list((yyvsp[(1) - (2)].lsp_L_stmnt_gen_val),(yyvsp[(2) - (2)].lsp_statement_val));
                   }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 375 "TmcLspParser.y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = create_statement_list_empty();
                   }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 380 "TmcLspParser.y"
    {
					 (yyval.lsp_ident_val) = create_identifier((yyvsp[(13) - (14)].ident),(int)(yyvsp[(7) - (14)].num),(int)(yyvsp[(10) - (14)].num));
					 }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 385 "TmcLspParser.y"
    {
					 (yyval.lsp_constant_val) = create_constant((enum CONST_VAL_TYPES)0,(yyvsp[(16) - (17)].lsp_const_val),(int)(yyvsp[(7) - (17)].num),(int)(yyvsp[(10) - (17)].num));
					}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 391 "TmcLspParser.y"
    {
					 (yyval.lsp_const_val) = make_number((yyvsp[(1) - (1)].num),0,const_val_real);
					}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 395 "TmcLspParser.y"
    {
                     (yyval.lsp_const_val) = make_number((yyvsp[(2) - (4)].num),(yyvsp[(3) - (4)].num),const_val_complex);
                   }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 399 "TmcLspParser.y"
    {
					 (yyval.lsp_const_val) = make_string((yyvsp[(1) - (1)].str));
                   }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 403 "TmcLspParser.y"
    {
                     (yyval.lsp_const_val) =  make_empty_matrix();
                   }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 408 "TmcLspParser.y"
    {
                     (yyval.lsp_const_val) =  make_magic_col();
                   }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 413 "TmcLspParser.y"
    {
				(yyval.lsp_L_vardecl_val) = (yyvsp[(5) - (6)].lsp_L_vardecl_val);
		}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 419 "TmcLspParser.y"
    {
			(yyval.lsp_L_vardecl_val)=(yyvsp[(1) - (1)].lsp_L_vardecl_val);
		}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 425 "TmcLspParser.y"
    {
	 (yyval.lsp_simple_assignment_val) = create_s_assignment_expression((int)(yyvsp[(13) - (23)].num),(yyvsp[(16) - (23)].ident),(yyvsp[(19) - (23)].lsp_expression_val),(yyvsp[(22) - (23)].lsp_expression_val),(int)(yyvsp[(7) - (23)].num),(int)(yyvsp[(10) - (23)].num));
	}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 430 "TmcLspParser.y"
    {
	 (yyval.lsp_multi_assignment_val) = create_m_assignment_expression((int)(yyvsp[(13) - (23)].num),(yyvsp[(16) - (23)].ident),(yyvsp[(19) - (23)].lsp_argument_list_val),(yyvsp[(22) - (23)].lsp_expression_val),(int)(yyvsp[(7) - (23)].num),(int)(yyvsp[(10) - (23)].num));
	}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 435 "TmcLspParser.y"
    {
	 (yyval.lsp_colon_expression_val) = create_colon_expression((yyvsp[(13) - (20)].lsp_expression_val),(yyvsp[(16) - (20)].lsp_expression_val),(yyvsp[(19) - (20)].lsp_expression_val),(int)(yyvsp[(7) - (20)].num),(int)(yyvsp[(10) - (20)].num));
	}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 441 "TmcLspParser.y"
    {
	  (yyval.lsp_index_expression_val) =(yyvsp[(1) - (1)].lsp_index_expression_val);
	 }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 445 "TmcLspParser.y"
    {
	  (yyval.lsp_index_expression_val) = (yyvsp[(1) - (1)].lsp_index_expression_val);
	 }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 450 "TmcLspParser.y"
    {
			(yyval.lsp_index_expression_val) = create_ref_index((yyvsp[(13) - (20)].ident),(yyvsp[(16) - (20)].lsp_argument_list_val),(yyvsp[(19) - (20)].lsp_expression_val),(int)(yyvsp[(7) - (20)].num),(int)(yyvsp[(10) - (20)].num));
		}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 455 "TmcLspParser.y"
    {
				(yyval.lsp_argument_list_val) = (yyvsp[(5) - (6)].lsp_argument_list_val);
			}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 460 "TmcLspParser.y"
    {
				(yyval.lsp_argument_list_val)=create_argument_list((yyvsp[(1) - (1)].lsp_expression_val));
			}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 464 "TmcLspParser.y"
    {
				(yyval.lsp_argument_list_val)=append_to_argument_list((yyvsp[(1) - (2)].lsp_argument_list_val),(yyvsp[(2) - (2)].lsp_expression_val));
			}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 469 "TmcLspParser.y"
    {
			(yyval.lsp_index_expression_val) = create_ref_field((yyvsp[(13) - (20)].ident),(yyvsp[(16) - (20)].ident),(yyvsp[(19) - (20)].lsp_expression_val),(int)(yyvsp[(7) - (20)].num),(int)(yyvsp[(10) - (20)].num));
		}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 475 "TmcLspParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression((yyvsp[(16) - (23)].ident),(yyvsp[(19) - (23)].lsp_expression_val),(yyvsp[(22) - (23)].lsp_expression_val),(int)(yyvsp[(7) - (23)].num),(int)(yyvsp[(10) - (23)].num));
		}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 481 "TmcLspParser.y"
    {
			(yyval.lsp_boolean_expression_val) = create_boolean_expression((yyvsp[(16) - (23)].ident),(yyvsp[(19) - (23)].lsp_expression_val),(yyvsp[(22) - (23)].lsp_expression_val),(int)(yyvsp[(7) - (23)].num),(int)(yyvsp[(10) - (23)].num));
		}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 487 "TmcLspParser.y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression((yyvsp[(16) - (20)].ident),(yyvsp[(19) - (20)].lsp_expression_val),(int)(yyvsp[(7) - (20)].num),(int)(yyvsp[(10) - (20)].num));
		}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 492 "TmcLspParser.y"
    {
			(yyval.lsp_cell_val) = create_cell_array((yyvsp[(13) - (14)].lsp_list_of_argument_list_val)); // convert matrix to cell array
		}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 497 "TmcLspParser.y"
    {
			(yyval.lsp_list_of_argument_list_val) = (yyvsp[(13) - (14)].lsp_list_of_argument_list_val);
		}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 503 "TmcLspParser.y"
    {
						(yyval.lsp_fcn_handle_val) = create_fcn_handle((yyvsp[(13) - (14)].ident),(int)(yyvsp[(7) - (14)].num),(int)(yyvsp[(10) - (14)].num));
					}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 508 "TmcLspParser.y"
    {
			(yyval.lsp_list_of_argument_list_val) = (yyvsp[(5) - (6)].lsp_list_of_argument_list_val);
		}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 513 "TmcLspParser.y"
    {
						(yyval.lsp_list_of_argument_list_val) = create_matrix((yyvsp[(1) - (1)].lsp_argument_list_val));
					}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 517 "TmcLspParser.y"
    {
						(yyval.lsp_list_of_argument_list_val) = add_row_to_matrix((yyvsp[(1) - (2)].lsp_list_of_argument_list_val),(yyvsp[(2) - (2)].lsp_argument_list_val));
					}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 521 "TmcLspParser.y"
    {
						(yyval.lsp_list_of_argument_list_val) = create_empty_matrix();
					}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 526 "TmcLspParser.y"
    {
		(yyval.lsp_argument_list_val) = (yyvsp[(7) - (8)].lsp_argument_list_val);
	}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 532 "TmcLspParser.y"
    {
		(yyval.lsp_return_command_val)=create_return((int)(yyvsp[(7) - (11)].num),(int)(yyvsp[(10) - (11)].num));
	}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 537 "TmcLspParser.y"
    {
		(yyval.lsp_T_ctrl_cmd_break_val)=create_break((int)(yyvsp[(7) - (11)].num),(int)(yyvsp[(10) - (11)].num));
	}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 542 "TmcLspParser.y"
    {
		(yyval.lsp_T_ctrl_cmd_continue_val)=create_continue((int)(yyvsp[(7) - (11)].num),(int)(yyvsp[(10) - (11)].num));
	}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 547 "TmcLspParser.y"
    {
		(yyval.lsp_T_cmd_decl_gen_val)=create_declaration((yyvsp[(13) - (17)].ident),(yyvsp[(16) - (17)].lsp_L_vardecl_val),(int)(yyvsp[(7) - (17)].num),(int)(yyvsp[(10) - (17)].num));
	}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 552 "TmcLspParser.y"
    {
		(yyval.lsp_T_cmd_ctrl_label_val)=create_cmd_ctrl_label((yyvsp[(13) - (14)].ident),(int)(yyvsp[(7) - (14)].num),(int)(yyvsp[(10) - (14)].num));
	}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 557 "TmcLspParser.y"
    {
		(yyval.lsp_T_ctrl_cmd_if_val) = create_if_statement((yyvsp[(13) - (14)].lsp_LT_if_blocks_val),(int)(yyvsp[(7) - (14)].num),(int)(yyvsp[(10) - (14)].num));
	}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 562 "TmcLspParser.y"
    {
		(yyval.lsp_LT_if_blocks_val)=(yyvsp[(5) - (6)].lsp_LT_if_blocks_val);
	}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 568 "TmcLspParser.y"
    {
					(yyval.lsp_LT_if_blocks_val) = create_if_clause_list((yyvsp[(1) - (1)].lsp_T_if_block_val));
					}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 572 "TmcLspParser.y"
    {
					(yyval.lsp_LT_if_blocks_val) = append_to_if_clause_list((yyvsp[(1) - (2)].lsp_LT_if_blocks_val),(yyvsp[(2) - (2)].lsp_T_if_block_val));
					}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 576 "TmcLspParser.y"
    {
					(yyval.lsp_LT_if_blocks_val) = create_if_clause_list_empty();
				}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 582 "TmcLspParser.y"
    {
				(yyval.lsp_T_if_block_val)=create_if_clause((yyvsp[(13) - (17)].lsp_expression_val),(yyvsp[(16) - (17)].lsp_L_stmnt_gen_val),(int)(yyvsp[(7) - (17)].num),(int)(yyvsp[(10) - (17)].num));
				}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 588 "TmcLspParser.y"
    {
				(yyval.lsp_T_ctrl_cmd_while_val)=create_while_command((yyvsp[(13) - (17)].lsp_expression_val),(yyvsp[(16) - (17)].lsp_L_stmnt_gen_val),(int)(yyvsp[(7) - (17)].num),(int)(yyvsp[(10) - (17)].num));
				}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 596 "TmcLspParser.y"
    {
				(yyval.lsp_T_ctrl_cmd_switch_val)=create_switch_command((yyvsp[(13) - (17)].lsp_expression_val),(yyvsp[(16) - (17)].lsp_LT_sw_cases_val),(int)(yyvsp[(7) - (17)].num),(int)(yyvsp[(10) - (17)].num));
				}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 602 "TmcLspParser.y"
    {
				(yyval.lsp_LT_sw_cases_val) = (yyvsp[(5) - (6)].lsp_LT_sw_cases_val);
				}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 608 "TmcLspParser.y"
    {
						(yyval.lsp_LT_sw_cases_val)  = create_switch_cases_list((yyvsp[(1) - (1)].lsp_T_sw_case_val));
					}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 612 "TmcLspParser.y"
    {
						(yyval.lsp_LT_sw_cases_val)  = append_to_switch_cases_list((yyvsp[(1) - (2)].lsp_LT_sw_cases_val),(yyvsp[(2) - (2)].lsp_T_sw_case_val));
					}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 616 "TmcLspParser.y"
    {
						(yyval.lsp_LT_sw_cases_val)  = create_switch_cases_list_empty();
					}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 621 "TmcLspParser.y"
    {
				(yyval.lsp_T_sw_case_val) = create_switch_case((yyvsp[(13) - (17)].lsp_expression_val),(yyvsp[(16) - (17)].lsp_L_stmnt_gen_val),(int)(yyvsp[(7) - (17)].num),(int)(yyvsp[(10) - (17)].num));
				}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 626 "TmcLspParser.y"
    {
					(yyval.lsp_expression_val)=(yyvsp[(1) - (1)].lsp_expression_val);
				}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 631 "TmcLspParser.y"
    {
				(yyval.lsp_T_ctrl_cmd_for_val)=create_for_statement((yyvsp[(13) - (20)].lsp_expression_val),(yyvsp[(16) - (20)].lsp_expression_val),(yyvsp[(19) - (20)].lsp_L_stmnt_gen_val),(int)(yyvsp[(7) - (20)].num),(int)(yyvsp[(10) - (20)].num));
				}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 641 "TmcLspParser.y"
    {
				(yyval.lsp_tree_try_command_val)=create_try_catch_statement((yyvsp[(13) - (17)].lsp_L_stmnt_gen_val),(yyvsp[(16) - (17)].lsp_L_stmnt_gen_val),(int)(yyvsp[(7) - (17)].num),(int)(yyvsp[(10) - (17)].num));
				}
    break;


/* Line 1792 of yacc.c  */
#line 2653 "TmcLspParser.tab.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 646 "TmcLspParser.y"


