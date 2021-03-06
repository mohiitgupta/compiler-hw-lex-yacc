/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AND = 258,
     OR = 259,
     EQUALS = 260,
     FOR = 261,
     IN = 262,
     SUM = 263,
     PRINT = 264,
     PRINTLN = 265,
     UNKNOWN = 266,
     IF = 267,
     ELSE = 268,
     WHILE = 269,
     INT = 270,
     BOOL = 271,
     STRING_TOKEN = 272,
     LESS_EQUALS = 273,
     GREAT_EQUALS = 274,
     NOT_EQUALS = 275,
     INPUT = 276,
     INTEGER = 277,
     ID = 278,
     STRING = 279,
     BOOLEAN = 280
   };
#endif
/* Tokens.  */
#define AND 258
#define OR 259
#define EQUALS 260
#define FOR 261
#define IN 262
#define SUM 263
#define PRINT 264
#define PRINTLN 265
#define UNKNOWN 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define INT 270
#define BOOL 271
#define STRING_TOKEN 272
#define LESS_EQUALS 273
#define GREAT_EQUALS 274
#define NOT_EQUALS 275
#define INPUT 276
#define INTEGER 277
#define ID 278
#define STRING 279
#define BOOLEAN 280




/* Copy the first part of user declarations.  */
#line 1 "hw7.y"

    #include <stdio.h>
    #include "hash.h"
    #include <stdlib.h>
    #include "util.h"
    #include "live_analysis_util.h"
    // #include "type_util.h"
    //#include <stdbool.h>
    int yylex(void);
    void yyerror(char *);
    int yydebug = 1;
    FILE *yyin;

    struct ast_node * mk_ast_number_node (int value);
    struct ast_node * mk_ast_node (int node_type, struct ast_node * left, struct ast_node * right);
    struct ast_node * mk_ast_symbol_reference_node (struct symbol_node * symbol);
    struct ast_node * mk_ast_assignment_node (struct ast_node * symbol, struct ast_node * value);
    void print_tree(struct ast_node * node);
    struct ast_node * traverse(struct ast_node * node);
    int add_value(struct ast_node * value_node);
    struct ast_node * mk_ast_for_sum_node (struct ast_node * symbol, int left_value, int right_value, struct ast_node * expression);
    struct ast_node * mk_ast_boolean_node (int value);
    struct ast_node * typecheck(struct ast_node * ast_tree);
    // int getOperatorResultNodeType(int node_type);

    int typeError = 0;




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 53 "hw7.y"
{
        int number;
        int boolean;
        struct ast_node * ast;
        struct symbol_node * symbol;
        char * string;
}
/* Line 193 of yacc.c.  */
#line 184 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 197 "y.tab.c"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   117

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNRULES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,    28,    35,    33,    32,    34,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    26,
      36,    31,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      25
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    15,    21,    27,    33,
      37,    41,    47,    51,    55,    59,    63,    65,    67,    69,
      71,    73,    77,    79,    83,    85,    89,    91,    95,    97,
     101,   103,   107,   111,   113,   117,   121,   125,   129,   131,
     135,   139,   141,   145,   147,   149,   151,   153,   155,   157,
     159,   161,   163,   165,   167,   169,   182,   186,   188,   190,
     192,   194,   196,   198
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    -1,    42,    43,    -1,    43,    -1,
      72,    44,    52,    26,    -1,    45,    27,    51,    28,    26,
      -1,    46,    27,    51,    28,    26,    -1,    21,    27,    49,
      28,    26,    -1,    29,    42,    30,    -1,    47,    52,    43,
      -1,    47,    52,    43,    13,    43,    -1,    48,    52,    43,
      -1,    15,    50,    26,    -1,    16,    50,    26,    -1,    17,
      50,    26,    -1,    31,    -1,     9,    -1,    10,    -1,    12,
      -1,    14,    -1,    49,    32,    72,    -1,    72,    -1,    50,
      32,    72,    -1,    72,    -1,    51,    32,    52,    -1,    52,
      -1,    52,    64,    53,    -1,    53,    -1,    53,    63,    54,
      -1,    54,    -1,    54,    61,    55,    -1,    54,    67,    55,
      -1,    55,    -1,    55,    62,    56,    -1,    55,    68,    56,
      -1,    55,    66,    56,    -1,    55,    65,    56,    -1,    56,
      -1,    56,    58,    57,    -1,    56,    59,    57,    -1,    57,
      -1,    57,    60,    69,    -1,    69,    -1,    33,    -1,    34,
      -1,    35,    -1,     5,    -1,    36,    -1,     3,    -1,     4,
      -1,    18,    -1,    19,    -1,    20,    -1,    37,    -1,     6,
      72,     7,    70,    22,    32,    22,    38,    71,    27,    52,
      28,    -1,    27,    52,    28,    -1,    22,    -1,    24,    -1,
      23,    -1,    25,    -1,    39,    -1,     8,    -1,    23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    74,    74,    78,    79,    81,    84,    85,    86,    87,
      88,    92,    93,    97,    98,    99,   103,   105,   107,   109,
     111,   114,   115,   119,   120,   124,   125,   129,   132,   135,
     138,   141,   143,   145,   148,   149,   150,   151,   152,   155,
     156,   157,   160,   161,   165,   167,   169,   171,   173,   175,
     177,   179,   181,   183,   185,   188,   191,   192,   193,   194,
     195,   200,   203,   206
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "OR", "EQUALS", "FOR", "IN",
  "SUM", "PRINT", "PRINTLN", "UNKNOWN", "IF", "ELSE", "WHILE", "INT",
  "BOOL", "STRING_TOKEN", "LESS_EQUALS", "GREAT_EQUALS", "NOT_EQUALS",
  "INPUT", "INTEGER", "ID", "STRING", "BOOLEAN", "';'", "'('", "')'",
  "'{'", "'}'", "'='", "','", "'+'", "'-'", "'*'", "'<'", "'>'", "']'",
  "'['", "$accept", "program", "statements", "statement", "eq_op",
  "print_op", "println_op", "if_op", "while_op", "inputlist", "idlist",
  "listexpr", "expr", "expr2", "expr3", "expr4", "expr5", "expr6",
  "plus_op", "minus_op", "multiply_op", "equals_op", "less_than_op",
  "and_op", "or_op", "less_equals_op", "great_equals_op", "not_equals_op",
  "great_than_op", "term", "bracket_op", "sum_op", "idexpr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    59,    40,    41,   123,
     125,    61,    44,    43,    45,    42,    60,    62,    93,    91
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    45,    46,    47,
      48,    49,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    54,    55,    55,    55,    55,    55,    56,
      56,    56,    57,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    69,    69,    69,    69,
      69,    70,    71,    72
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     4,     5,     5,     5,     3,
       3,     5,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,    12,     3,     1,     1,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    17,    18,    19,    20,     0,     0,     0,     0,    63,
       0,     0,     2,     4,     0,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,     1,     3,     0,     0,     0,
      57,    59,    58,    60,     0,     0,    28,    30,    33,    38,
      41,    43,     0,    16,     0,    13,     0,    14,    15,     0,
      22,     9,     0,    26,     0,     0,     0,    50,    10,     0,
      49,     0,    47,    53,     0,     0,    51,    52,    48,    54,
       0,     0,     0,     0,    44,    45,     0,     0,    46,     0,
      12,     0,    23,     0,     0,     0,     0,     0,     0,    56,
       0,    27,    29,    31,    32,    34,    37,    36,    35,    39,
      40,    42,     5,     8,    21,     6,    25,     7,    61,     0,
      11,     0,     0,     0,     0,    62,     0,     0,     0,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    11,    12,    13,    44,    14,    15,    16,    17,    49,
      19,    52,    53,    36,    37,    38,    39,    40,    76,    77,
      79,    64,    70,    61,    59,    71,    72,    65,    73,    41,
     109,   116,    18
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -50
static const yytype_int8 yypact[] =
{
      74,   -50,   -50,   -50,   -50,    10,    10,    10,    11,   -50,
      74,    52,    74,   -50,    44,    47,     0,     0,    26,   -15,
     -50,     9,    22,    10,    46,   -50,   -50,     0,     0,    10,
     -50,   -50,   -50,   -50,     0,    30,    69,    16,    75,   -21,
      57,   -50,    30,   -50,     0,   -50,    10,   -50,   -50,   -18,
     -50,   -50,    36,    76,    45,    71,     1,   -50,    66,     0,
     -50,     0,   -50,   -50,     0,     0,   -50,   -50,   -50,   -50,
       0,     0,     0,     0,   -50,   -50,     0,     0,   -50,     0,
     -50,     5,   -50,    56,    10,    61,     0,    70,    59,   -50,
      74,    69,    16,    75,    75,   -21,   -21,   -21,   -21,    57,
      57,   -50,   -50,   -50,   -50,   -50,    76,   -50,   -50,    77,
     -50,    68,    80,    72,   100,   -50,    82,     0,     4,   -50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -50,   -50,   103,    -5,   -50,   -50,   -50,   -50,   -50,   -50,
      43,    86,   -16,    58,    54,   -49,    34,   -11,   -50,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,    37,
     -50,   -50,    -3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      35,    42,    20,    20,    20,    57,    29,    26,    57,    57,
      83,    45,    74,    75,    84,    93,    94,    46,    56,    26,
      50,    62,    30,    31,    32,    33,    55,    34,    81,    89,
      58,   102,   119,     9,    57,    47,    63,    80,    23,     1,
       2,    46,     3,    82,     4,     5,     6,     7,    48,    21,
      22,     8,    25,     9,    46,     1,     2,    43,     3,    10,
       4,     5,     6,     7,    85,    99,   100,     8,    86,     9,
     106,    27,    60,    87,    28,    10,    51,    86,    88,    90,
      57,   104,   103,     1,     2,   110,     3,   105,     4,     5,
       6,     7,    78,    66,    67,     8,   107,     9,   108,   111,
     112,   118,   113,    10,    95,    96,    97,    98,   115,   117,
     114,    68,    69,    24,    54,    92,   101,    91
};

