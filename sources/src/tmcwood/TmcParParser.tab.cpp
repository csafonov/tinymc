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
#define yyparse         tmcpar_parse
#define yylex           tmcpar_lex
#define yyerror         tmcpar_error
#define yylval          tmcpar_lval
#define yychar          tmcpar_char
#define yydebug         tmcpar_debug
#define yynerrs         tmcpar_nerrs

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "TmcParParser.Y"

//! Gramma for m-file parser

/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "tmcpar_tree.h"
#include "tmcpar_utils.h"



/* Line 371 of yacc.c  */
#line 94 "TmcParParser.tab.cpp"

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
   by #include "TmcParParser.tab.hpp".  */
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
/* Line 387 of yacc.c  */
#line 24 "TmcParParser.Y"

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
	


/* Line 387 of yacc.c  */
#line 258 "TmcParParser.tab.cpp"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 286 "TmcParParser.tab.cpp"

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   678

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNRULES -- Number of states.  */
#define YYNSTATES  276

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

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
      65,    66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     9,    12,    14,    15,    17,    19,
      21,    28,    33,    36,    38,    40,    42,    45,    48,    50,
      52,    54,    56,    58,    60,    62,    64,    66,    68,    70,
      72,    74,    75,    81,    82,    84,    86,    88,    90,    92,
      94,    96,    98,   100,   103,   105,   108,   112,   114,   118,
     119,   121,   125,   127,   130,   132,   134,   136,   138,   140,
     142,   144,   147,   151,   155,   157,   159,   163,   167,   168,
     169,   177,   178,   179,   187,   188,   189,   197,   198,   199,
     207,   211,   215,   219,   223,   227,   231,   235,   239,   243,
     247,   251,   255,   259,   263,   267,   271,   275,   279,   283,
     287,   291,   295,   298,   301,   304,   307,   310,   311,   317,
     318,   319,   325,   326,   327,   329,   332,   336,   339,   343,
     345,   347,   350,   353,   357,   360,   362,   364,   366,   369,
     371,   373,   378,   383,   388,   393,   399,   403,   408,   412,
     419,   425,   431,   436,   441,   446,   451,   457,   464,   472,
     476,   480,   485,   492,   498,   502,   503,   505,   507,   509,
     512,   514,   517,   519,   521,   524,   527,   529
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      68,     0,    -1,    71,    69,    48,    -1,    70,    -1,    69,
      70,    -1,    72,    -1,    -1,   138,    -1,   136,    -1,    73,
      -1,    65,    83,    30,     3,    84,    74,    -1,    65,     3,
      84,    74,    -1,   135,    86,    -1,   134,    -1,    74,    -1,
      86,    -1,    78,   135,    -1,    81,   135,    -1,    78,    -1,
      87,    -1,    89,    -1,    88,    -1,   106,    -1,    93,    -1,
      92,    -1,    95,    -1,   104,    -1,   105,    -1,   107,    -1,
     110,    -1,   116,    -1,    -1,    31,    80,    78,    79,    32,
      -1,    -1,   117,    -1,   120,    -1,   121,    -1,   128,    -1,
     119,    -1,   118,    -1,   129,    -1,   132,    -1,   133,    -1,
       3,    82,    -1,     3,    -1,    82,     3,    -1,    35,    85,
      36,    -1,    87,    -1,    31,    85,    32,    -1,    -1,    87,
      -1,    85,    38,    87,    -1,    76,    -1,    86,    76,    -1,
       3,    -1,    43,    -1,    90,    -1,     4,    -1,     5,    -1,
       6,    -1,    87,    -1,    91,    87,    -1,    78,    30,    78,
      -1,    78,    41,    78,    -1,    41,    -1,    78,    -1,    41,
      38,    94,    -1,    78,    38,    94,    -1,    -1,    -1,     3,
      31,    96,    80,    94,    97,    32,    -1,    -1,    -1,    95,
      31,    98,    80,    94,    99,    32,    -1,    -1,    -1,     3,
      33,   100,    80,    94,   101,    34,    -1,    -1,    -1,    95,
      33,   102,    80,    94,   103,    34,    -1,     3,    42,     3,
      -1,    95,    42,     3,    -1,    78,     7,    78,    -1,    78,
       8,    78,    -1,    78,     9,    78,    -1,    78,    10,    78,
      -1,    78,    11,    78,    -1,    78,    12,    78,    -1,    78,
      13,    78,    -1,    78,    14,    78,    -1,    78,    15,    78,
      -1,    78,    16,    78,    -1,    78,    17,    78,    -1,    78,
      18,    78,    -1,    78,    19,    78,    -1,    78,    20,    78,
      -1,    78,    21,    78,    -1,    78,    22,    78,    -1,    78,
      23,    78,    -1,    78,    24,    78,    -1,    78,    25,    78,
      -1,    78,    26,    78,    -1,     7,    78,    -1,     8,    78,
      -1,    29,    78,    -1,    78,    27,    -1,    78,    28,    -1,
      -1,    33,   109,   113,   108,    34,    -1,    -1,    -1,    35,
     112,   113,   111,    36,    -1,    -1,    -1,   114,    -1,   113,
      37,    -1,   113,    37,   114,    -1,   113,    39,    -1,   113,
      39,   114,    -1,    78,    -1,   115,    -1,   115,    78,    -1,
      78,    38,    -1,   115,    78,    38,    -1,    40,     3,    -1,
      50,    -1,    51,    -1,    52,    -1,    66,    91,    -1,   122,
      -1,   123,    -1,    53,    77,    74,    56,    -1,    53,    77,
      74,   124,    -1,    53,    77,    74,   126,    -1,    54,    77,
      74,    56,    -1,    54,    77,    74,    54,   125,    -1,    77,
      74,    56,    -1,    77,    74,    54,   125,    -1,    55,    75,
      56,    -1,    54,    77,    74,    55,    75,    56,    -1,    54,
      77,    74,    54,   127,    -1,    77,    74,    55,    75,    56,
      -1,    77,    74,    54,   127,    -1,    57,    77,    74,    56,
      -1,    58,    77,   135,   130,    -1,    59,    77,    74,    56,
      -1,    59,   131,    77,    74,    56,    -1,    59,    77,    74,
      60,    74,    56,    -1,    59,   131,    77,    74,    60,    74,
      56,    -1,    60,    74,    56,    -1,    77,    74,    59,    -1,
     131,    77,    74,    59,    -1,    61,    87,    30,    77,    74,
      56,    -1,    63,    74,    64,    74,    56,    -1,    63,    74,
      56,    -1,    -1,   135,    -1,   136,    -1,   138,    -1,   136,
     138,    -1,   137,    -1,   136,   137,    -1,    38,    -1,    37,
      -1,   138,    38,    -1,   138,    37,    -1,    39,    -1,   138,
      39,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   219,   219,   228,   232,   251,   257,   259,   260,   264,
     273,   277,   283,   287,   293,   297,   305,   309,   316,   324,
     328,   332,   336,   341,   346,   351,   356,   360,   364,   369,
     375,   381,   380,   391,   400,   404,   408,   412,   417,   421,
     426,   431,   437,   443,   449,   453,   459,   463,   469,   474,
     480,   484,   490,   494,   500,   506,   511,   516,   520,   525,
     533,   537,   543,   552,   563,   567,   571,   575,   582,   583,
     582,   590,   591,   590,   601,   602,   601,   609,   610,   609,
     619,   624,   635,   639,   643,   647,   652,   656,   662,   666,
     671,   675,   680,   684,   689,   693,   698,   702,   707,   711,
     717,   721,   728,   732,   736,   741,   746,   755,   754,   765,
     774,   773,   784,   792,   795,   799,   803,   807,   811,   818,
     822,   826,   833,   837,   845,   854,   859,   864,   870,   879,
     885,   894,   898,   902,   909,   913,   920,   924,   931,   935,
     942,   948,   955,   961,   970,   977,   981,   985,   990,   997,
    1004,  1008,  1016,  1027,  1031,  1038,  1040,  1043,  1044,  1045,
    1048,  1049,  1052,  1053,  1054,  1055,  1058,  1059
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "NUMBER", "NUMBER_IM", "STRING",
  "PLUS", "MINUS", "MUL", "EMUL", "AND", "OR", "DIV", "EDIV", "POW",
  "EPOW", "LDIV", "ELDIV", "LE", "LT", "GE", "GT", "NE", "EQL", "BOOL_AND",
  "BOOL_OR", "TRANSPOSE", "CTRANSPOSE", "NOT", "ASG", "LPAREN", "RPAREN",
  "LC", "RC", "LBRA", "RBRA", "SM", "CM", "LINE", "COMAT", "COLON",
  "ELLIP", "MAGIC_END", "LEXERROR", "UNARYMINUS", "UNARYPLUS", "UNARYNOT",
  "END_OF_INPUT", "NO_OP_CMD", "RETURN", "BREAK", "CONTINUE", "IF",
  "ELSEIF", "ELSE", "END", "WHILE", "SWITCH", "CASE", "OTHERWISE", "FOR",
  "FUNC_HANDLE", "TRY", "CATCH", "FUNCTION", "GLOBAL", "$accept", "module",
  "list_function", "func_def_statement", "file_hdr", "fnc_def",
  "T_func_block", "f_list_statement", "e_list_statement", "statement",
  "eval_expression", "expression", "$@1", "parenthesis1", "command",
  "cmd_pars", "out_list_par", "in_list_par", "list_par", "list_statement",
  "ident", "magic_end", "const", "variant_val", "t_list_decl", "s_assign",
  "colon_expr", "argument_list", "indx_expr", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "bin_expr", "bool_expr", "un_expr", "cell",
  "$@10", "boxes1c", "matrix", "$@11", "boxes1", "rows", "row",
  "row_with_commas", "fcn_handle", "return", "break", "continue",
  "decl_cmd", "if", "t_if_clause", "list_if_clause", "elseif_list",
  "elseif_list1", "elseifelse_list", "elseifelse_list1", "while", "switch",
  "case_list", "case_list1", "for", "try", "opt_delimiter", "delimiter",
  "null_lines", "null_line", "empty_lines", YY_NULL
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
     315,   316,   317,   318,   319,   320,   321
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    69,    69,    70,    71,    71,    71,    72,
      73,    73,    74,    74,    75,    75,    76,    76,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    79,    78,    80,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    82,    82,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    88,    89,    90,    90,    90,
      91,    91,    92,    93,    94,    94,    94,    94,    96,    97,
      95,    98,    99,    95,   100,   101,    95,   102,   103,    95,
      95,    95,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     105,   105,   106,   106,   106,   106,   106,   108,   107,   109,
     111,   110,   112,   113,   113,   113,   113,   113,   113,   114,
     114,   114,   115,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   123,   123,   124,   124,   125,   125,   126,   126,
     126,   127,   127,   128,   129,   130,   130,   130,   130,   130,
     131,   131,   132,   133,   133,   134,   134,   135,   135,   135,
     136,   136,   137,   137,   137,   137,   138,   138
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     1,     2,     1,     0,     1,     1,     1,
       6,     4,     2,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     5,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     3,     1,     3,     0,
       1,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     3,     1,     1,     3,     3,     0,     0,
       7,     0,     0,     7,     0,     0,     7,     0,     0,     7,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     0,     5,     0,
       0,     5,     0,     0,     1,     2,     3,     2,     3,     1,
       1,     2,     2,     3,     2,     1,     1,     1,     2,     1,
       1,     4,     4,     4,     4,     5,     3,     4,     3,     6,
       5,     5,     4,     4,     4,     4,     5,     6,     7,     3,
       3,     4,     6,     5,     3,     0,     1,     1,     1,     2,
       1,     2,     1,     1,     2,     2,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,   163,   162,   166,     0,     0,     8,   160,     7,     1,
       0,     0,     3,     5,     9,   161,     0,   165,   164,   167,
      49,     0,     0,    47,     2,     4,     0,   155,    54,     0,
      50,     0,     0,    11,    13,   156,   157,   158,    46,     0,
      49,    48,    54,    57,    58,    59,     0,     0,     0,    33,
     109,   112,     0,    55,   125,   126,   127,     0,     0,     0,
       0,   155,     0,    52,     0,     0,    12,    19,    21,    20,
      56,    24,    23,    25,    26,    27,    22,    28,    29,    30,
      34,    39,    38,    35,    36,   129,   130,    37,    40,    41,
      42,   159,    51,   155,    44,    68,    74,     0,    43,    54,
     102,   103,   104,     0,   113,   113,   124,   155,    18,   155,
       0,     0,     0,    60,   128,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,     0,     0,    16,
      17,    53,    71,    77,     0,    10,    33,    33,    80,    45,
      31,   119,   107,   114,   120,   110,     0,     0,     0,     0,
     154,   155,    61,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,    62,    63,    33,    33,    81,     0,     0,
       0,   122,   115,   117,     0,   121,     0,     0,   155,   131,
     132,   133,   143,     0,   155,   144,   155,     0,     0,     0,
      64,    65,    69,    75,    32,   116,   118,   108,   123,   111,
     155,    14,     0,    15,   155,     0,     0,     0,   153,    72,
      78,     0,     0,     0,     0,     0,   138,     0,   155,   149,
     152,     0,     0,    66,    67,    70,    76,     0,   155,   134,
     145,   150,   155,     0,    73,    79,   155,   135,   140,     0,
       0,   146,   151,   155,     0,   139,   147,     0,     0,   155,
     136,   148,   137,   142,     0,   141
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    11,    12,     5,    13,    14,   221,   222,    63,
     256,   108,   190,   103,    65,    98,    22,    27,    29,   223,
      67,    68,    69,    70,   114,    71,    72,   212,    73,   146,
     233,   185,   241,   147,   234,   186,   242,    74,    75,    76,
      77,   194,   104,    78,   196,   105,   152,   153,   154,    79,
      80,    81,    82,    83,    84,    85,    86,   200,   257,   201,
     258,    87,    88,   205,   225,    89,    90,    34,    35,    36,
       7,    37
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -235
static const yytype_int16 yypact[] =
{
      98,  -235,  -235,  -235,    26,   -35,    98,  -235,   101,  -235,
       6,   -33,  -235,  -235,  -235,  -235,   101,  -235,  -235,  -235,
       9,    43,    19,  -235,  -235,  -235,    43,    98,  -235,   -15,
    -235,    52,    -1,  -235,  -235,   250,    98,   101,  -235,    43,
      33,  -235,    14,  -235,  -235,  -235,   332,   332,   332,  -235,
    -235,  -235,    78,  -235,  -235,  -235,  -235,   332,   332,   332,
      43,    98,    43,  -235,   369,    98,   250,  -235,  -235,  -235,
    -235,  -235,  -235,    36,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,   101,  -235,    98,  -235,  -235,  -235,   110,   115,    37,
      58,    58,    58,   332,   332,   332,  -235,    98,   509,    98,
      98,    95,   -31,  -235,    43,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,  -235,  -235,   332,   332,  -235,
    -235,  -235,  -235,  -235,   130,  -235,  -235,  -235,  -235,  -235,
     509,   404,   120,  -235,   332,   120,    89,    93,    24,   332,
    -235,    98,  -235,    44,    44,    58,    58,   637,   608,    58,
      58,  -235,  -235,    58,    58,   114,   114,   114,   114,   114,
     114,   579,   544,   509,   341,  -235,  -235,  -235,   291,   291,
     122,  -235,   332,   332,   128,   439,   127,   332,   209,  -235,
    -235,  -235,  -235,   332,    98,  -235,    98,   111,   291,   291,
     131,   474,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
      98,  -235,   112,   250,    98,   332,   116,   117,  -235,  -235,
    -235,   291,   291,   134,   137,    92,  -235,    55,    98,  -235,
    -235,   142,   141,  -235,  -235,  -235,  -235,   332,   209,  -235,
    -235,  -235,    98,    60,  -235,  -235,    98,  -235,  -235,   126,
     129,  -235,  -235,    98,    97,  -235,  -235,   132,   332,   209,
    -235,  -235,  -235,  -235,   133,  -235
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -235,  -235,  -235,   165,  -235,  -235,  -235,   -27,  -234,   -65,
     -47,   -28,  -235,  -142,  -235,  -235,  -235,   143,   158,   151,
       3,  -235,  -235,  -235,  -235,  -235,  -235,  -181,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,    82,   -85,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,   -78,  -235,
     -77,  -235,  -235,  -235,  -235,  -235,  -235,  -235,   -62,   192,
       0,    16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -55
static const yytype_int16 yytable[] =
{
      33,   141,   139,   140,   188,   189,    15,    64,   213,    20,
     107,   109,   110,    23,   259,    24,     8,    94,   100,   101,
     102,    38,    16,    39,    30,   160,     9,   229,   230,    30,
      10,    41,    10,   161,   112,   274,    15,    39,    64,   -54,
      26,    21,    92,   208,   209,    95,    28,    96,   158,    31,
     243,   244,    91,   117,   118,    40,    97,   121,   122,   123,
     124,   125,   126,   111,    26,   113,   145,   142,    95,   143,
      96,   135,   136,   123,   124,   150,   151,   151,   144,    97,
     156,   106,   157,   203,   204,   135,   136,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   215,   216,   183,
     184,   250,   206,   148,   251,   252,   261,   162,   149,   262,
     263,   115,   116,   117,   118,   159,   195,   121,   122,   123,
     124,   125,   126,   187,   207,     1,     2,     3,    17,    18,
      19,   135,   136,   197,   198,   199,   247,   248,   249,   202,
     220,   268,   269,   270,   214,   138,   224,   192,   141,   193,
     211,   211,   217,   219,   151,   151,   245,   228,   236,   231,
      64,   246,   239,   240,   254,   255,    25,   226,   238,   227,
     211,   211,   265,    93,    32,   266,    66,   155,   271,   275,
     272,   273,     6,   235,     0,    64,     0,   237,     0,     0,
       0,     0,     0,   211,   211,     0,     0,     0,     0,     0,
       0,   253,    42,    43,    44,    45,    46,    47,     0,     0,
      64,     0,     0,     0,     0,   260,     0,     0,     0,   264,
       0,     0,     0,     0,     0,     0,   267,     0,    48,     0,
      49,    64,    50,     0,    51,     0,     1,     2,     3,    52,
       0,     0,    53,    42,    43,    44,    45,    46,    47,    54,
      55,    56,    57,     0,     0,     0,    58,    59,     0,     0,
      60,     0,    61,     0,     0,    62,     0,     0,     0,    48,
       0,    49,     0,    50,     0,    51,     0,     0,     0,     0,
      52,     0,     0,    53,    99,    43,    44,    45,    46,    47,
      54,    55,    56,    57,     0,     0,     0,    58,    59,     0,
       0,    60,     0,    61,     0,     0,    62,     0,     0,     0,
      48,     0,    49,     0,    50,     0,    51,     0,     0,     0,
       0,    52,   210,     0,    53,    99,    43,    44,    45,    46,
      47,     0,     0,     0,     0,     0,     0,     0,   115,   116,
     117,   118,     0,     0,   121,   122,   123,   124,   125,   126,
       0,    48,     0,    49,     0,    50,     0,    51,   135,   136,
       0,     0,    52,     0,     0,    53,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,     0,   137,
       0,     0,     0,     0,     0,     0,     1,     2,     3,     0,
     138,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,     0,   137,     0,     0,     0,     0,     0,
       0,     0,   191,     0,     0,   138,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,     0,   137,
       0,     0,     0,     0,     0,     0,     0,   218,     0,     0,
     138,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,     0,   137,     0,     0,     0,     0,     0,
       0,     0,   232,     0,     0,   138,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,     0,   137,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
       0,   135,   136,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,     0,     0,   135,   136,     0,     0,
       0,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     138,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,     0,     0,   135,   136,     0,     0,     0,
       0,     0,     0,     0,   115,   116,   117,   118,     0,   138,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,     0,     0,   135,   136,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-235)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      27,    66,    64,    65,   146,   147,     6,    35,   189,     3,
      57,    58,    59,    10,   248,    48,     0,     3,    46,    47,
      48,    36,     6,    38,    21,    56,     0,   208,   209,    26,
      65,    32,    65,    64,    61,   269,    36,    38,    66,    30,
      31,    35,    39,   185,   186,    31,     3,    33,   110,    30,
     231,   232,    36,     9,    10,     3,    42,    13,    14,    15,
      16,    17,    18,    60,    31,    62,    93,    31,    31,    33,
      33,    27,    28,    15,    16,   103,   104,   105,    42,    42,
     107,     3,   109,    59,    60,    27,    28,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   192,   193,   137,
     138,    56,   159,     3,    59,    60,    56,   114,     3,    59,
      60,     7,     8,     9,    10,    30,   154,    13,    14,    15,
      16,    17,    18,     3,   161,    37,    38,    39,    37,    38,
      39,    27,    28,    54,    55,    56,    54,    55,    56,    56,
     197,    54,    55,    56,    32,    41,   203,    37,   223,    39,
     188,   189,    34,    36,   192,   193,    32,    56,    56,    38,
     198,    34,    56,    56,    32,    34,    11,   204,   225,   206,
     208,   209,    56,    40,    26,    56,    35,   105,    56,    56,
     268,   268,     0,   220,    -1,   223,    -1,   224,    -1,    -1,
      -1,    -1,    -1,   231,   232,    -1,    -1,    -1,    -1,    -1,
      -1,   238,     3,     4,     5,     6,     7,     8,    -1,    -1,
     248,    -1,    -1,    -1,    -1,   252,    -1,    -1,    -1,   256,
      -1,    -1,    -1,    -1,    -1,    -1,   263,    -1,    29,    -1,
      31,   269,    33,    -1,    35,    -1,    37,    38,    39,    40,
      -1,    -1,    43,     3,     4,     5,     6,     7,     8,    50,
      51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,
      61,    -1,    63,    -1,    -1,    66,    -1,    -1,    -1,    29,
      -1,    31,    -1,    33,    -1,    35,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    43,     3,     4,     5,     6,     7,     8,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,
      -1,    61,    -1,    63,    -1,    -1,    66,    -1,    -1,    -1,
      29,    -1,    31,    -1,    33,    -1,    35,    -1,    -1,    -1,
      -1,    40,    41,    -1,    43,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,     8,
       9,    10,    -1,    -1,    13,    14,    15,    16,    17,    18,
      -1,    29,    -1,    31,    -1,    33,    -1,    35,    27,    28,
      -1,    -1,    40,    -1,    -1,    43,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    -1,
      41,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      41,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     7,     8,     9,    10,    11,
      41,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     7,     8,     9,    10,    -1,    41,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,    39,    68,    71,   136,   137,   138,     0,
      65,    69,    70,    72,    73,   137,   138,    37,    38,    39,
       3,    35,    83,    87,    48,    70,    31,    84,     3,    85,
      87,    30,    85,    74,   134,   135,   136,   138,    36,    38,
       3,    32,     3,     4,     5,     6,     7,     8,    29,    31,
      33,    35,    40,    43,    50,    51,    52,    53,    57,    58,
      61,    63,    66,    76,    78,    81,    86,    87,    88,    89,
      90,    92,    93,    95,   104,   105,   106,   107,   110,   116,
     117,   118,   119,   120,   121,   122,   123,   128,   129,   132,
     133,   138,    87,    84,     3,    31,    33,    42,    82,     3,
      78,    78,    78,    80,   109,   112,     3,    77,    78,    77,
      77,    87,    74,    87,    91,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    30,    41,   135,
     135,    76,    31,    33,    42,    74,    96,   100,     3,     3,
      78,    78,   113,   114,   115,   113,    74,    74,   135,    30,
      56,    64,    87,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    98,   102,     3,    80,    80,
      79,    38,    37,    39,   108,    78,   111,    54,    55,    56,
     124,   126,    56,    59,    60,   130,    77,    74,    80,    80,
      41,    78,    94,    94,    32,   114,   114,    34,    38,    36,
      77,    74,    75,    86,    77,   131,    74,    74,    56,    94,
      94,    38,    38,    97,   101,    74,    56,    74,    77,    56,
      56,    99,   103,    94,    94,    32,    34,    54,    55,    56,
      56,    59,    60,    74,    32,    34,    77,   125,   127,    75,
      74,    56,    59,    60,    74,    56,    56,    74,    54,    55,
      56,    56,   125,   127,    75,    56
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
#line 220 "TmcParParser.Y"
    {
			(yyval.lsp_L_stmnt_gen_val)=(yyvsp[(2) - (3)].lsp_L_stmnt_gen_val);
			tmcpar_parsing_module = (yyval.lsp_L_stmnt_gen_val);
			YYACCEPT;
		}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 229 "TmcParParser.Y"
    {
            (yyval.lsp_L_stmnt_gen_val) = create_module((yyvsp[(1) - (1)].lsp_T_func_hdr_val));
        }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 233 "TmcParParser.Y"
    {
            (yyval.lsp_L_stmnt_gen_val) = append_to_module((yyvsp[(1) - (2)].lsp_L_stmnt_gen_val),(yyvsp[(2) - (2)].lsp_T_func_hdr_val));
        }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 252 "TmcParParser.Y"
    {
			(yyval.lsp_T_func_hdr_val)=(yyvsp[(1) - (1)].lsp_T_func_hdr_val);
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 265 "TmcParParser.Y"
    {
							(yyval.lsp_T_func_hdr_val) = create_func_def_statement((yyvsp[(1) - (1)].lsp_T_func_block_val),(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 274 "TmcParParser.Y"
    { // fnc name, inpars,outpars,stms
						 (yyval.lsp_T_func_block_val) = create_func_body((yyvsp[(4) - (6)].ident),(yyvsp[(5) - (6)].lsp_L_vardecl_val),(yyvsp[(2) - (6)].lsp_L_vardecl_val),(yyvsp[(6) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 278 "TmcParParser.Y"
    {
						 (yyval.lsp_T_func_block_val) = create_func_body((yyvsp[(2) - (4)].ident),(yyvsp[(3) - (4)].lsp_L_vardecl_val),0,(yyvsp[(4) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 284 "TmcParParser.Y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = (yyvsp[(2) - (2)].lsp_L_stmnt_gen_val);
                   }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 288 "TmcParParser.Y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = create_statement_list_empty();
                   }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 294 "TmcParParser.Y"
    {
					(yyval.lsp_L_stmnt_gen_val) = (yyvsp[(1) - (1)].lsp_L_stmnt_gen_val);
                   }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 298 "TmcParParser.Y"
    {
				     (yyval.lsp_L_stmnt_gen_val) = (yyvsp[(1) - (1)].lsp_L_stmnt_gen_val);
				   }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 306 "TmcParParser.Y"
    {
                    (yyval.lsp_statement_val) = create_expression((yyvsp[(1) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
                   }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 310 "TmcParParser.Y"
    {
                    (yyval.lsp_statement_val) = create_command((yyvsp[(1) - (2)].lsp_command_val),(int)tmcpar_lineno,(int)tmcpar_colno);
                   }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 317 "TmcParParser.Y"
    {
				//$$=$1;
				(yyval.lsp_expression_val) = try_to_colon_expression((yyvsp[(1) - (1)].lsp_expression_val));
				//$$ = create_colon_expression($1,0,0,(int)tmcpar_lineno,(int)tmcpar_colno);
				}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 325 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_ident_val));
					}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 329 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_constant_val));
					}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 333 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_ident_val));
				}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 337 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_unary_expression_val));
					}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 342 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_colon_expression_val);
				}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 347 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_simple_assignment_val));
				}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 352 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_index_expression_val));
					}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 357 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_binary_expression_val));
					}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 361 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_boolean_expression_val));
					}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 365 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=simplify_empty_matrix((yyvsp[(1) - (1)].lsp_cell_val));
					}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 370 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=simplify_empty_matrix((yyvsp[(1) - (1)].lsp_list_of_argument_list_val));
					}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 376 "TmcParParser.Y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_fcn_handle_val));
					}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 381 "TmcParParser.Y"
    {
                                 BracketDelimiter = (yyvsp[(2) - (3)].lsp_delimiter);
                                }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 384 "TmcParParser.Y"
    {
				         yyinsert_comma_in_input(RPAREN);
					(yyval.lsp_expression_val) = (yyvsp[(3) - (5)].lsp_expression_val);
				}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 391 "TmcParParser.Y"
    {
                                (yyval.lsp_delimiter) = BracketDelimiter;
                                BracketDelimiter = LPAREN;
                                }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 401 "TmcParParser.Y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_return_command_val);
					}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 405 "TmcParParser.Y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_cmd_decl_gen_val);
					}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 409 "TmcParParser.Y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_if_val);
					}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 413 "TmcParParser.Y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_while_val);
					}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 418 "TmcParParser.Y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_continue_val);
					}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 422 "TmcParParser.Y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_break_val);
					}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 427 "TmcParParser.Y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_switch_val);
					}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 432 "TmcParParser.Y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_for_val);
					}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 438 "TmcParParser.Y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_tree_try_command_val);
					}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 444 "TmcParParser.Y"
    {
				  (yyval.lsp_command_val) = (T_cmd_gen*)create_ref_index("M",(yyvsp[(2) - (2)].lsp_argument_list_val),create_identifier((yyvsp[(1) - (2)].ident),(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
				  }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 450 "TmcParParser.Y"
    {
					(yyval.lsp_argument_list_val) = create_argument_list((T_expr_gen*)create_constant((CONST_VAL_TYPES)0,make_string((yyvsp[(1) - (1)].ident)),(int)tmcpar_lineno,(int)tmcpar_colno) );
					}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 454 "TmcParParser.Y"
    {
					(yyval.lsp_argument_list_val) = append_to_argument_list((yyvsp[(1) - (2)].lsp_argument_list_val),(T_expr_gen*)create_constant((CONST_VAL_TYPES)0,make_string((yyvsp[(2) - (2)].ident)),(int)tmcpar_lineno,(int)tmcpar_colno) );
					}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 460 "TmcParParser.Y"
    {
					(yyval.lsp_L_vardecl_val)=(yyvsp[(2) - (3)].lsp_L_vardecl_val);
					}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 464 "TmcParParser.Y"
    {
					(yyval.lsp_L_vardecl_val)=create_list_ident((yyvsp[(1) - (1)].lsp_ident_val));
					}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 470 "TmcParParser.Y"
    {
					(yyval.lsp_L_vardecl_val)=(yyvsp[(2) - (3)].lsp_L_vardecl_val);
					}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 474 "TmcParParser.Y"
    {
					(yyval.lsp_L_vardecl_val)=create_list_ident_empty();
					}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 481 "TmcParParser.Y"
    {
					(yyval.lsp_L_vardecl_val) = create_list_ident((yyvsp[(1) - (1)].lsp_ident_val));
					}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 485 "TmcParParser.Y"
    {
                   	(yyval.lsp_L_vardecl_val) = append_to_list_ident((yyvsp[(1) - (3)].lsp_L_vardecl_val),(yyvsp[(3) - (3)].lsp_ident_val));
					}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 491 "TmcParParser.Y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = create_statement_list((yyvsp[(1) - (1)].lsp_statement_val));
                   }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 495 "TmcParParser.Y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = append_to_statement_list((yyvsp[(1) - (2)].lsp_L_stmnt_gen_val),(yyvsp[(2) - (2)].lsp_statement_val));
                   }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 501 "TmcParParser.Y"
    {
					 (yyval.lsp_ident_val) = create_identifier((yyvsp[(1) - (1)].ident),(int)tmcpar_lineno,(int)tmcpar_colno);
					 }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 507 "TmcParParser.Y"
    {
						 (yyval.lsp_ident_val) = create_identifier("__end__",(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 512 "TmcParParser.Y"
    {
					 (yyval.lsp_constant_val) = create_constant((enum CONST_VAL_TYPES)0,(yyvsp[(1) - (1)].lsp_const_val),(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 517 "TmcParParser.Y"
    {
					 (yyval.lsp_const_val) = make_number((yyvsp[(1) - (1)].num),0,const_val_real);
					}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 521 "TmcParParser.Y"
    {
                     (yyval.lsp_const_val) = make_number(0,(yyvsp[(1) - (1)].num),const_val_complex);
                   }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 526 "TmcParParser.Y"
    {
					 (yyval.lsp_const_val) = make_string((yyvsp[(1) - (1)].str));
                   }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 534 "TmcParParser.Y"
    {
			(yyval.lsp_L_vardecl_val) = create_list_ident((yyvsp[(1) - (1)].lsp_ident_val));
		}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 538 "TmcParParser.Y"
    {
                     (yyval.lsp_L_vardecl_val) = append_to_list_ident((yyvsp[(1) - (2)].lsp_L_vardecl_val),(yyvsp[(2) - (2)].lsp_ident_val));
                }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 544 "TmcParParser.Y"
    {
	 (yyval.lsp_simple_assignment_val) = create_s_assignment_expression(0,0,(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 553 "TmcParParser.Y"
    {
           (yyval.lsp_colon_expression_val) = append_colon_expression((yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
          }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 564 "TmcParParser.Y"
    {
          (yyval.lsp_argument_list_val) =  create_argument_list( create_constant((enum CONST_VAL_TYPES)0,make_magic_col(),(int)tmcpar_lineno,(int)tmcpar_colno) );
        }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 568 "TmcParParser.Y"
    {
          (yyval.lsp_argument_list_val) =  create_argument_list( (yyvsp[(1) - (1)].lsp_expression_val));
        }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 572 "TmcParParser.Y"
    {
          (yyval.lsp_argument_list_val) = insert_head_to_argument_list((yyvsp[(3) - (3)].lsp_argument_list_val),create_constant((enum CONST_VAL_TYPES)0,make_magic_col(),(int)tmcpar_lineno,(int)tmcpar_colno));
        }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 576 "TmcParParser.Y"
    {
          (yyval.lsp_argument_list_val) = insert_head_to_argument_list((yyvsp[(3) - (3)].lsp_argument_list_val),(yyvsp[(1) - (3)].lsp_expression_val));
        }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 582 "TmcParParser.Y"
    { indexdeep(1); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 583 "TmcParParser.Y"
    {
        BracketDelimiter = (yyvsp[(4) - (5)].lsp_delimiter);
        }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 586 "TmcParParser.Y"
    {
           (yyval.lsp_index_expression_val) = create_ref_index("M",(yyvsp[(5) - (7)].lsp_argument_list_val),create_identifier((yyvsp[(1) - (7)].ident),(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RPAREN);indexdeep(-1);
        }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 590 "TmcParParser.Y"
    {indexdeep(1);}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 591 "TmcParParser.Y"
    {
        BracketDelimiter = (yyvsp[(4) - (5)].lsp_delimiter);
        }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 594 "TmcParParser.Y"
    {
           (yyval.lsp_index_expression_val) = create_ref_index("M",(yyvsp[(5) - (7)].lsp_argument_list_val),(yyvsp[(1) - (7)].lsp_index_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RPAREN);indexdeep(-1);
        }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 601 "TmcParParser.Y"
    {indexdeep(1);}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 602 "TmcParParser.Y"
    {
        BracketDelimiter = (yyvsp[(4) - (5)].lsp_delimiter);
        }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 605 "TmcParParser.Y"
    {
           (yyval.lsp_index_expression_val) = create_ref_index("C",(yyvsp[(5) - (7)].lsp_argument_list_val),create_identifier((yyvsp[(1) - (7)].ident),(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RC);indexdeep(-1);
        }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 609 "TmcParParser.Y"
    {indexdeep(1);}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 610 "TmcParParser.Y"
    {
        BracketDelimiter = (yyvsp[(4) - (5)].lsp_delimiter);
        }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 613 "TmcParParser.Y"
    {
           (yyval.lsp_index_expression_val) = create_ref_index("C",(yyvsp[(5) - (7)].lsp_argument_list_val),(yyvsp[(1) - (7)].lsp_index_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RC);indexdeep(-1);
        }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 620 "TmcParParser.Y"
    {
            (yyval.lsp_index_expression_val) = create_ref_field("F",(yyvsp[(3) - (3)].ident),create_identifier((yyvsp[(1) - (3)].ident),(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
         yyinsert_comma_in_input(ELLIP);
       }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 625 "TmcParParser.Y"
    {
            (yyval.lsp_index_expression_val) = create_ref_field("F",(yyvsp[(3) - (3)].ident),(yyvsp[(1) - (3)].lsp_index_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(ELLIP);
        }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 636 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("+",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 640 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("-",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 644 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("*",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 648 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression(".*",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 653 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("&",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 657 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("|",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 663 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("/",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 667 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("./",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 672 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("^",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 676 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression(".^",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 681 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("\\",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 685 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression(".\\",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 690 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("<=",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 694 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("<",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 699 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression(">=",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 703 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression(">",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 708 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("!=",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);//legacy
		}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 712 "TmcParParser.Y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("==",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 718 "TmcParParser.Y"
    {
			(yyval.lsp_boolean_expression_val) = create_boolean_expression("&&",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 722 "TmcParParser.Y"
    {
			(yyval.lsp_boolean_expression_val) = create_boolean_expression("||",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 729 "TmcParParser.Y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression("+",(yyvsp[(2) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 733 "TmcParParser.Y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression("-",(yyvsp[(2) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 737 "TmcParParser.Y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression("!",(yyvsp[(2) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);//legacy
		}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 742 "TmcParParser.Y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression(".'",(yyvsp[(1) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
			yyinsert_comma_in_input(TRANSPOSE);
		}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 747 "TmcParParser.Y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression("'",(yyvsp[(1) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
			yyinsert_comma_in_input(CTRANSPOSE);
		}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 755 "TmcParParser.Y"
    {
        BracketDelimiter = (yyvsp[(2) - (3)].lsp_delimiter);
        }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 758 "TmcParParser.Y"
    {
        yyinsert_comma_in_input(RC);
         (yyval.lsp_cell_val) = create_cell_array((yyvsp[(3) - (5)].lsp_list_of_argument_list_val));// convert matrix to cell array
        }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 765 "TmcParParser.Y"
    {
        (yyval.lsp_delimiter) = BracketDelimiter;
        BracketDelimiter = LC;
        }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 774 "TmcParParser.Y"
    {
        BracketDelimiter = (yyvsp[(2) - (3)].lsp_delimiter);
        }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 777 "TmcParParser.Y"
    {
        yyinsert_comma_in_input(RBRA);
         (yyval.lsp_list_of_argument_list_val) = (yyvsp[(3) - (5)].lsp_list_of_argument_list_val);
        }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 784 "TmcParParser.Y"
    {
        (yyval.lsp_delimiter) = BracketDelimiter;
        BracketDelimiter = LBRA;
        }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 792 "TmcParParser.Y"
    {
                         (yyval.lsp_list_of_argument_list_val) = create_empty_matrix();
        }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 796 "TmcParParser.Y"
    {
                         (yyval.lsp_list_of_argument_list_val) = create_matrix((yyvsp[(1) - (1)].lsp_argument_list_val));
        }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 800 "TmcParParser.Y"
    {
         (yyval.lsp_list_of_argument_list_val)=(yyvsp[(1) - (2)].lsp_list_of_argument_list_val);
        }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 804 "TmcParParser.Y"
    {
                         (yyval.lsp_list_of_argument_list_val) = add_row_to_matrix((yyvsp[(1) - (3)].lsp_list_of_argument_list_val),(yyvsp[(3) - (3)].lsp_argument_list_val));
        }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 808 "TmcParParser.Y"
    {
                         (yyval.lsp_list_of_argument_list_val)=(yyvsp[(1) - (2)].lsp_list_of_argument_list_val);
        }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 812 "TmcParParser.Y"
    {
                    (yyval.lsp_list_of_argument_list_val) = add_row_to_matrix((yyvsp[(1) - (3)].lsp_list_of_argument_list_val),(yyvsp[(3) - (3)].lsp_argument_list_val));
        }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 819 "TmcParParser.Y"
    {
                    (yyval.lsp_argument_list_val) = create_argument_list((yyvsp[(1) - (1)].lsp_expression_val));
        }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 823 "TmcParParser.Y"
    {
                    (yyval.lsp_argument_list_val) = (yyvsp[(1) - (1)].lsp_argument_list_val);
        }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 827 "TmcParParser.Y"
    {
                    (yyval.lsp_argument_list_val) = append_to_argument_list((yyvsp[(1) - (2)].lsp_argument_list_val),(yyvsp[(2) - (2)].lsp_expression_val));
        }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 834 "TmcParParser.Y"
    {
          (yyval.lsp_argument_list_val) = create_argument_list((yyvsp[(1) - (2)].lsp_expression_val));
        }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 838 "TmcParParser.Y"
    {
          (yyval.lsp_argument_list_val) = append_to_argument_list((yyvsp[(1) - (3)].lsp_argument_list_val),(yyvsp[(2) - (3)].lsp_expression_val));
        }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 846 "TmcParParser.Y"
    {
			(yyval.lsp_fcn_handle_val) = create_fcn_handle((yyvsp[(2) - (2)].ident),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 855 "TmcParParser.Y"
    {
		(yyval.lsp_return_command_val)=create_return((int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 860 "TmcParParser.Y"
    {
		(yyval.lsp_T_ctrl_cmd_break_val)=create_break((int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 865 "TmcParParser.Y"
    {
		(yyval.lsp_T_ctrl_cmd_continue_val)=create_continue((int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 871 "TmcParParser.Y"
    {
		(yyval.lsp_T_cmd_decl_gen_val)=create_declaration("global",(yyvsp[(2) - (2)].lsp_L_vardecl_val),(int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 880 "TmcParParser.Y"
    {

		(yyval.lsp_T_ctrl_cmd_if_val) = create_if_statement((yyvsp[(1) - (1)].lsp_LT_if_blocks_val),(int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 886 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val)=(yyvsp[(1) - (1)].lsp_LT_if_blocks_val);
	}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 895 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = create_if_clause_list(create_if_clause((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 899 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(4) - (4)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 903 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(4) - (4)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 910 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = create_if_clause_list(create_if_clause((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 914 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(5) - (5)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(2) - (5)].lsp_expression_val),(yyvsp[(3) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 921 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = create_if_clause_list(create_if_clause((yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(2) - (3)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 925 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(4) - (4)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(1) - (4)].lsp_expression_val),(yyvsp[(2) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 932 "TmcParParser.Y"
    {
	  (yyval.lsp_LT_if_blocks_val) = create_if_clause_list(create_if_clause(0,(yyvsp[(2) - (3)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 936 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = append_to_if_clause_list(
		create_if_clause_list(create_if_clause((yyvsp[(2) - (6)].lsp_expression_val),(yyvsp[(3) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)),
		create_if_clause(0,(yyvsp[(5) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)
		);
	}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 943 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(5) - (5)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(2) - (5)].lsp_expression_val),(yyvsp[(3) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 949 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = append_to_if_clause_list(
		create_if_clause_list(create_if_clause((yyvsp[(1) - (5)].lsp_expression_val),(yyvsp[(2) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)),
		create_if_clause(0,(yyvsp[(4) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)
		);
	}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 956 "TmcParParser.Y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(4) - (4)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(1) - (4)].lsp_expression_val),(yyvsp[(2) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 962 "TmcParParser.Y"
    {
				(yyval.lsp_T_ctrl_cmd_while_val)=create_while_command((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno);
			//	yyinsert_comma_in_input(END);
				}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 971 "TmcParParser.Y"
    {
		(yyval.lsp_T_ctrl_cmd_switch_val) =create_switch_command((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(4) - (4)].lsp_LT_sw_cases_val),(int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 978 "TmcParParser.Y"
    {
	 	(yyval.lsp_LT_sw_cases_val) = create_switch_cases_list(create_switch_case((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 982 "TmcParParser.Y"
    {
	 	(yyval.lsp_LT_sw_cases_val) = append_to_switch_cases_list((yyvsp[(2) - (5)].lsp_LT_sw_cases_val),create_switch_case((yyvsp[(3) - (5)].lsp_expression_val),(yyvsp[(4) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 986 "TmcParParser.Y"
    {
	 	(yyval.lsp_LT_sw_cases_val) = append_to_switch_cases_list(create_switch_cases_list(create_switch_case((yyvsp[(2) - (6)].lsp_expression_val),(yyvsp[(3) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)),
                 create_switch_case(0,(yyvsp[(5) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 991 "TmcParParser.Y"
    {
	 	(yyval.lsp_LT_sw_cases_val) =append_to_switch_cases_list(
                    append_to_switch_cases_list((yyvsp[(2) - (7)].lsp_LT_sw_cases_val),create_switch_case((yyvsp[(3) - (7)].lsp_expression_val),(yyvsp[(4) - (7)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)),
                    create_switch_case(0,(yyvsp[(6) - (7)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)
                    );
	}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 998 "TmcParParser.Y"
    {
	 	(yyval.lsp_LT_sw_cases_val) = create_switch_cases_list(create_switch_case(0,(yyvsp[(2) - (3)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1005 "TmcParParser.Y"
    {
		(yyval.lsp_LT_sw_cases_val) = create_switch_cases_list(create_switch_case((yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(2) - (3)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1009 "TmcParParser.Y"
    {
		(yyval.lsp_LT_sw_cases_val) = append_to_switch_cases_list((yyvsp[(1) - (4)].lsp_LT_sw_cases_val),create_switch_case((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1017 "TmcParParser.Y"
    {
				(yyval.lsp_T_ctrl_cmd_for_val)=create_for_statement(/*convert_to_colon_expression*/((yyvsp[(2) - (6)].lsp_ident_val)),(yyvsp[(4) - (6)].lsp_expression_val),(yyvsp[(5) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno);
				}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1028 "TmcParParser.Y"
    {
				(yyval.lsp_tree_try_command_val)=create_try_catch_statement((yyvsp[(2) - (5)].lsp_L_stmnt_gen_val),(yyvsp[(4) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno);
				}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1032 "TmcParParser.Y"
    {
				(yyval.lsp_tree_try_command_val)=create_try_catch_statement((yyvsp[(2) - (3)].lsp_L_stmnt_gen_val),0,(int)tmcpar_lineno,(int)tmcpar_colno);
				}
    break;


/* Line 1792 of yacc.c  */
#line 3062 "TmcParParser.tab.cpp"
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
#line 1062 "TmcParParser.Y"



