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
#line 1 "TmcParParser.y"

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
#define YYLAST   662

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  168
/* YYNRULES -- Number of states.  */
#define YYNSTATES  277

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
     142,   144,   146,   149,   153,   157,   159,   161,   165,   169,
     170,   171,   179,   180,   181,   189,   190,   191,   199,   200,
     201,   209,   213,   217,   221,   225,   229,   233,   237,   241,
     245,   249,   253,   257,   261,   265,   269,   273,   277,   281,
     285,   289,   293,   297,   300,   303,   306,   309,   312,   313,
     319,   320,   321,   327,   328,   329,   331,   334,   338,   341,
     345,   347,   349,   352,   355,   359,   362,   364,   366,   368,
     371,   373,   375,   380,   385,   390,   395,   401,   405,   410,
     414,   421,   427,   433,   438,   443,   448,   453,   459,   466,
     474,   478,   482,   487,   494,   500,   504,   505,   507,   509,
     511,   514,   516,   519,   521,   523,   526,   529,   531
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
       3,    -1,    29,    -1,    43,    -1,    90,    -1,     4,    -1,
       5,    -1,     6,    -1,    87,    -1,    91,    87,    -1,    78,
      30,    78,    -1,    78,    41,    78,    -1,    41,    -1,    78,
      -1,    41,    38,    94,    -1,    78,    38,    94,    -1,    -1,
      -1,     3,    31,    96,    80,    94,    97,    32,    -1,    -1,
      -1,    95,    31,    98,    80,    94,    99,    32,    -1,    -1,
      -1,     3,    33,   100,    80,    94,   101,    34,    -1,    -1,
      -1,    95,    33,   102,    80,    94,   103,    34,    -1,     3,
      42,     3,    -1,    95,    42,     3,    -1,    78,     7,    78,
      -1,    78,     8,    78,    -1,    78,     9,    78,    -1,    78,
      10,    78,    -1,    78,    11,    78,    -1,    78,    12,    78,
      -1,    78,    13,    78,    -1,    78,    14,    78,    -1,    78,
      15,    78,    -1,    78,    16,    78,    -1,    78,    17,    78,
      -1,    78,    18,    78,    -1,    78,    19,    78,    -1,    78,
      20,    78,    -1,    78,    21,    78,    -1,    78,    22,    78,
      -1,    78,    23,    78,    -1,    78,    24,    78,    -1,    78,
      25,    78,    -1,    78,    26,    78,    -1,     7,    78,    -1,
       8,    78,    -1,    29,    78,    -1,    78,    27,    -1,    78,
      28,    -1,    -1,    33,   109,   113,   108,    34,    -1,    -1,
      -1,    35,   112,   113,   111,    36,    -1,    -1,    -1,   114,
      -1,   113,    37,    -1,   113,    37,   114,    -1,   113,    39,
      -1,   113,    39,   114,    -1,    78,    -1,   115,    -1,   115,
      78,    -1,    78,    38,    -1,   115,    78,    38,    -1,    40,
       3,    -1,    50,    -1,    51,    -1,    52,    -1,    66,    91,
      -1,   122,    -1,   123,    -1,    53,    77,    74,    56,    -1,
      53,    77,    74,   124,    -1,    53,    77,    74,   126,    -1,
      54,    77,    74,    56,    -1,    54,    77,    74,    54,   125,
      -1,    77,    74,    56,    -1,    77,    74,    54,   125,    -1,
      55,    75,    56,    -1,    54,    77,    74,    55,    75,    56,
      -1,    54,    77,    74,    54,   127,    -1,    77,    74,    55,
      75,    56,    -1,    77,    74,    54,   127,    -1,    57,    77,
      74,    56,    -1,    58,    77,   135,   130,    -1,    59,    77,
      74,    56,    -1,    59,   131,    77,    74,    56,    -1,    59,
      77,    74,    60,    74,    56,    -1,    59,   131,    77,    74,
      60,    74,    56,    -1,    60,    74,    56,    -1,    77,    74,
      59,    -1,   131,    77,    74,    59,    -1,    61,    87,    30,
      77,    74,    56,    -1,    63,    74,    64,    74,    56,    -1,
      63,    74,    56,    -1,    -1,   135,    -1,   136,    -1,   138,
      -1,   136,   138,    -1,   137,    -1,   136,   137,    -1,    38,
      -1,    37,    -1,   138,    38,    -1,   138,    37,    -1,    39,
      -1,   138,    39,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   219,   219,   228,   232,   251,   257,   259,   260,   264,
     273,   277,   283,   287,   293,   297,   305,   309,   316,   324,
     328,   332,   336,   341,   346,   351,   356,   360,   364,   369,
     375,   381,   380,   391,   400,   404,   408,   412,   417,   421,
     426,   431,   437,   443,   449,   453,   459,   463,   469,   474,
     481,   485,   491,   495,   501,   506,   512,   517,   522,   526,
     531,   539,   543,   549,   558,   569,   573,   577,   581,   588,
     589,   588,   596,   597,   596,   607,   608,   607,   615,   616,
     615,   625,   630,   641,   645,   649,   653,   658,   662,   668,
     672,   677,   681,   686,   690,   695,   699,   704,   708,   713,
     717,   723,   727,   734,   738,   742,   747,   752,   761,   760,
     771,   780,   779,   790,   798,   801,   805,   809,   813,   817,
     824,   828,   832,   839,   843,   851,   860,   865,   870,   876,
     885,   891,   900,   904,   908,   915,   919,   926,   930,   937,
     941,   948,   954,   961,   967,   976,   983,   987,   991,   996,
    1003,  1010,  1014,  1022,  1033,  1037,  1044,  1046,  1049,  1050,
    1051,  1054,  1055,  1058,  1059,  1060,  1061,  1064,  1065
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
      85,    85,    86,    86,    87,    87,    88,    89,    90,    90,
      90,    91,    91,    92,    93,    94,    94,    94,    94,    96,
      97,    95,    98,    99,    95,   100,   101,    95,   102,   103,
      95,    95,    95,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   105,   105,   106,   106,   106,   106,   106,   108,   107,
     109,   111,   110,   112,   113,   113,   113,   113,   113,   113,
     114,   114,   114,   115,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   123,   123,   124,   124,   125,   125,   126,
     126,   126,   127,   127,   128,   129,   130,   130,   130,   130,
     130,   131,   131,   132,   133,   133,   134,   134,   135,   135,
     135,   136,   136,   137,   137,   137,   137,   138,   138
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
       1,     1,     2,     3,     3,     1,     1,     3,     3,     0,
       0,     7,     0,     0,     7,     0,     0,     7,     0,     0,
       7,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     0,     5,
       0,     0,     5,     0,     0,     1,     2,     3,     2,     3,
       1,     1,     2,     2,     3,     2,     1,     1,     1,     2,
       1,     1,     4,     4,     4,     4,     5,     3,     4,     3,
       6,     5,     5,     4,     4,     4,     4,     5,     6,     7,
       3,     3,     4,     6,     5,     3,     0,     1,     1,     1,
       2,     1,     2,     1,     1,     2,     2,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,   164,   163,   167,     0,     0,     8,   161,     7,     1,
       0,     0,     3,     5,     9,   162,     0,   166,   165,   168,
      49,    55,     0,     0,    47,     2,     4,     0,   156,    54,
       0,    50,     0,     0,    11,    13,   157,   158,   159,    46,
       0,    49,    48,    54,    58,    59,    60,     0,     0,    55,
      33,   110,   113,     0,    56,   126,   127,   128,     0,     0,
       0,     0,   156,     0,    52,     0,     0,    12,    19,    21,
      20,    57,    24,    23,    25,    26,    27,    22,    28,    29,
      30,    34,    39,    38,    35,    36,   130,   131,    37,    40,
      41,    42,   160,    51,   156,    44,    69,    75,     0,    43,
      54,   103,   104,   105,     0,   114,   114,   125,   156,    18,
     156,     0,     0,     0,    61,   129,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   106,   107,     0,     0,
      16,    17,    53,    72,    78,     0,    10,    33,    33,    81,
      45,    31,   120,   108,   115,   121,   111,     0,     0,     0,
       0,   155,   156,    62,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,    63,    64,    33,    33,    82,     0,
       0,     0,   123,   116,   118,     0,   122,     0,     0,   156,
     132,   133,   134,   144,     0,   156,   145,   156,     0,     0,
       0,    65,    66,    70,    76,    32,   117,   119,   109,   124,
     112,   156,    14,     0,    15,   156,     0,     0,     0,   154,
      73,    79,     0,     0,     0,     0,     0,   139,     0,   156,
     150,   153,     0,     0,    67,    68,    71,    77,     0,   156,
     135,   146,   151,   156,     0,    74,    80,   156,   136,   141,
       0,     0,   147,   152,   156,     0,   140,   148,     0,     0,
     156,   137,   149,   138,   143,     0,   142
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    11,    12,     5,    13,    14,   222,   223,    64,
     257,   109,   191,   104,    66,    99,    23,    28,    30,   224,
      68,    69,    70,    71,   115,    72,    73,   213,    74,   147,
     234,   186,   242,   148,   235,   187,   243,    75,    76,    77,
      78,   195,   105,    79,   197,   106,   153,   154,   155,    80,
      81,    82,    83,    84,    85,    86,    87,   201,   258,   202,
     259,    88,    89,   206,   226,    90,    91,    35,    36,    37,
       7,    38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -217