static const yytype_uint8 yycheck[] =
{
      16,    17,     5,     6,     7,     4,     6,    12,     4,     4,
      28,    26,    33,    34,    32,    64,    65,    32,    34,    24,
      23,     5,    22,    23,    24,    25,    29,    27,    44,    28,
      35,    26,    28,    23,     4,    26,    20,    42,    27,     9,
      10,    32,    12,    46,    14,    15,    16,    17,    26,     6,
       7,    21,     0,    23,    32,     9,    10,    31,    12,    29,
      14,    15,    16,    17,    28,    76,    77,    21,    32,    23,
      86,    27,     3,    28,    27,    29,    30,    32,     7,    13,
       4,    84,    26,     9,    10,    90,    12,    26,    14,    15,
      16,    17,    35,    18,    19,    21,    26,    23,    39,    22,
      32,   117,    22,    29,    70,    71,    72,    73,     8,    27,
      38,    36,    37,    10,    28,    61,    79,    59
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    12,    14,    15,    16,    17,    21,    23,
      29,    41,    42,    43,    45,    46,    47,    48,    72,    50,
      72,    50,    50,    27,    42,     0,    43,    27,    27,     6,
      22,    23,    24,    25,    27,    52,    53,    54,    55,    56,
      57,    69,    52,    31,    44,    26,    32,    26,    26,    49,
      72,    30,    51,    52,    51,    72,    52,     4,    43,    64,
       3,    63,     5,    20,    61,    67,    18,    19,    36,    37,
      62,    65,    66,    68,    33,    34,    58,    59,    35,    60,
      43,    52,    72,    28,    32,    28,    32,    28,     7,    28,
      13,    53,    54,    55,    55,    56,    56,    56,    56,    57,
      57,    69,    26,    26,    72,    26,    52,    26,    39,    70,
      43,    22,    32,    22,    38,     8,    71,    27,    52,    28
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
#line 74 "hw7.y"
    { print_tree((yyvsp[(1) - (1)].ast)); }
    break;

  case 3:
#line 78 "hw7.y"
    { (yyval.ast) = mk_ast_node('S',(yyvsp[(1) - (2)].ast), (yyvsp[(2) - (2)].ast));}
    break;

  case 4:
#line 79 "hw7.y"
    { /*printf("");*/(yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 5:
#line 81 "hw7.y"
    {(yyval.ast)= mk_ast_assignment_node((yyvsp[(1) - (4)].ast), (yyvsp[(3) - (4)].ast));
        (yyval.ast)->line_no=(yyvsp[(2) - (4)].ast)->line_no;
         /*printf("line number for equals is %d\n", $$->line_no);*/}
    break;

  case 6:
#line 84 "hw7.y"
    {/*printf("");*/(yyval.ast) = mk_ast_node('p', (yyvsp[(3) - (5)].ast), NULL);(yyval.ast)->line_no=(yyvsp[(1) - (5)].ast)->line_no; }
    break;

  case 7:
#line 85 "hw7.y"
    {(yyval.ast) = mk_ast_node('P', (yyvsp[(3) - (5)].ast), NULL);(yyval.ast)->line_no=(yyvsp[(1) - (5)].ast)->line_no; }
    break;

  case 8:
#line 86 "hw7.y"
    {(yyval.ast) = mk_ast_node('Q', (yyvsp[(3) - (5)].ast), NULL); }
    break;

  case 9:
#line 87 "hw7.y"
    {/*printf("");*/(yyval.ast) = mk_ast_node('C', (yyvsp[(2) - (3)].ast), NULL);}
    break;

  case 10:
#line 88 "hw7.y"
    {/*printf("");*/(yyval.ast) = mk_ast_if_node((yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].ast), NULL);
        (yyval.ast)->line_no=(yyvsp[(1) - (3)].ast)->line_no;
        // printf("line no of if is %d", $$->line_no);
        /*$$->right=NULL;*/}
    break;

  case 11:
#line 92 "hw7.y"
    {(yyval.ast) = mk_ast_if_node((yyvsp[(2) - (5)].ast), (yyvsp[(3) - (5)].ast), (yyvsp[(5) - (5)].ast));(yyval.ast)->line_no=(yyvsp[(1) - (5)].ast)->line_no;}
    break;

  case 12:
#line 93 "hw7.y"
    {(yyval.ast) = mk_ast_while_node((yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast)->line_no=(yyvsp[(1) - (3)].ast)->line_no;
            // printf("line no of while is %d", $$->line_no);
        }
    break;

  case 13:
#line 97 "hw7.y"
    {(yyval.ast) = mk_ast_node('i', (yyvsp[(2) - (3)].ast), NULL);}
    break;

  case 14:
#line 98 "hw7.y"
    {(yyval.ast) = mk_ast_node('b', (yyvsp[(2) - (3)].ast), NULL);}
    break;

  case 15:
#line 99 "hw7.y"
    {(yyval.ast) = mk_ast_node('c', (yyvsp[(2) - (3)].ast), NULL);}
    break;

  case 16:
#line 103 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 17:
#line 105 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 18:
#line 107 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 19:
#line 109 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 20:
#line 111 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 21:
#line 114 "hw7.y"
    {(yyval.ast) = mk_ast_node('q', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));}
    break;

  case 22:
#line 115 "hw7.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 23:
#line 119 "hw7.y"
    {(yyval.ast) = mk_ast_node('l', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));}
    break;

  case 24:
#line 120 "hw7.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);/*printf("line is %d", $$->line_no);*/}
    break;

  case 25:
#line 124 "hw7.y"
    { (yyval.ast) = mk_ast_node ('L', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));}
    break;

  case 26:
#line 125 "hw7.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 27:
#line 129 "hw7.y"
    {(yyval.ast) = mk_ast_node('O', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); 
    (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no; 
}
    break;

  case 28:
#line 132 "hw7.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 29:
#line 135 "hw7.y"
    {(yyval.ast) = mk_ast_node('a', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); 
    (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no; 
}
    break;

  case 30:
#line 138 "hw7.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 31:
#line 141 "hw7.y"
    {(yyval.ast) = mk_ast_node('E', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); 
    (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no;}
    break;

  case 32:
#line 143 "hw7.y"
    {(yyval.ast) = mk_ast_node('w', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); 
    (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no;}
    break;

  case 33:
#line 145 "hw7.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 34:
#line 148 "hw7.y"
    {(yyval.ast) = mk_ast_node('<', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no;}
    break;

  case 35:
#line 149 "hw7.y"
    {(yyval.ast) = mk_ast_node('x', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no;}
    break;

  case 36:
#line 150 "hw7.y"
    {(yyval.ast) = mk_ast_node('y', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no;}
    break;

  case 37:
#line 151 "hw7.y"
    {(yyval.ast) = mk_ast_node('z', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no;}
    break;

  case 38:
#line 152 "hw7.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 39:
#line 155 "hw7.y"
    {(yyval.ast) = mk_ast_node('+', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no;}
    break;

  case 40:
#line 156 "hw7.y"
    {(yyval.ast) = mk_ast_node('-', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no;}
    break;

  case 41:
#line 157 "hw7.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 42:
#line 160 "hw7.y"
    {(yyval.ast) = mk_ast_node('*', (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); (yyval.ast)->line_no=(yyvsp[(2) - (3)].ast)->line_no;}
    break;

  case 43:
#line 161 "hw7.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 44:
#line 165 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 45:
#line 167 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 46:
#line 169 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 47:
#line 171 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 48:
#line 173 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 49:
#line 175 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 50:
#line 177 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 51:
#line 179 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 52:
#line 181 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 53:
#line 183 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 54:
#line 185 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 55:
#line 188 "hw7.y"
    {/*printf("");*/(yyval.ast) = mk_ast_for_sum_node((yyvsp[(2) - (12)].ast), (yyvsp[(5) - (12)].number), (yyvsp[(7) - (12)].number), (yyvsp[(11) - (12)].ast));
                                (yyval.ast)->line_no=(yyvsp[(4) - (12)].ast)->line_no;
                                (yyval.ast)->line_no_2=(yyvsp[(9) - (12)].ast)->line_no;}
    break;

  case 56:
#line 191 "hw7.y"
    {(yyval.ast) = (yyvsp[(2) - (3)].ast);/*printf("line no of id is %d", $$->line_no);*/}
    break;

  case 57:
#line 192 "hw7.y"
    {(yyval.ast) = mk_ast_number_node((yyvsp[(1) - (1)].number));}
    break;

  case 58:
#line 193 "hw7.y"
    {(yyval.ast) = mk_ast_string_node((yyvsp[(1) - (1)].string));}
    break;

  case 59:
#line 194 "hw7.y"
    {(yyval.ast) = mk_ast_symbol_reference_node((yyvsp[(1) - (1)].symbol));/*$$->line_no=yylineno;*//*printf("line no of id is %d", $$->line_no);*/}
    break;

  case 60:
#line 195 "hw7.y"
    {(yyval.ast) = mk_ast_boolean_node((yyvsp[(1) - (1)].boolean));}
    break;

  case 61:
#line 200 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 62:
#line 203 "hw7.y"
    {(yyval.ast) = mk_ast_node(0, NULL, NULL);}
    break;

  case 63:
#line 206 "hw7.y"
    {(yyval.ast) = mk_ast_symbol_reference_node((yyvsp[(1) - (1)].symbol));
        (yyval.ast)->line_no=yylineno;
        /*printf("line no of id is %d", $$->line_no);*/}
    break;


/* Line 1267 of yacc.c.  */
#line 1823 "y.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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


#line 210 "hw7.y"

void yyerror(char *s) {
    fprintf(stderr, "Syntax Error\n");
}

int main(int argc, char *argv[]) {
    yyin = fopen(argv[1], "r");
    yyparse();
    fclose(yyin);
    return 0;
}

void print_tree(struct ast_node * node) {
    //printf("length is %d", length);
    //struct symbol_node * sym_node = lookup("a");
    //sym_node->value = 4;
    /*for (int i=0; i < length; i++) {
        printf("%s", symbols[i]->name);
        printf("%d", symbols[i]->value);
        printf("%s", symbols[i]->initialize);
        printf("%s", symbols[i]->string_val);
        printf("\n");
    }*/
    // block_level = 1;
    present_scope = (struct scope_node *)malloc(sizeof(struct scope_node));
    present_scope->parent = NULL;
    // present_scope->scope_level = 1;
    present_scope->len_child_scopes = 0;
    present_scope->len_symbol_table = 0;
    // printf("length child scopes present scope is %d\n", present_scope->len_child_scopes);
    typecheck(node);
    if (typeError == 0) {
        present_scope->current_child_scope = 0;
        // printf("traverse begin\n");
        traverse(node);
        // find_def_use(node);
    }
    

    // for (int i=0; i < length; i++) {
    //     printf("%s ", symbols[i]->name);
    //     int * number = ((int *)symbols[i]->value);
    //     printf("%d ", *number);
    //     printf("%s ", symbols[i]->type);
    //     //printf("%s ", symbols[i]->string_val);
    //     printf("\n");
    // }
    //fprintf(stderr, "tree test");
}

void printErrorMessage(int line) {
    typeError = 1;
    printf("Type violation in %d\n", line);
}

void actIfViolation(struct ast_node * ast_tree, struct ast_node * result, int typeViolationCheckLeft, int typeViolationCheckRight) {
    if (typeViolationCheckLeft == -1 || typeViolationCheckRight == -1) {
        result->node_type = 'U';
    } else if (typeViolationCheckLeft == 1 || typeViolationCheckRight == 1) {
        result->node_type = 'U';
        printErrorMessage(ast_tree->line_no);
        // printf("Type violation error in line %d\n", ast_tree->line_no);
    }
}



char * getOperandType(int node_type) {
    if (node_type == '+' || node_type == '-' || node_type == '*' || node_type == '<' || node_type == 'E'
        || node_type == 'w' || node_type == 'x' || node_type == 'y' || node_type == 'z')
        return "number";
    //printf("undefined node type\n");
    return NULL;
}

void checkSymbolViolation(struct ast_node * dummy, struct scope_node *scope) {
    if (dummy->node_type == 's') {
        // struct ast_symbol_reference_node * node = (struct ast_symbol_reference_node *) dummy;
        struct ast_node * node = dummy;
        struct symbol_node * sym_node = lookup_variable_present_scope(present_scope, node->symbol->name);
        if (sym_node == NULL) {
            printErrorMessage(node->line_no);
            // printf("type violation error in line %d\n", node->line_no);
        }
    }
}


struct ast_node * typecheck(struct ast_node * ast_tree) {
    // printf("start ast tree %p\n", ast_tree);
    
    if (ast_tree == NULL) {
        // printf("null\n");
        return NULL;
    }
    // printf("yylineno is %d\n", yylineno);
    // printf("print node type %c line no %d\n", ast_tree->node_type, ast_tree->line_no);
    switch (ast_tree->node_type)
    {
        case 'Q':
        {
            struct ast_node * left = ast_tree->left;
            struct symbol_node * sym_node;
            if (left->node_type != 's') {
                typecheck(ast_tree->left);
            } else {
                int typeViolation = typeViolationCheck(present_scope, left, "", 's');
                if (typeViolation == -1) {
                    printErrorMessage(ast_tree->line_no);
                    // printf("Type violation error in line %d\n", ast_tree->line_no);
                }
                sym_node = lookup_variable_present_scope(present_scope, left->symbol->name);
            }
            break;
        }
        case 'q':
        {
            // printf("inside input list\n");
            struct ast_node * left = ast_tree->left;
            struct symbol_node * sym_node;
            if (left->node_type != 's') {
                typecheck(ast_tree->left);
            } else {
                int typeViolation = typeViolationCheck(present_scope, ast_tree, "", 's');
                if (typeViolation == -1) {
                    printErrorMessage(ast_tree->line_no);
                    // printf("Type violation error in line %d\n", ast_tree->line_no);
                }
                sym_node = lookup_variable_present_scope(present_scope, left->symbol->name);
            }
            // printf("%p", ast_tree->right);
            typecheck(ast_tree->right);
            sym_node = lookup_variable_present_scope(present_scope, ast_tree->right->symbol->name);
            break;
        }
        case 'l':
        {
            // printf("inside l block\n");
            struct ast_string_node * result = (struct ast_string_node *) malloc (sizeof (struct ast_string_node));
            result->node_type = 'n';
            struct ast_node * left = ast_tree->left;
            struct ast_node * dummy;
            // printf("left node type %c\n", left->node_type);
            if (left->node_type != 's') {
                dummy = typecheck(ast_tree->left);
            } else {
                dummy = left;
            }
            char * value1 = get_symbol_name(dummy);
            //printf("value 1 is %s\n", value1);
            // struct ast_node * dummy2 = typecheck(ast_tree->right);
            struct ast_node * right = ast_tree->right;
            // printf("right node type %c\n", right->node_type);
            struct ast_node * dummy2;
            if (right->node_type != 's') {
                dummy2 = typecheck(ast_tree->right);
            } else {
                dummy2 = right;
            }
            char * value2 = get_symbol_name(dummy2);
            // printf("%s\n", value2);
            //printf("value 2 is %s\n", value2);
            result->value = malloc(strlen(value1)+strlen(value2)+1);
            strcpy(result->value, value1);
            strcat(result->value, " ");
            strcat(result->value, value2);
            // printf("value is %s\n", result->value);
            return (struct ast_node *) result;
            break;
        }
        case 'i':
        case 'b':
        case 'c':
        {
            char * type;
            if (ast_tree->node_type == 'i') type = "number";
            else if (ast_tree->node_type == 'b') type = "boolean";
            else type = "string";
            // struct ast_node * dummy = typecheck(ast_tree->left);
            struct ast_node * left = ast_tree->left;
            struct ast_node * dummy;
            if (left->node_type != 's') {
                dummy = typecheck(ast_tree->left);
            } else {
                dummy = left;
            }
            char * value1 = get_symbol_name(dummy);
            char * variable = strtok(value1, " ");
            while (variable != NULL) {
                // printf("%s ", variable);
                int check = add_variable_to_present_scope(present_scope, variable, type);
                if (check == 0) {

                    printErrorMessage(ast_tree->line_no);
                    // printf("redeclaration error in line %d\n", ast_tree->line_no);
                } else {
                    setDeclareValue(present_scope, variable); 
                }
                variable = strtok(NULL, " ");
            }
            // printf("present scope length %d\n", present_scope->len_symbol_table);
            break;
        }
        case 'C':
        {
            // printf("inside compound statement\n");
            present_scope = create_new_scope(present_scope);
            typecheck(ast_tree->left);
            present_scope = present_scope->parent;
            break;

        }
        case '+':
        case '-':
        case '*':
        case '<':
        case 'E':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        {
            struct ast_node * result = (struct ast_node *) malloc (sizeof (struct ast_node));
            result->node_type = getOperatorResultNodeType(ast_tree->node_type);
            char * operand_type = getOperandType(ast_tree->node_type);

            struct ast_node * dummy = typecheck(ast_tree->left);
            // printf("before type check\n");
            int typeViolationCheckLeft = typeViolationCheck(present_scope, dummy, operand_type, 'N');
            // if (dummy->node_type == 's' && typeViolationCheckLeft == -1) {
            //     printf("type violation error in line %d\n", dummy->line_no);
            // }
            //result->value = add_value(dummy);
            struct ast_node * dummy2 = typecheck(ast_tree->right);
            int typeViolationCheckRight = typeViolationCheck(present_scope, dummy2, operand_type, 'N');
            // if (dummy2->node_type == 's' && typeViolationCheckLeft == -1) {
            //     printf("type violation error in line %d\n", dummy->line_no);
            // }
            actIfViolation( ast_tree, (struct ast_node *) result, typeViolationCheckLeft, typeViolationCheckRight);
            // printf("after type check\n");
            return (struct ast_node *) result;
            break;
        }
        case 'F':
        {
            struct ast_for_sum_node * for_node = (struct ast_for_sum_node *) ast_tree;
            struct ast_node * result = (struct ast_node *) malloc (sizeof (struct ast_node));
            result->node_type = 'N';
            present_scope = create_new_scope(present_scope);


            struct ast_node * symbol_node = for_node->symbol;
            int range1 = for_node->left_value;
            int range2 = for_node->right_value;
            char * variable = get_symbol_name(symbol_node);
            add_variable_to_present_scope(present_scope, variable, "number");

            // printf("ranges are %d %d\n", range1, range2);
            if (range1 > range2) {

                printErrorMessage(for_node->line_no);
                result->node_type = 'U';
                // printf("Type violation error in line %d\n", for_node->line_no);
            }
            struct ast_node * expression_node = typecheck(for_node->expression);
            int typeViolation = typeViolationCheck(present_scope, expression_node, "number", 'N');
            if (typeViolation != 0) {
                result->node_type = 'U';
                if (typeViolation == 1) {
                    printErrorMessage(for_node->line_no_2);
                    // printf("Type violation error in line %d\n", for_node->line_no);
                }

            }
            
            // struct ast_while_node * while_node = (struct ast_while_node *) ast_tree;
            // struct ast_number_node * condition = (struct ast_number_node *) traverse(while_node->condition);
            // while(condition->value != 0) {
            //     traverse(while_node->while_branch);
            //     condition = (struct ast_number_node *) traverse(while_node->condition);
            // }
            //printf("while block came");
            present_scope = present_scope->parent;
            return (struct ast_node *) result;
            break;
        }
        case 'a':
        {
            struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
            result->node_type = 'B';
            struct ast_node * dummy = typecheck(ast_tree->left);
            int typeViolationCheckLeft = typeViolationCheck(present_scope, dummy, "boolean", 'B');
            //result->value = add_value(dummy);
            struct ast_node * dummy2 = typecheck(ast_tree->right);
            int typeViolationCheckRight = typeViolationCheck(present_scope, dummy2, "boolean", 'B');
            actIfViolation( ast_tree, (struct ast_node *) result, typeViolationCheckLeft, typeViolationCheckRight);
            return (struct ast_node *) result;
            break;
        }
        case 's':
        {
            int typeViolation = typeViolationCheck(present_scope, ast_tree, "", 's');
            if (typeViolation == -1) {
                printErrorMessage(ast_tree->line_no);
                // printf("Type violation error in line %d\n", ast_tree->line_no);
            }
            break;
        }
        case 'O':
        {

            struct ast_node * result = (struct ast_node *) malloc (sizeof (struct ast_node));
            struct ast_node * dummy = typecheck(ast_tree->left);
            int typeViolationCheckLeft = typeViolationCheck(present_scope, dummy, "boolean", 'B');
            int typeViolationCheckRight = 0;
            if (typeViolationCheckLeft == 0) {
                struct ast_node * dummy2 = typecheck(ast_tree->right);
                typeViolationCheckRight = typeViolationCheck(present_scope, dummy2, "boolean", 'B');
                actIfViolation( ast_tree, (struct ast_node *) result, typeViolationCheckLeft, typeViolationCheckRight);
                if (result->node_type != 'U') {
                    result->node_type = 'B';
                }
            } else if (typeViolationCheckLeft == 1) {
                typeViolationCheckLeft = typeViolationCheck(present_scope, dummy, "string", 'n');
                struct ast_node * dummy2 = typecheck(ast_tree->right);
                typeViolationCheckRight = typeViolationCheck(present_scope, dummy2, "string", 'n');
                actIfViolation( ast_tree, (struct ast_node *) result, typeViolationCheckLeft, typeViolationCheckRight);
                if (result->node_type != 'U') {
                    result->node_type = 'n';
                }
            } else {
                struct ast_node * dummy2 = typecheck(ast_tree->right);
                result->node_type = 'U';
            }
            return (struct ast_node *) result;
            break;        
        }

        case 'A':
        {
            // printf("inside assignment\n");
            struct ast_assignment_node * node = (struct ast_assignment_node *) ast_tree;
            //struct symbol_node * sym_node = find(node->symbol->name);
            // struct ast_symbol_reference_node * sym_ref_node = (struct ast_symbol_reference_node *) typecheck(node->symbol);
            struct ast_node * sym_ref_node = typecheck(node->symbol);
            struct symbol_node * sym_node = lookup_variable_present_scope(present_scope, sym_ref_node->symbol->name);
            // if (value_node->node_type == 's') {
            //     struct ast_symbol_reference_node * dum = (struct ast_symbol_reference_node *) value_node;
            //     printf("inside assignment type of right hand side is %d\n", dum->line_no);
            // }
            // printf("inside assignment type of right hand side is %d\n", value_node->line_no);
            // if (sym_node == NULL) {
            //     printf("type violation error in line %d\n", sym_ref_node->line_no);
            // } else {

            // }
            struct ast_node * value_node = typecheck(node->value);
            
            if (value_node->node_type == 'U') 
            {
            } 
            else if ( sym_node != NULL && (   ((value_node->node_type == 'N') && (strcmp(sym_node->type, "number")==0))
                || ((value_node->node_type == 'n') && (strcmp(sym_node->type, "string")==0))
                || ((value_node->node_type == 'B') && (strcmp(sym_node->type, "boolean")==0))
                    )
                )
            {

            } 
            else if (sym_node != NULL && value_node->node_type == 's')
            {
                int typeViolationCheckLeft = typeViolationCheck(present_scope, value_node, sym_node->type, 0);
                if (typeViolationCheckLeft == 1) {
                    // sym_node->type = "undefined";
                    printErrorMessage(ast_tree->line_no);
                    // printf("type violation error in line %d\n", ast_tree->line_no);
                } 
                // else if (typeViolationCheckLeft == -1) {
                //     printErrorMessage(value_node->line_no);
                //     // printf("type violation error in line %d\n", value_node->line_no);
                //     // sym_node->type = "undefined";
                // }
                
            }
            else if (sym_node != NULL && value_node->node_type != 'U') {
                printErrorMessage(ast_tree->line_no);
                // printf("type violation error in line %d\n", ast_tree->line_no);
            }
            //printf("end of assignment\n");
            return ast_tree;
            break;
        }
           

        case 'n':
            return ast_tree;
            break;
        case 'N':
            return ast_tree;
            break;
        case 'S':
            typecheck(ast_tree->left);
            typecheck(ast_tree->right);
            break;
        case 'P':
        {
            struct ast_node * value_node = typecheck(ast_tree->left);
            // checkSymbolViolation(value_node, present_scope);
            break;
        }
            
        case 'p':
        {
            // printf("inside p block\n");
            struct ast_node * value_node = typecheck(ast_tree->left);
            // checkSymbolViolation(value_node, present_scope);
            break;
        }
            
        case 'L':
        {  
            // printf("inside L block\n");
            struct ast_string_node * result = (struct ast_string_node *) malloc (sizeof (struct ast_string_node));
            result->node_type = 'n';
            struct ast_node * dummy = typecheck(ast_tree->left);
            struct ast_node * dummy2 = typecheck(ast_tree->right);
            break;
        }
        case 'I':
        {
            struct ast_node * if_node = ast_tree;
            struct ast_node * condition = typecheck(if_node->condition);
            int typeViolation = typeViolationCheck(present_scope, condition, "boolean", 'B');
            // printf("before typeViolation check in if\n");
            if (typeViolation == 1) {
                printErrorMessage(ast_tree->line_no);
                // printf("type violation error in line %d\n", ast_tree->line_no);
            } else {
               
            }
            // printf("after typeViolation in if\n");
            typecheck(if_node->left);
            // // printf("after if branch in if\n");
            // if (if_node->right != NULL /*|| if_node->right != 0x2*/) {
            //     // printf("inside else\n");
                typecheck(if_node->right);
            // }
            
            // printf("after else branch in if\n");
            //printf("if block came");
            break;
        }
        case 'W':
        {
            // printf("line no of while %d\n", ast_tree->line_no);
            // struct ast_while_node * while_node = (struct ast_while_node *) ast_tree;
            struct ast_node * while_node = ast_tree;
            struct ast_node * condition = typecheck(while_node->condition);
            int typeViolation = typeViolationCheck(present_scope, condition, "boolean", 'B');
            if (typeViolation == 1) {
                printErrorMessage(ast_tree->line_no);
                // printf("type violation error in line %d\n", ast_tree->line_no);
            } else {
               
            }
            // while(condition->value != 0) {
            //     traverse(while_node->while_branch);
            //     condition = (struct ast_number_node *) traverse(while_node->condition);
            // }
            typecheck(while_node->left);
            //printf("while block came");
            break;
        }

            
    }
    return ast_tree;
}