static const yytype_int16 yypact[] =
{
      92,  -217,  -217,  -217,     8,   -30,    92,  -217,   101,  -217,
      34,     3,  -217,  -217,  -217,  -217,   101,  -217,  -217,  -217,
      55,  -217,    11,    31,  -217,  -217,  -217,    11,    92,  -217,
     -21,  -217,    46,   -16,  -217,  -217,   250,    92,   101,  -217,
      11,    39,  -217,    10,  -217,  -217,  -217,   112,   112,   291,
    -217,  -217,  -217,    71,  -217,  -217,  -217,  -217,   112,   112,
     112,    11,    92,    11,  -217,   328,    92,   250,  -217,  -217,
    -217,  -217,  -217,  -217,    80,  -217,  -217,  -217,  -217,  -217,
    -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,  -217,   101,  -217,    92,  -217,  -217,  -217,    75,   122,
      90,    56,    56,    56,   112,   112,   112,  -217,    92,   468,
      92,    92,   105,    -6,  -217,    11,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,  -217,  -217,   112,   112,
    -217,  -217,  -217,  -217,  -217,   139,  -217,  -217,  -217,  -217,
    -217,   468,   363,    42,  -217,   112,    42,   128,    88,    48,
     112,  -217,    92,  -217,   158,   158,    56,    56,   596,   567,
      56,    56,  -217,  -217,    56,    56,   618,   618,   618,   618,
     618,   618,   538,   503,   468,   634,  -217,  -217,  -217,    24,
      24,   114,  -217,   112,   112,   117,   398,   118,   112,   209,
    -217,  -217,  -217,  -217,   112,    92,  -217,    92,    97,    24,
      24,   119,   433,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,    92,  -217,   103,   250,    92,   112,   106,   107,  -217,
    -217,  -217,    24,    24,   134,   135,   133,  -217,    68,    92,
    -217,  -217,   162,   164,  -217,  -217,  -217,  -217,   112,   209,
    -217,  -217,  -217,    92,    77,  -217,  -217,    92,  -217,  -217,
     140,   143,  -217,  -217,    92,   136,  -217,  -217,   144,   112,
     209,  -217,  -217,  -217,  -217,   145,  -217
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -217,  -217,  -217,   191,  -217,  -217,  -217,   -28,  -216,   -66,
     -48,   -29,  -217,  -142,  -217,  -217,  -217,   165,   178,   171,
      -1,  -217,  -217,  -217,  -217,  -217,  -217,  -186,  -217,  -217,
    -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,  -217,  -217,  -217,  -217,  -217,   102,   -45,  -217,  -217,
    -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,   -60,  -217,
     -59,  -217,  -217,  -217,  -217,  -217,  -217,  -217,   -63,   218,
      19,    36
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -55
static const yytype_int16 yytable[] =
{
      34,   142,   140,   141,   214,   189,   190,    65,     9,    24,
     108,   110,   111,    95,    29,    39,    42,    40,   101,   102,
     103,    31,    40,   230,   231,    15,    31,   100,    44,    45,
      46,    47,    48,   260,   113,    10,     8,    20,    65,    93,
      21,    96,    16,    97,   209,   210,   244,   245,   159,    41,
     161,    25,    98,    49,   275,    50,    15,    51,   162,    52,
     112,    32,   114,    21,    53,   211,   146,    54,    10,    22,
      27,   124,   125,    92,   107,   151,   152,   152,   149,   193,
     157,   194,   158,   136,   137,   -54,    27,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   204,   205,   184,
     185,   143,   207,   144,   163,   100,    44,    45,    46,    47,
      48,    96,   145,    97,   251,   150,   196,   252,   253,     1,
       2,     3,    98,   262,   208,   160,   263,   264,    17,    18,
      19,    49,   188,    50,   203,    51,   215,    52,   216,   217,
     221,   218,    53,   229,   220,    54,   225,   232,   142,   237,
     212,   212,   240,   241,   152,   152,   246,   118,   119,   247,
      65,   122,   123,   124,   125,   126,   127,   227,   239,   228,
     212,   212,   198,   199,   200,   136,   137,   248,   249,   250,
     269,   270,   271,   236,   255,    65,   266,   238,   256,   267,
     272,   276,    26,   212,   212,    33,    94,    67,   156,   273,
     274,   254,    43,    44,    45,    46,    47,    48,     6,     0,
      65,     0,     0,     0,     0,   261,     0,     0,     0,   265,
       0,     0,     0,     0,     0,     0,   268,     0,    49,     0,
      50,    65,    51,     0,    52,     0,     1,     2,     3,    53,
       0,     0,    54,    43,    44,    45,    46,    47,    48,    55,
      56,    57,    58,     0,     0,     0,    59,    60,     0,     0,
      61,     0,    62,     0,     0,    63,     0,     0,     0,    49,
       0,    50,     0,    51,     0,    52,     0,     0,     0,     0,
      53,     0,     0,    54,   100,    44,    45,    46,     0,     0,
      55,    56,    57,    58,     0,     0,     0,    59,    60,     0,
       0,    61,     0,    62,     0,     0,    63,     0,     0,     0,
      49,     0,    50,     0,    51,     0,    52,     0,     0,     0,
       0,    53,     0,     0,    54,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,     0,   138,     0,
       0,     0,     0,     0,     0,     1,     2,     3,     0,   139,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,     0,   138,     0,     0,     0,     0,     0,     0,
       0,   192,     0,     0,   139,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,     0,   138,     0,
       0,     0,     0,     0,     0,     0,   219,     0,     0,   139,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,     0,   138,     0,     0,     0,     0,     0,     0,
       0,   233,     0,     0,   139,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,     0,   138,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   139,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,     0,
     136,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   139,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,     0,     0,   136,   137,     0,     0,     0,
       0,     0,     0,     0,   116,   117,   118,   119,   120,   139,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,     0,     0,   136,   137,     0,     0,     0,     0,
       0,     0,     0,   116,   117,   118,   119,     0,   139,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,     0,   136,   137,   116,   117,   118,   119,     0,
       0,   122,   123,   124,   125,   126,   127,   139,     0,     0,
       0,   116,   117,   118,   119,   136,   137,   122,   123,   124,
     125,   126,   127,     0,     0,     0,     0,     0,     0,   139,
       0,   136,   137
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-217)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      28,    67,    65,    66,   190,   147,   148,    36,     0,    10,
      58,    59,    60,     3,     3,    36,    32,    38,    47,    48,
      49,    22,    38,   209,   210,     6,    27,     3,     4,     5,
       6,     7,     8,   249,    62,    65,     0,     3,    67,    40,
      29,    31,     6,    33,   186,   187,   232,   233,   111,     3,
      56,    48,    42,    29,   270,    31,    37,    33,    64,    35,
      61,    30,    63,    29,    40,    41,    94,    43,    65,    35,
      31,    15,    16,    37,     3,   104,   105,   106,     3,    37,
     108,    39,   110,    27,    28,    30,    31,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,    59,    60,   138,
     139,    31,   160,    33,   115,     3,     4,     5,     6,     7,
       8,    31,    42,    33,    56,     3,   155,    59,    60,    37,
      38,    39,    42,    56,   162,    30,    59,    60,    37,    38,
      39,    29,     3,    31,    56,    33,    32,    35,   193,   194,
     198,    34,    40,    56,    36,    43,   204,    38,   224,    56,
     189,   190,    56,    56,   193,   194,    32,     9,    10,    34,
     199,    13,    14,    15,    16,    17,    18,   205,   226,   207,
     209,   210,    54,    55,    56,    27,    28,    54,    55,    56,
      54,    55,    56,   221,    32,   224,    56,   225,    34,    56,
      56,    56,    11,   232,   233,    27,    41,    36,   106,   269,
     269,   239,     3,     4,     5,     6,     7,     8,     0,    -1,
     249,    -1,    -1,    -1,    -1,   253,    -1,    -1,    -1,   257,
      -1,    -1,    -1,    -1,    -1,    -1,   264,    -1,    29,    -1,
      31,   270,    33,    -1,    35,    -1,    37,    38,    39,    40,
      -1,    -1,    43,     3,     4,     5,     6,     7,     8,    50,
      51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,
      61,    -1,    63,    -1,    -1,    66,    -1,    -1,    -1,    29,
      -1,    31,    -1,    33,    -1,    35,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    43,     3,     4,     5,     6,    -1,    -1,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,
      -1,    61,    -1,    63,    -1,    -1,    66,    -1,    -1,    -1,
      29,    -1,    31,    -1,    33,    -1,    35,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    43,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    -1,    41,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    41,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    41,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     7,     8,     9,    10,    11,    41,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     7,     8,     9,    10,    -1,    41,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    27,    28,     7,     8,     9,    10,    -1,
      -1,    13,    14,    15,    16,    17,    18,    41,    -1,    -1,
      -1,     7,     8,     9,    10,    27,    28,    13,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      -1,    27,    28
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,    39,    68,    71,   136,   137,   138,     0,
      65,    69,    70,    72,    73,   137,   138,    37,    38,    39,
       3,    29,    35,    83,    87,    48,    70,    31,    84,     3,
      85,    87,    30,    85,    74,   134,   135,   136,   138,    36,
      38,     3,    32,     3,     4,     5,     6,     7,     8,    29,
      31,    33,    35,    40,    43,    50,    51,    52,    53,    57,
      58,    61,    63,    66,    76,    78,    81,    86,    87,    88,
      89,    90,    92,    93,    95,   104,   105,   106,   107,   110,
     116,   117,   118,   119,   120,   121,   122,   123,   128,   129,
     132,   133,   138,    87,    84,     3,    31,    33,    42,    82,
       3,    78,    78,    78,    80,   109,   112,     3,    77,    78,
      77,    77,    87,    74,    87,    91,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    30,    41,
     135,   135,    76,    31,    33,    42,    74,    96,   100,     3,
       3,    78,    78,   113,   114,   115,   113,    74,    74,   135,
      30,    56,    64,    87,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    98,   102,     3,    80,
      80,    79,    38,    37,    39,   108,    78,   111,    54,    55,
      56,   124,   126,    56,    59,    60,   130,    77,    74,    80,
      80,    41,    78,    94,    94,    32,   114,   114,    34,    38,
      36,    77,    74,    75,    86,    77,   131,    74,    74,    56,
      94,    94,    38,    38,    97,   101,    74,    56,    74,    77,
      56,    56,    99,   103,    94,    94,    32,    34,    54,    55,
      56,    56,    59,    60,    74,    32,    34,    77,   125,   127,
      75,    74,    56,    59,    60,    74,    56,    56,    74,    54,
      55,    56,    56,   125,   127,    75,    56
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
#line 220 "TmcParParser.y"
    {
			(yyval.lsp_L_stmnt_gen_val)=(yyvsp[(2) - (3)].lsp_L_stmnt_gen_val);
			tmcpar_parsing_module = (yyval.lsp_L_stmnt_gen_val);
			YYACCEPT;
		}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 229 "TmcParParser.y"
    {
            (yyval.lsp_L_stmnt_gen_val) = create_module((yyvsp[(1) - (1)].lsp_T_func_hdr_val));
        }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 233 "TmcParParser.y"
    {
            (yyval.lsp_L_stmnt_gen_val) = append_to_module((yyvsp[(1) - (2)].lsp_L_stmnt_gen_val),(yyvsp[(2) - (2)].lsp_T_func_hdr_val));
        }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 252 "TmcParParser.y"
    {
			(yyval.lsp_T_func_hdr_val)=(yyvsp[(1) - (1)].lsp_T_func_hdr_val);
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 265 "TmcParParser.y"
    {
							(yyval.lsp_T_func_hdr_val) = create_func_def_statement((yyvsp[(1) - (1)].lsp_T_func_block_val),(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 274 "TmcParParser.y"
    { // fnc name, inpars,outpars,stms
						 (yyval.lsp_T_func_block_val) = create_func_body((yyvsp[(4) - (6)].ident),(yyvsp[(5) - (6)].lsp_L_vardecl_val),(yyvsp[(2) - (6)].lsp_L_vardecl_val),(yyvsp[(6) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 278 "TmcParParser.y"
    {
						 (yyval.lsp_T_func_block_val) = create_func_body((yyvsp[(2) - (4)].ident),(yyvsp[(3) - (4)].lsp_L_vardecl_val),0,(yyvsp[(4) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 284 "TmcParParser.y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = (yyvsp[(2) - (2)].lsp_L_stmnt_gen_val);
                   }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 288 "TmcParParser.y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = create_statement_list_empty();
                   }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 294 "TmcParParser.y"
    {
					(yyval.lsp_L_stmnt_gen_val) = (yyvsp[(1) - (1)].lsp_L_stmnt_gen_val);
                   }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 298 "TmcParParser.y"
    {
				     (yyval.lsp_L_stmnt_gen_val) = (yyvsp[(1) - (1)].lsp_L_stmnt_gen_val);
				   }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 306 "TmcParParser.y"
    {
                    (yyval.lsp_statement_val) = create_expression((yyvsp[(1) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
                   }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 310 "TmcParParser.y"
    {
                    (yyval.lsp_statement_val) = create_command((yyvsp[(1) - (2)].lsp_command_val),(int)tmcpar_lineno,(int)tmcpar_colno);
                   }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 317 "TmcParParser.y"
    {
				//$$=$1;
				(yyval.lsp_expression_val) = try_to_colon_expression((yyvsp[(1) - (1)].lsp_expression_val));
				//$$ = create_colon_expression($1,0,0,(int)tmcpar_lineno,(int)tmcpar_colno);
				}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 325 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_ident_val));
					}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 329 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_constant_val));
					}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 333 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_ident_val));
				}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 337 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_unary_expression_val));
					}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 342 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)(yyvsp[(1) - (1)].lsp_colon_expression_val);
				}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 347 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_simple_assignment_val));
				}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 352 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_index_expression_val));
					}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 357 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_binary_expression_val));
					}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 361 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_boolean_expression_val));
					}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 365 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=simplify_empty_matrix((yyvsp[(1) - (1)].lsp_cell_val));
					}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 370 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=simplify_empty_matrix((yyvsp[(1) - (1)].lsp_list_of_argument_list_val));
					}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 376 "TmcParParser.y"
    {
					(yyval.lsp_expression_val)=(T_expr_gen*)((yyvsp[(1) - (1)].lsp_fcn_handle_val));
					}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 381 "TmcParParser.y"
    {
                                 BracketDelimiter = (yyvsp[(2) - (3)].lsp_delimiter);
                                }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 384 "TmcParParser.y"
    {
				         yyinsert_comma_in_input(RPAREN);
					(yyval.lsp_expression_val) = (yyvsp[(3) - (5)].lsp_expression_val);
				}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 391 "TmcParParser.y"
    {
                                (yyval.lsp_delimiter) = BracketDelimiter;
                                BracketDelimiter = LPAREN;
                                }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 401 "TmcParParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_return_command_val);
					}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 405 "TmcParParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_cmd_decl_gen_val);
					}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 409 "TmcParParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_if_val);
					}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 413 "TmcParParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_while_val);
					}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 418 "TmcParParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_continue_val);
					}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 422 "TmcParParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_break_val);
					}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 427 "TmcParParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_switch_val);
					}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 432 "TmcParParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_T_ctrl_cmd_for_val);
					}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 438 "TmcParParser.y"
    {
					(yyval.lsp_command_val)=(T_cmd_gen*)(yyvsp[(1) - (1)].lsp_tree_try_command_val);
					}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 444 "TmcParParser.y"
    {
				  (yyval.lsp_command_val) = (T_cmd_gen*)create_ref_index("M",(yyvsp[(2) - (2)].lsp_argument_list_val),create_identifier((yyvsp[(1) - (2)].ident),(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
				  }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 450 "TmcParParser.y"
    {
					(yyval.lsp_argument_list_val) = create_argument_list((T_expr_gen*)create_constant((CONST_VAL_TYPES)0,make_string((yyvsp[(1) - (1)].ident)),(int)tmcpar_lineno,(int)tmcpar_colno) );
					}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 454 "TmcParParser.y"
    {
					(yyval.lsp_argument_list_val) = append_to_argument_list((yyvsp[(1) - (2)].lsp_argument_list_val),(T_expr_gen*)create_constant((CONST_VAL_TYPES)0,make_string((yyvsp[(2) - (2)].ident)),(int)tmcpar_lineno,(int)tmcpar_colno) );
					}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 460 "TmcParParser.y"
    {
					(yyval.lsp_L_vardecl_val)=(yyvsp[(2) - (3)].lsp_L_vardecl_val);
					}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 464 "TmcParParser.y"
    {
					(yyval.lsp_L_vardecl_val)=create_list_ident((yyvsp[(1) - (1)].lsp_ident_val));
					}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 470 "TmcParParser.y"
    {
					(yyval.lsp_L_vardecl_val)=(yyvsp[(2) - (3)].lsp_L_vardecl_val);
					}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 474 "TmcParParser.y"
    {
					(yyval.lsp_L_vardecl_val)=create_list_ident_empty();
					}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 482 "TmcParParser.y"
    {
					(yyval.lsp_L_vardecl_val) = create_list_ident((yyvsp[(1) - (1)].lsp_ident_val));
					}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 486 "TmcParParser.y"
    {
                   	(yyval.lsp_L_vardecl_val) = append_to_list_ident((yyvsp[(1) - (3)].lsp_L_vardecl_val),(yyvsp[(3) - (3)].lsp_ident_val));
					}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 492 "TmcParParser.y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = create_statement_list((yyvsp[(1) - (1)].lsp_statement_val));
                   }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 496 "TmcParParser.y"
    {
                   (yyval.lsp_L_stmnt_gen_val) = append_to_statement_list((yyvsp[(1) - (2)].lsp_L_stmnt_gen_val),(yyvsp[(2) - (2)].lsp_statement_val));
                   }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 502 "TmcParParser.y"
    {
					 (yyval.lsp_ident_val) = create_identifier((yyvsp[(1) - (1)].ident),(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 507 "TmcParParser.y"
    {
					 (yyval.lsp_ident_val) = create_identifier_dummy((int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 513 "TmcParParser.y"
    {
						 (yyval.lsp_ident_val) = create_identifier("__end__",(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 518 "TmcParParser.y"
    {
					 (yyval.lsp_constant_val) = create_constant((enum CONST_VAL_TYPES)0,(yyvsp[(1) - (1)].lsp_const_val),(int)tmcpar_lineno,(int)tmcpar_colno);
					}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 523 "TmcParParser.y"
    {
					 (yyval.lsp_const_val) = make_number((yyvsp[(1) - (1)].num),0,const_val_real);
					}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 527 "TmcParParser.y"
    {
                     (yyval.lsp_const_val) = make_number(0,(yyvsp[(1) - (1)].num),const_val_complex);
                   }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 532 "TmcParParser.y"
    {
					 (yyval.lsp_const_val) = make_string((yyvsp[(1) - (1)].str));
                   }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 540 "TmcParParser.y"
    {
			(yyval.lsp_L_vardecl_val) = create_list_ident((yyvsp[(1) - (1)].lsp_ident_val));
		}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 544 "TmcParParser.y"
    {
                     (yyval.lsp_L_vardecl_val) = append_to_list_ident((yyvsp[(1) - (2)].lsp_L_vardecl_val),(yyvsp[(2) - (2)].lsp_ident_val));
                }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 550 "TmcParParser.y"
    {
	 (yyval.lsp_simple_assignment_val) = create_s_assignment_expression(0,0,(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 559 "TmcParParser.y"
    {
           (yyval.lsp_colon_expression_val) = append_colon_expression((yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
          }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 570 "TmcParParser.y"
    {
          (yyval.lsp_argument_list_val) =  create_argument_list( create_constant((enum CONST_VAL_TYPES)0,make_magic_col(),(int)tmcpar_lineno,(int)tmcpar_colno) );
        }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 574 "TmcParParser.y"
    {
          (yyval.lsp_argument_list_val) =  create_argument_list( (yyvsp[(1) - (1)].lsp_expression_val));
        }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 578 "TmcParParser.y"
    {
          (yyval.lsp_argument_list_val) = insert_head_to_argument_list((yyvsp[(3) - (3)].lsp_argument_list_val),create_constant((enum CONST_VAL_TYPES)0,make_magic_col(),(int)tmcpar_lineno,(int)tmcpar_colno));
        }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 582 "TmcParParser.y"
    {
          (yyval.lsp_argument_list_val) = insert_head_to_argument_list((yyvsp[(3) - (3)].lsp_argument_list_val),(yyvsp[(1) - (3)].lsp_expression_val));
        }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 588 "TmcParParser.y"
    { indexdeep(1); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 589 "TmcParParser.y"
    {
        BracketDelimiter = (yyvsp[(4) - (5)].lsp_delimiter);
        }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 592 "TmcParParser.y"
    {
           (yyval.lsp_index_expression_val) = create_ref_index("M",(yyvsp[(5) - (7)].lsp_argument_list_val),create_identifier((yyvsp[(1) - (7)].ident),(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RPAREN);indexdeep(-1);
        }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 596 "TmcParParser.y"
    {indexdeep(1);}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 597 "TmcParParser.y"
    {
        BracketDelimiter = (yyvsp[(4) - (5)].lsp_delimiter);
        }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 600 "TmcParParser.y"
    {
           (yyval.lsp_index_expression_val) = create_ref_index("M",(yyvsp[(5) - (7)].lsp_argument_list_val),(yyvsp[(1) - (7)].lsp_index_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RPAREN);indexdeep(-1);
        }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 607 "TmcParParser.y"
    {indexdeep(1);}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 608 "TmcParParser.y"
    {
        BracketDelimiter = (yyvsp[(4) - (5)].lsp_delimiter);
        }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 611 "TmcParParser.y"
    {
           (yyval.lsp_index_expression_val) = create_ref_index("C",(yyvsp[(5) - (7)].lsp_argument_list_val),create_identifier((yyvsp[(1) - (7)].ident),(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RC);indexdeep(-1);
        }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 615 "TmcParParser.y"
    {indexdeep(1);}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 616 "TmcParParser.y"
    {
        BracketDelimiter = (yyvsp[(4) - (5)].lsp_delimiter);
        }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 619 "TmcParParser.y"
    {
           (yyval.lsp_index_expression_val) = create_ref_index("C",(yyvsp[(5) - (7)].lsp_argument_list_val),(yyvsp[(1) - (7)].lsp_index_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RC);indexdeep(-1);
        }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 626 "TmcParParser.y"
    {
            (yyval.lsp_index_expression_val) = create_ref_field("F",(yyvsp[(3) - (3)].ident),create_identifier((yyvsp[(1) - (3)].ident),(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
         yyinsert_comma_in_input(ELLIP);
       }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 631 "TmcParParser.y"
    {
            (yyval.lsp_index_expression_val) = create_ref_field("F",(yyvsp[(3) - (3)].ident),(yyvsp[(1) - (3)].lsp_index_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(ELLIP);
        }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 642 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("+",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 646 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("-",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 650 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("*",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 654 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression(".*",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 659 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("&",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 663 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("|",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 669 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("/",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 673 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("./",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 678 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("^",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 682 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression(".^",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 687 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("\\",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 691 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression(".\\",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 696 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("<=",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 700 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("<",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 705 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression(">=",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 709 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression(">",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 714 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("!=",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);//legacy
		}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 718 "TmcParParser.y"
    {
			(yyval.lsp_binary_expression_val) = create_binary_expression("==",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 724 "TmcParParser.y"
    {
			(yyval.lsp_boolean_expression_val) = create_boolean_expression("&&",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 728 "TmcParParser.y"
    {
			(yyval.lsp_boolean_expression_val) = create_boolean_expression("||",(yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(3) - (3)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 735 "TmcParParser.y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression("+",(yyvsp[(2) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 739 "TmcParParser.y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression("-",(yyvsp[(2) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 743 "TmcParParser.y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression("!",(yyvsp[(2) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);//legacy
		}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 748 "TmcParParser.y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression(".'",(yyvsp[(1) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
			yyinsert_comma_in_input(TRANSPOSE);
		}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 753 "TmcParParser.y"
    {
			(yyval.lsp_unary_expression_val) = create_unary_expression("'",(yyvsp[(1) - (2)].lsp_expression_val),(int)tmcpar_lineno,(int)tmcpar_colno);
			yyinsert_comma_in_input(CTRANSPOSE);
		}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 761 "TmcParParser.y"
    {
        BracketDelimiter = (yyvsp[(2) - (3)].lsp_delimiter);
        }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 764 "TmcParParser.y"
    {
        yyinsert_comma_in_input(RC);
         (yyval.lsp_cell_val) = create_cell_array((yyvsp[(3) - (5)].lsp_list_of_argument_list_val));// convert matrix to cell array
        }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 771 "TmcParParser.y"
    {
        (yyval.lsp_delimiter) = BracketDelimiter;
        BracketDelimiter = LC;
        }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 780 "TmcParParser.y"
    {
        BracketDelimiter = (yyvsp[(2) - (3)].lsp_delimiter);
        }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 783 "TmcParParser.y"
    {
        yyinsert_comma_in_input(RBRA);
         (yyval.lsp_list_of_argument_list_val) = (yyvsp[(3) - (5)].lsp_list_of_argument_list_val);
        }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 790 "TmcParParser.y"
    {
        (yyval.lsp_delimiter) = BracketDelimiter;
        BracketDelimiter = LBRA;
        }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 798 "TmcParParser.y"
    {
                         (yyval.lsp_list_of_argument_list_val) = create_empty_matrix();
        }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 802 "TmcParParser.y"
    {
                         (yyval.lsp_list_of_argument_list_val) = create_matrix((yyvsp[(1) - (1)].lsp_argument_list_val));
        }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 806 "TmcParParser.y"
    {
         (yyval.lsp_list_of_argument_list_val)=(yyvsp[(1) - (2)].lsp_list_of_argument_list_val);
        }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 810 "TmcParParser.y"
    {
                         (yyval.lsp_list_of_argument_list_val) = add_row_to_matrix((yyvsp[(1) - (3)].lsp_list_of_argument_list_val),(yyvsp[(3) - (3)].lsp_argument_list_val));
        }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 814 "TmcParParser.y"
    {
                         (yyval.lsp_list_of_argument_list_val)=(yyvsp[(1) - (2)].lsp_list_of_argument_list_val);
        }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 818 "TmcParParser.y"
    {
                    (yyval.lsp_list_of_argument_list_val) = add_row_to_matrix((yyvsp[(1) - (3)].lsp_list_of_argument_list_val),(yyvsp[(3) - (3)].lsp_argument_list_val));
        }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 825 "TmcParParser.y"
    {
                    (yyval.lsp_argument_list_val) = create_argument_list((yyvsp[(1) - (1)].lsp_expression_val));
        }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 829 "TmcParParser.y"
    {
                    (yyval.lsp_argument_list_val) = (yyvsp[(1) - (1)].lsp_argument_list_val);
        }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 833 "TmcParParser.y"
    {
                    (yyval.lsp_argument_list_val) = append_to_argument_list((yyvsp[(1) - (2)].lsp_argument_list_val),(yyvsp[(2) - (2)].lsp_expression_val));
        }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 840 "TmcParParser.y"
    {
          (yyval.lsp_argument_list_val) = create_argument_list((yyvsp[(1) - (2)].lsp_expression_val));
        }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 844 "TmcParParser.y"
    {
          (yyval.lsp_argument_list_val) = append_to_argument_list((yyvsp[(1) - (3)].lsp_argument_list_val),(yyvsp[(2) - (3)].lsp_expression_val));
        }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 852 "TmcParParser.y"
    {
			(yyval.lsp_fcn_handle_val) = create_fcn_handle((yyvsp[(2) - (2)].ident),(int)tmcpar_lineno,(int)tmcpar_colno);
		}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 861 "TmcParParser.y"
    {
		(yyval.lsp_return_command_val)=create_return((int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 866 "TmcParParser.y"
    {
		(yyval.lsp_T_ctrl_cmd_break_val)=create_break((int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 871 "TmcParParser.y"
    {
		(yyval.lsp_T_ctrl_cmd_continue_val)=create_continue((int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 877 "TmcParParser.y"
    {
		(yyval.lsp_T_cmd_decl_gen_val)=create_declaration("global",(yyvsp[(2) - (2)].lsp_L_vardecl_val),(int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 886 "TmcParParser.y"
    {

		(yyval.lsp_T_ctrl_cmd_if_val) = create_if_statement((yyvsp[(1) - (1)].lsp_LT_if_blocks_val),(int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 892 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val)=(yyvsp[(1) - (1)].lsp_LT_if_blocks_val);
	}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 901 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = create_if_clause_list(create_if_clause((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 905 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(4) - (4)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 909 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(4) - (4)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 916 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = create_if_clause_list(create_if_clause((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 920 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(5) - (5)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(2) - (5)].lsp_expression_val),(yyvsp[(3) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 927 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = create_if_clause_list(create_if_clause((yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(2) - (3)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 931 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(4) - (4)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(1) - (4)].lsp_expression_val),(yyvsp[(2) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 938 "TmcParParser.y"
    {
	  (yyval.lsp_LT_if_blocks_val) = create_if_clause_list(create_if_clause(0,(yyvsp[(2) - (3)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 942 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = append_to_if_clause_list(
		create_if_clause_list(create_if_clause((yyvsp[(2) - (6)].lsp_expression_val),(yyvsp[(3) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)),
		create_if_clause(0,(yyvsp[(5) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)
		);
	}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 949 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(5) - (5)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(2) - (5)].lsp_expression_val),(yyvsp[(3) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 955 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = append_to_if_clause_list(
		create_if_clause_list(create_if_clause((yyvsp[(1) - (5)].lsp_expression_val),(yyvsp[(2) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)),
		create_if_clause(0,(yyvsp[(4) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)
		);
	}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 962 "TmcParParser.y"
    {
		(yyval.lsp_LT_if_blocks_val) = insert_head_to_if_clause_list((yyvsp[(4) - (4)].lsp_LT_if_blocks_val),create_if_clause((yyvsp[(1) - (4)].lsp_expression_val),(yyvsp[(2) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 968 "TmcParParser.y"
    {
				(yyval.lsp_T_ctrl_cmd_while_val)=create_while_command((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno);
			//	yyinsert_comma_in_input(END);
				}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 977 "TmcParParser.y"
    {
		(yyval.lsp_T_ctrl_cmd_switch_val) =create_switch_command((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(4) - (4)].lsp_LT_sw_cases_val),(int)tmcpar_lineno,(int)tmcpar_colno);
	}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 984 "TmcParParser.y"
    {
	 	(yyval.lsp_LT_sw_cases_val) = create_switch_cases_list(create_switch_case((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 988 "TmcParParser.y"
    {
	 	(yyval.lsp_LT_sw_cases_val) = append_to_switch_cases_list((yyvsp[(2) - (5)].lsp_LT_sw_cases_val),create_switch_case((yyvsp[(3) - (5)].lsp_expression_val),(yyvsp[(4) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 992 "TmcParParser.y"
    {
	 	(yyval.lsp_LT_sw_cases_val) = append_to_switch_cases_list(create_switch_cases_list(create_switch_case((yyvsp[(2) - (6)].lsp_expression_val),(yyvsp[(3) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)),
                 create_switch_case(0,(yyvsp[(5) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 997 "TmcParParser.y"
    {
	 	(yyval.lsp_LT_sw_cases_val) =append_to_switch_cases_list(
                    append_to_switch_cases_list((yyvsp[(2) - (7)].lsp_LT_sw_cases_val),create_switch_case((yyvsp[(3) - (7)].lsp_expression_val),(yyvsp[(4) - (7)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)),
                    create_switch_case(0,(yyvsp[(6) - (7)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno)
                    );
	}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1004 "TmcParParser.y"
    {
	 	(yyval.lsp_LT_sw_cases_val) = create_switch_cases_list(create_switch_case(0,(yyvsp[(2) - (3)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1011 "TmcParParser.y"
    {
		(yyval.lsp_LT_sw_cases_val) = create_switch_cases_list(create_switch_case((yyvsp[(1) - (3)].lsp_expression_val),(yyvsp[(2) - (3)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1015 "TmcParParser.y"
    {
		(yyval.lsp_LT_sw_cases_val) = append_to_switch_cases_list((yyvsp[(1) - (4)].lsp_LT_sw_cases_val),create_switch_case((yyvsp[(2) - (4)].lsp_expression_val),(yyvsp[(3) - (4)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno));
	}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1023 "TmcParParser.y"
    {
				(yyval.lsp_T_ctrl_cmd_for_val)=create_for_statement(/*convert_to_colon_expression*/((yyvsp[(2) - (6)].lsp_ident_val)),(yyvsp[(4) - (6)].lsp_expression_val),(yyvsp[(5) - (6)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno);
				}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1034 "TmcParParser.y"
    {
				(yyval.lsp_tree_try_command_val)=create_try_catch_statement((yyvsp[(2) - (5)].lsp_L_stmnt_gen_val),(yyvsp[(4) - (5)].lsp_L_stmnt_gen_val),(int)tmcpar_lineno,(int)tmcpar_colno);
				}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1038 "TmcParParser.y"
    {
				(yyval.lsp_tree_try_command_val)=create_try_catch_statement((yyvsp[(2) - (3)].lsp_L_stmnt_gen_val),0,(int)tmcpar_lineno,(int)tmcpar_colno);
				}
    break;


/* Line 1792 of yacc.c  */
#line 3068 "TmcParParser.tab.cpp"
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
#line 1068 "TmcParParser.y"



