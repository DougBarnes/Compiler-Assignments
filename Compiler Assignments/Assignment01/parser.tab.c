/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

// // // // // // // // // // // // // // // // // // // // // // // 
// CS445 - Parser for c- files built upon from calc given to
// 	   class by Robert Heckendorn
//
// Doug Barnes
// Jan 30, 2021    
#include "ourGetopt.h"   //read in a command line
#include "scanType.h"    // TokenData Type
#include "treeNode.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
#include "yyerror.h"
#include "codegen.h"


double vars[26];    
bool printOffsetFlag = false;
extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count
extern int numWarning;
extern int yydebug;
extern int goffset;
extern SymbolTable symbolTable;
extern TreeNode *addSibling(TreeNode *t, TreeNode *s);
extern TreeNode *newDeclNode(DeclKind kind);
extern TreeNode *newStmtNode(StmtKind kind);
extern TreeNode *newExpNode(ExpKind kind);
extern void addIOLibrary(TreeNode *tree);
extern void printTree(TreeNode *tree);
extern void codegen(char* outFile, TreeNode *tree);
//extern void printTreeTypes(Semantic *tree);

TreeNode *syntaxTree;
//Semantic *syntaxTree;

#define YYERROR_VERBOSE
/*void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line, msg);
    numErrors++;
}*/


#line 116 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    NUMCONST = 259,
    OPERATOR = 260,
    EQ = 261,
    ADDASS = 262,
    SUBASS = 263,
    MULTASS = 264,
    DIVASS = 265,
    STRINGCONST = 266,
    CHARCONST = 267,
    DEC = 268,
    MIN = 269,
    MAX = 270,
    GEQ = 271,
    LEQ = 272,
    INC = 273,
    NEQ = 274,
    BOOLCONST = 275,
    STATIC = 276,
    INT = 277,
    BOOL = 278,
    CHAR = 279,
    IF = 280,
    THEN = 281,
    ELSE = 282,
    WHILE = 283,
    FOR = 284,
    DO = 285,
    NOT = 286,
    BY = 287,
    RETURN = 288,
    BREAK = 289,
    OR = 290,
    AND = 291,
    TO = 292,
    EQASS = 293,
    ADD = 294,
    SUB = 295,
    STAR = 296,
    DIV = 297,
    MOD = 298,
    LESS = 299,
    GREATER = 300,
    RAND = 301,
    OPENCURLY = 302,
    CLOSEDCURLY = 303,
    OPENBRACKET = 304,
    CLOSEDBRACKET = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 53 "parser.y" /* yacc.c:355  */
 
    ExpType expType;            // for passing types.  typespec to pass up a type in decl like int or bool
    DeclKind declKind;
    TokenData *tokenData;    // for terminals.  token data comes from yylex() in the $ variables
    TreeNode *tree;          // for nonterminals.   these tree nodes as you build the tree

#line 214 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 231 "parser.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1092

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  286

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      56,    57,     2,     2,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    51,
       2,    58,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    66,    66,    69,    70,    73,    74,    75,    79,    98,
      99,   102,   125,   144,   147,   148,   149,   150,   153,   154,
     156,   157,   160,   165,   172,   173,   176,   177,   178,   182,
     191,   198,   199,   200,   201,   204,   205,   208,   209,   210,
     211,   214,   234,   235,   236,   237,   240,   244,   250,   254,
     255,   258,   266,   273,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   297,   303,   309,   316,   326,
     327,   328,   331,   332,   333,   336,   343,   344,   347,   351,
     372,   377,   383,   384,   385,   388,   391,   396,   399,   404,
     409,   414,   419,   424,   429,   433,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   452,
     457,   458,   461,   466,   467,   470,   474,   475,   478,   483,
     488,   493,   498,   503,   508,   509,   510,   511,   512,   513,
     514,   518,   523,   528,   532,   537,   542,   543,   544,   548,
     553,   558,   563,   564,   565,   566,   580,   581,   582,   585,
     589,   593,   598,   599,   602,   608,   620,   621,   622,   623,
     626,   630,   633,   634,   637,   638,   639,   642,   648,   654,
     663
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "NUMCONST", "OPERATOR", "EQ",
  "ADDASS", "SUBASS", "MULTASS", "DIVASS", "STRINGCONST", "CHARCONST",
  "DEC", "MIN", "MAX", "GEQ", "LEQ", "INC", "NEQ", "BOOLCONST", "STATIC",
  "INT", "BOOL", "CHAR", "IF", "THEN", "ELSE", "WHILE", "FOR", "DO", "NOT",
  "BY", "RETURN", "BREAK", "OR", "AND", "TO", "EQASS", "ADD", "SUB",
  "STAR", "DIV", "MOD", "LESS", "GREATER", "RAND", "OPENCURLY",
  "CLOSEDCURLY", "OPENBRACKET", "CLOSEDBRACKET", "';'", "','", "':'",
  "'['", "']'", "'('", "')'", "'='", "$accept", "program", "declList",
  "decl", "varDecl", "scopedVarDecl", "varDeclList", "varDeclInit",
  "varDeclId", "typeSpec", "funDecl", "parms", "parmList", "parmTypeList",
  "parmIdList", "parmId", "stmt", "matched", "unmatched", "expStmt",
  "compoundStmt", "localDecls", "stmtList", "iterRange", "returnStmt",
  "breakStmt", "exp", "simpleExp", "andExp", "unaryRelExp", "relExp",
  "minmaxExp", "sumExp", "mulExp", "unaryExp", "unaryop", "factor",
  "mutable", "immutable", "call", "args", "argList", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,    59,    44,    58,    91,    93,    40,    41,    61
};
# endif

#define YYPACT_NINF -201

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-201)))

#define YYTABLE_NINF -164

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     122,   240,    -5,  -201,  -201,  -201,    33,   281,  -201,  -201,
     152,  -201,   110,    61,   -29,  -201,   -16,     4,  -201,  -201,
     174,    41,    90,   445,  -201,    92,   120,  -201,   168,   478,
       5,   181,   113,   127,  -201,  -201,    35,  -201,   129,    49,
    -201,  -201,  -201,  -201,   491,  -201,  -201,  -201,   509,   166,
     179,  -201,  -201,   452,   150,    88,  -201,   163,  -201,  -201,
    -201,  -201,  -201,   161,  -201,   110,  -201,   129,   166,   171,
     193,   172,  -201,   309,   175,     5,   188,  -201,   532,   116,
     129,  -201,  1036,   213,   166,    22,   550,   563,   176,   820,
     820,   838,   851,   869,   892,   910,   923,   941,   964,   982,
     995,   129,  -201,  -201,  -201,   236,   192,   130,   581,   604,
     199,   432,   243,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,  -201,   244,  -201,  -201,   350,  1036,   248,  -201,   249,
     255,   299,   532,   532,   532,  -201,  -201,   532,  -201,   622,
     635,   653,   676,  -201,  -201,   694,   129,   179,   129,  -201,
     129,   222,   150,   150,   129,   222,   129,   222,   129,   222,
     129,   222,   129,   222,   129,    88,   129,    88,   129,  -201,
     129,  -201,   129,  -201,  -201,   171,  -201,  -201,   -15,    58,
     -14,    83,  -201,   -20,  1024,  -201,   260,  -201,   227,  -201,
     130,  -201,  -201,  -201,   707,  -201,  -201,  -201,  -201,  -201,
    1036,  -201,  1036,  -201,  1036,  -201,  1036,  -201,  1036,  -201,
     350,   391,   350,   350,   350,   725,   316,  -201,  -201,   211,
     136,  -201,   211,   268,  1036,  -201,  -201,   291,   748,   766,
     217,  -201,  -201,   295,  -201,  -201,  -201,  -201,   -12,   293,
     250,   296,   202,   211,   214,  -201,  -201,   350,    -2,    68,
     -13,   119,   -19,   350,   324,   350,   779,   391,  -201,   225,
    -201,  -201,  -201,   391,   391,   391,   391,   725,  -201,  -201,
    -201,  -201,  -201,   129,    79,  -201,  -201,   300,   301,   302,
     797,   391,   391,   391,   129,   166
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    26,    27,    28,     0,     0,     4,     5,
       0,     6,    17,    22,     0,    15,    18,     0,     1,     3,
      31,    22,     0,     0,    25,     0,     0,     9,     0,     0,
      33,     0,     0,    35,    38,    10,     0,     8,     0,   154,
     167,   169,   168,   170,     0,   149,   150,   151,     0,    20,
     110,   113,   116,   124,   133,   136,   142,     0,   147,   153,
     152,   157,   158,     0,    24,    16,    14,    21,    19,    45,
      46,    41,    43,     0,     0,    32,     0,   161,     0,     0,
     117,   115,   159,     0,    96,   153,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   148,   146,    23,    48,     0,     0,    34,     0,     0,
       0,     0,     0,    77,    73,    30,    49,    50,    56,    57,
      54,    55,     0,    39,    37,     0,     0,     0,   165,     0,
     162,     0,     0,     0,     0,   108,   107,     0,   156,     0,
       0,     0,     0,    95,    94,     0,   111,   109,   114,   112,
     129,   122,   132,   131,   128,   121,   125,   118,   130,   123,
     126,   119,   127,   120,   137,   134,   138,   135,   143,   139,
     144,   140,   145,   141,    47,    44,    42,    74,    58,     0,
      62,     0,    64,     0,     0,    85,     0,    88,     0,    72,
       0,    29,   155,   160,     0,    98,    99,   100,   101,    97,
     103,    90,   104,    91,   105,    92,   106,    93,   102,    89,
       0,     0,     0,     0,     0,     0,     0,    87,    86,     0,
       0,    76,     0,     0,   166,   164,    69,    49,     0,     0,
       0,    59,    65,    49,    61,    71,    52,    67,     0,     0,
       0,     0,     0,     0,     0,    75,    78,     0,    58,     0,
      62,     0,     0,     0,     0,     0,     0,     0,    13,     0,
      12,    60,    70,     0,     0,     0,     0,     0,    51,    66,
      83,    53,    68,    82,    80,    63,    11,     0,     0,     0,
       0,     0,     0,     0,    84,    81
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -201,  -201,  -201,   323,  -201,  -201,    -9,   303,  -201,     3,
    -201,   297,  -201,   261,  -201,   230,  -121,  -131,  -200,  -201,
    -201,  -201,  -201,    72,  -201,  -201,   -33,   -21,   266,   -35,
    -201,   253,   200,   195,   -50,  -201,  -201,   -23,  -201,  -201,
    -201,  -201,  -201
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,   221,    14,    15,    16,    31,
      11,    32,    33,    34,    71,    72,   115,   116,   117,   118,
     119,   188,   223,   239,   120,   121,   122,    84,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    85,    60,    61,
     129,   130,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      59,    22,    49,    10,   191,    30,    59,   102,    68,    81,
      10,   210,   211,   235,   237,    83,   213,   265,   215,   267,
     254,    59,    27,    28,   263,   211,     3,     4,     5,   139,
     140,   141,   142,    18,    59,   143,    75,    29,   216,   216,
     144,    77,    77,    77,    77,   127,   128,   262,   169,   171,
     173,    17,   149,   269,    77,   272,   -40,     3,     4,     5,
     145,   -36,   -40,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,   186,   227,
     231,   233,   234,   236,   212,    59,    59,   179,   181,   226,
      25,   232,   -36,    86,   264,    26,    63,    36,    78,   196,
     197,   198,   246,    86,   199,    79,   201,   203,   205,   207,
      25,   280,   209,   214,    86,    26,   261,   126,    86,    39,
      40,    64,   268,     1,   271,     2,   275,    41,    42,    98,
      99,   100,   277,   278,   234,   236,    43,   131,   132,   133,
     134,    37,    28,   135,     3,     4,     5,    44,   136,   266,
     261,   268,   271,    20,    86,    21,    45,    46,     3,     4,
       5,   225,    47,    23,   101,    24,    39,    40,   137,    65,
      73,    13,    48,  -163,    41,    42,   123,   150,    74,    39,
      40,   177,    69,    43,    70,    77,    77,    41,    42,    96,
      97,   222,    59,   175,   240,    70,    43,     3,     4,     5,
     182,    86,   183,    45,    46,    59,    59,   249,   251,    47,
     242,   103,    12,   244,    13,    87,    45,    46,   182,    48,
     252,   104,    47,   243,   106,    35,   -17,    23,   219,    24,
     -79,   -79,    48,    59,   259,   274,    89,    90,   -79,   -79,
      -7,    12,   105,    13,    59,   125,   240,   -79,   220,     3,
       4,     5,   -79,   258,    28,   -79,   -79,    59,   -79,   285,
     -79,   -79,    -7,    -7,    -7,   260,    28,   -79,   -79,   190,
     138,    39,    40,   -79,   -79,   -79,   276,    28,   -79,    41,
      42,    -2,     1,   -79,     2,    86,   174,   256,    43,   152,
     153,   165,   167,   108,   187,   189,   109,   110,   192,    44,
     195,   111,   112,     3,     4,     5,   193,   194,    45,    46,
     107,   218,    39,    40,    47,   113,   245,   241,   247,   114,
      41,    42,   253,   255,    48,   270,   257,   281,   282,    43,
      19,    66,   283,    76,   108,   124,   176,   109,   110,   279,
      44,   151,   111,   112,   155,   157,   159,   161,   163,    45,
      46,   190,   147,    39,    40,    47,   113,     0,     0,     0,
     114,    41,    42,     0,     0,    48,     0,     0,     0,     0,
      43,     0,     0,     0,     0,   108,     0,     0,   109,   110,
       0,    44,     0,   111,   112,     0,     0,     0,     0,     0,
      45,    46,   190,     0,    39,    40,    47,   113,     0,     0,
       0,   114,    41,    42,     0,     0,    48,     0,     0,     0,
       0,    43,     0,     0,     0,     0,   228,     0,     0,   229,
     230,     0,    44,     0,   111,   112,     0,     0,     0,     0,
       0,    45,    46,   184,     0,    39,    40,    47,   113,     0,
       0,     0,   114,    41,    42,     0,    38,    48,    39,    40,
       0,     0,    43,     0,     0,     0,    41,    42,    88,     0,
       0,     0,     0,    44,     0,    43,    89,    90,    91,    92,
       0,    93,    45,    46,     0,     0,    44,     0,    47,    67,
       0,    39,    40,   185,     0,    45,    46,     0,    48,    41,
      42,    47,    80,     0,    39,    40,    94,    95,    43,     0,
       0,    48,    41,    42,     0,     0,     0,     0,     0,    44,
      82,    43,    39,    40,     0,     0,     0,     0,    45,    46,
      41,    42,    44,     0,    47,     0,     0,     0,     0,    43,
       0,    45,    46,   126,    48,    39,    40,    47,     0,     0,
      44,     0,     0,    41,    42,     0,     0,    48,     0,    45,
      46,   146,    43,    39,    40,    47,     0,     0,     0,     0,
       0,    41,    42,    44,   148,    48,    39,    40,     0,     0,
      43,     0,    45,    46,    41,    42,     0,     0,    47,     0,
       0,    44,   178,    43,    39,    40,     0,     0,    48,     0,
      45,    46,    41,    42,    44,     0,    47,     0,     0,     0,
       0,    43,     0,    45,    46,   180,    48,    39,    40,    47,
       0,     0,    44,     0,     0,    41,    42,     0,     0,    48,
       0,    45,    46,   200,    43,    39,    40,    47,     0,     0,
       0,     0,     0,    41,    42,    44,   202,    48,    39,    40,
       0,     0,    43,     0,    45,    46,    41,    42,     0,     0,
      47,     0,     0,    44,   204,    43,    39,    40,     0,     0,
      48,     0,    45,    46,    41,    42,    44,     0,    47,     0,
       0,     0,     0,    43,     0,    45,    46,   206,    48,    39,
      40,    47,     0,     0,    44,     0,     0,    41,    42,     0,
       0,    48,     0,    45,    46,   208,    43,    39,    40,    47,
       0,     0,     0,     0,     0,    41,    42,    44,   224,    48,
      39,    40,     0,     0,    43,     0,    45,    46,    41,    42,
       0,     0,    47,     0,     0,    44,   238,    43,    39,    40,
       0,     0,    48,     0,    45,    46,    41,    42,    44,     0,
      47,     0,     0,     0,     0,    43,     0,    45,    46,   248,
      48,    39,    40,    47,     0,     0,    44,     0,     0,    41,
      42,     0,     0,    48,     0,    45,    46,   250,    43,    39,
      40,    47,     0,     0,     0,     0,     0,    41,    42,    44,
     273,    48,    39,    40,     0,     0,    43,     0,    45,    46,
      41,    42,     0,     0,    47,     0,     0,    44,   284,    43,
      39,    40,     0,     0,    48,     0,    45,    46,    41,    42,
      44,     0,    47,     0,     0,     0,     0,    43,     0,    45,
      46,    38,    48,    39,    40,    47,     0,     0,    44,     0,
       0,    41,    42,     0,     0,    48,     0,    45,    46,   154,
      43,    39,    40,    47,     0,     0,     0,     0,     0,    41,
      42,     0,   156,    48,    39,    40,     0,     0,    43,     0,
      45,    46,    41,    42,     0,     0,    47,     0,     0,     0,
     158,    43,    39,    40,     0,     0,    48,     0,    45,    46,
      41,    42,     0,     0,    47,     0,     0,     0,     0,    43,
       0,    45,    46,   160,    48,    39,    40,    47,     0,     0,
       0,     0,     0,    41,    42,     0,     0,    48,     0,    45,
      46,   162,    43,    39,    40,    47,     0,     0,     0,     0,
       0,    41,    42,     0,   164,    48,    39,    40,     0,     0,
      43,     0,    45,    46,    41,    42,     0,     0,    47,     0,
       0,     0,   166,    43,    39,    40,     0,     0,    48,     0,
      45,    46,    41,    42,     0,     0,    47,     0,     0,     0,
       0,    43,     0,    45,    46,   168,    48,    39,    40,    47,
       0,     0,     0,     0,     0,    41,    42,     0,     0,    48,
       0,    45,    46,   170,    43,    39,    40,    47,     0,     0,
       0,     0,     0,    41,    42,     0,   172,    48,    39,    40,
       0,     0,    43,     0,    45,    46,    41,    42,     0,     0,
      47,     0,     0,     0,     0,    43,     0,     0,     0,     0,
      48,     0,    45,    46,     0,     0,     0,     0,    47,     0,
       0,   131,   132,   133,   134,    45,    46,   135,    48,     0,
       0,    47,   136,   131,   132,   133,   134,     0,     0,   135,
       0,    48,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   217,     0,     0,     0,     0,
      77,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    77
};

static const yytype_int16 yycheck[] =
{
      23,    10,    23,     0,   125,     1,    29,    57,    29,    44,
       7,    26,    27,   213,   214,    48,    30,    30,    38,    38,
      32,    44,    51,    52,    26,    27,    22,    23,    24,     7,
       8,     9,    10,     0,    57,    13,     1,    53,    58,    58,
      18,    56,    56,    56,    56,    78,    79,   247,    98,    99,
     100,    56,    87,   253,    56,   255,    51,    22,    23,    24,
      38,    57,    57,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   111,   210,
     211,   212,   213,   214,    26,   108,   109,   108,   109,   210,
      49,   212,    57,    35,    26,    54,     4,    56,    49,   132,
     133,   134,   223,    35,   137,    56,   139,   140,   141,   142,
      49,    32,   145,    30,    35,    54,   247,     1,    35,     3,
       4,     1,   253,     1,   255,     3,   257,    11,    12,    41,
      42,    43,   263,   264,   265,   266,    20,     7,     8,     9,
      10,    51,    52,    13,    22,    23,    24,    31,    18,    30,
     281,   282,   283,     1,    35,     3,    40,    41,    22,    23,
      24,   194,    46,    53,     1,    55,     3,     4,    38,     1,
      57,     3,    56,    57,    11,    12,     1,     1,    51,     3,
       4,    51,     1,    20,     3,    56,    56,    11,    12,    39,
      40,   188,   215,     1,   215,     3,    20,    22,    23,    24,
       1,    35,     3,    40,    41,   228,   229,   228,   229,    46,
     219,    50,     1,   222,     3,    36,    40,    41,     1,    56,
       3,    50,    46,   220,    52,    51,    52,    53,     1,    55,
       3,     4,    56,   256,   243,   256,    14,    15,    11,    12,
       0,     1,    49,     3,   267,    57,   267,    20,    21,    22,
      23,    24,    25,    51,    52,    28,    29,   280,    31,   280,
      33,    34,    22,    23,    24,    51,    52,    40,    41,     1,
      57,     3,     4,    46,    47,    48,    51,    52,    51,    11,
      12,     0,     1,    56,     3,    35,    50,    37,    20,    89,
      90,    96,    97,    25,    51,    51,    28,    29,    50,    31,
       1,    33,    34,    22,    23,    24,    57,    52,    40,    41,
       1,    51,     3,     4,    46,    47,    48,     1,    27,    51,
      11,    12,    27,    30,    56,     1,    30,    27,    27,    20,
       7,    28,    30,    36,    25,    74,   106,    28,    29,   267,
      31,    88,    33,    34,    91,    92,    93,    94,    95,    40,
      41,     1,    86,     3,     4,    46,    47,    -1,    -1,    -1,
      51,    11,    12,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    25,    -1,    -1,    28,    29,
      -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      40,    41,     1,    -1,     3,     4,    46,    47,    -1,    -1,
      -1,    51,    11,    12,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    25,    -1,    -1,    28,
      29,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    41,     1,    -1,     3,     4,    46,    47,    -1,
      -1,    -1,    51,    11,    12,    -1,     1,    56,     3,     4,
      -1,    -1,    20,    -1,    -1,    -1,    11,    12,     6,    -1,
      -1,    -1,    -1,    31,    -1,    20,    14,    15,    16,    17,
      -1,    19,    40,    41,    -1,    -1,    31,    -1,    46,     1,
      -1,     3,     4,    51,    -1,    40,    41,    -1,    56,    11,
      12,    46,     1,    -1,     3,     4,    44,    45,    20,    -1,
      -1,    56,    11,    12,    -1,    -1,    -1,    -1,    -1,    31,
       1,    20,     3,     4,    -1,    -1,    -1,    -1,    40,    41,
      11,    12,    31,    -1,    46,    -1,    -1,    -1,    -1,    20,
      -1,    40,    41,     1,    56,     3,     4,    46,    -1,    -1,
      31,    -1,    -1,    11,    12,    -1,    -1,    56,    -1,    40,
      41,     1,    20,     3,     4,    46,    -1,    -1,    -1,    -1,
      -1,    11,    12,    31,     1,    56,     3,     4,    -1,    -1,
      20,    -1,    40,    41,    11,    12,    -1,    -1,    46,    -1,
      -1,    31,     1,    20,     3,     4,    -1,    -1,    56,    -1,
      40,    41,    11,    12,    31,    -1,    46,    -1,    -1,    -1,
      -1,    20,    -1,    40,    41,     1,    56,     3,     4,    46,
      -1,    -1,    31,    -1,    -1,    11,    12,    -1,    -1,    56,
      -1,    40,    41,     1,    20,     3,     4,    46,    -1,    -1,
      -1,    -1,    -1,    11,    12,    31,     1,    56,     3,     4,
      -1,    -1,    20,    -1,    40,    41,    11,    12,    -1,    -1,
      46,    -1,    -1,    31,     1,    20,     3,     4,    -1,    -1,
      56,    -1,    40,    41,    11,    12,    31,    -1,    46,    -1,
      -1,    -1,    -1,    20,    -1,    40,    41,     1,    56,     3,
       4,    46,    -1,    -1,    31,    -1,    -1,    11,    12,    -1,
      -1,    56,    -1,    40,    41,     1,    20,     3,     4,    46,
      -1,    -1,    -1,    -1,    -1,    11,    12,    31,     1,    56,
       3,     4,    -1,    -1,    20,    -1,    40,    41,    11,    12,
      -1,    -1,    46,    -1,    -1,    31,     1,    20,     3,     4,
      -1,    -1,    56,    -1,    40,    41,    11,    12,    31,    -1,
      46,    -1,    -1,    -1,    -1,    20,    -1,    40,    41,     1,
      56,     3,     4,    46,    -1,    -1,    31,    -1,    -1,    11,
      12,    -1,    -1,    56,    -1,    40,    41,     1,    20,     3,
       4,    46,    -1,    -1,    -1,    -1,    -1,    11,    12,    31,
       1,    56,     3,     4,    -1,    -1,    20,    -1,    40,    41,
      11,    12,    -1,    -1,    46,    -1,    -1,    31,     1,    20,
       3,     4,    -1,    -1,    56,    -1,    40,    41,    11,    12,
      31,    -1,    46,    -1,    -1,    -1,    -1,    20,    -1,    40,
      41,     1,    56,     3,     4,    46,    -1,    -1,    31,    -1,
      -1,    11,    12,    -1,    -1,    56,    -1,    40,    41,     1,
      20,     3,     4,    46,    -1,    -1,    -1,    -1,    -1,    11,
      12,    -1,     1,    56,     3,     4,    -1,    -1,    20,    -1,
      40,    41,    11,    12,    -1,    -1,    46,    -1,    -1,    -1,
       1,    20,     3,     4,    -1,    -1,    56,    -1,    40,    41,
      11,    12,    -1,    -1,    46,    -1,    -1,    -1,    -1,    20,
      -1,    40,    41,     1,    56,     3,     4,    46,    -1,    -1,
      -1,    -1,    -1,    11,    12,    -1,    -1,    56,    -1,    40,
      41,     1,    20,     3,     4,    46,    -1,    -1,    -1,    -1,
      -1,    11,    12,    -1,     1,    56,     3,     4,    -1,    -1,
      20,    -1,    40,    41,    11,    12,    -1,    -1,    46,    -1,
      -1,    -1,     1,    20,     3,     4,    -1,    -1,    56,    -1,
      40,    41,    11,    12,    -1,    -1,    46,    -1,    -1,    -1,
      -1,    20,    -1,    40,    41,     1,    56,     3,     4,    46,
      -1,    -1,    -1,    -1,    -1,    11,    12,    -1,    -1,    56,
      -1,    40,    41,     1,    20,     3,     4,    46,    -1,    -1,
      -1,    -1,    -1,    11,    12,    -1,     1,    56,     3,     4,
      -1,    -1,    20,    -1,    40,    41,    11,    12,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      56,    -1,    40,    41,    -1,    -1,    -1,    -1,    46,    -1,
      -1,     7,     8,     9,    10,    40,    41,    13,    56,    -1,
      -1,    46,    18,     7,     8,     9,    10,    -1,    -1,    13,
      -1,    56,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    51,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,    22,    23,    24,    60,    61,    62,    63,
      68,    69,     1,     3,    65,    66,    67,    56,     0,    62,
       1,     3,    65,    53,    55,    49,    54,    51,    52,    53,
       1,    68,    70,    71,    72,    51,    56,    51,     1,     3,
       4,    11,    12,    20,    31,    40,    41,    46,    56,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,   101,     4,     1,     1,    66,     1,    86,     1,
       3,    73,    74,    57,    51,     1,    70,    56,    49,    56,
       1,    88,     1,    85,    86,    96,    35,    36,     6,    14,
      15,    16,    17,    19,    44,    45,    39,    40,    41,    42,
      43,     1,    93,    50,    50,    49,    52,     1,    25,    28,
      29,    33,    34,    47,    51,    75,    76,    77,    78,    79,
      83,    84,    85,     1,    72,    57,     1,    85,    85,    99,
     100,     7,     8,     9,    10,    13,    18,    38,    57,     7,
       8,     9,    10,    13,    18,    38,     1,    87,     1,    88,
       1,    90,    91,    91,     1,    90,     1,    90,     1,    90,
       1,    90,     1,    90,     1,    92,     1,    92,     1,    93,
       1,    93,     1,    93,    50,     1,    74,    51,     1,    86,
       1,    86,     1,     3,     1,    51,    85,    51,    80,    51,
       1,    75,    50,    57,    52,     1,    85,    85,    85,    85,
       1,    85,     1,    85,     1,    85,     1,    85,     1,    85,
      26,    27,    26,    30,    30,    38,    58,    51,    51,     1,
      21,    64,    68,    81,     1,    85,    75,    76,    25,    28,
      29,    76,    75,    76,    76,    77,    76,    77,     1,    82,
      86,     1,    65,    68,    65,    48,    75,    27,     1,    86,
       1,    86,     3,    27,    32,    30,    37,    30,    51,    65,
      51,    76,    77,    26,    26,    30,    30,    38,    76,    77,
       1,    76,    77,     1,    86,    76,    51,    76,    76,    82,
      32,    27,    27,    30,     1,    86
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    61,    61,    62,    62,    62,    63,    63,
      63,    64,    64,    64,    65,    65,    65,    65,    66,    66,
      66,    66,    67,    67,    67,    67,    68,    68,    68,    69,
      69,    69,    69,    69,    69,    70,    70,    71,    71,    71,
      71,    72,    73,    73,    73,    73,    74,    74,    74,    75,
      75,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    77,    77,    77,    77,    77,
      77,    77,    78,    78,    78,    79,    80,    80,    81,    81,
      82,    82,    82,    82,    82,    83,    83,    83,    84,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    86,
      86,    86,    87,    87,    87,    88,    88,    88,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    90,    90,    90,    91,    91,    91,    91,    91,    92,
      92,    92,    92,    92,    92,    92,    93,    93,    93,    94,
      94,    94,    95,    95,    96,    96,    97,    97,    97,    97,
      98,    98,    99,    99,   100,   100,   100,   101,   101,   101,
     101
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     3,
       3,     4,     3,     3,     3,     1,     3,     1,     1,     3,
       3,     3,     1,     4,     3,     2,     1,     1,     1,     6,
       5,     2,     4,     3,     5,     1,     0,     3,     1,     3,
       1,     2,     3,     1,     3,     1,     1,     3,     2,     1,
       1,     6,     4,     6,     1,     1,     1,     1,     2,     4,
       6,     4,     2,     6,     2,     4,     6,     4,     6,     4,
       6,     4,     2,     1,     2,     4,     2,     0,     2,     0,
       3,     5,     3,     3,     5,     2,     3,     3,     2,     3,
       3,     3,     3,     3,     2,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       1,     3,     3,     1,     3,     2,     1,     2,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     4,     3,     1,     1,     2,
       4,     2,     1,     0,     3,     1,     3,     1,     1,     1,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 66 "parser.y" /* yacc.c:1646  */
    { syntaxTree = (yyvsp[0].tree);}
#line 1680 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 69 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree));}
#line 1686 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 70 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 1692 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 73 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 1698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 74 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 1704 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 75 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 1710 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 79 "parser.y" /* yacc.c:1646  */
    { TreeNode* t = (yyvsp[-1].tree);
                   													if (t != NULL)
                   										  			{ 	while (t->sibling != NULL)
																		{
                        									    			t = t->sibling;
																			if ((yyvsp[-2].expType) == Integer){t->expType=Integer;}
												  				  			else if ((yyvsp[-2].expType) == Boolean){t->expType=Boolean;}
												  				  			else if ((yyvsp[-2].expType) == Char){t->expType=Char;}
																		}
                     										  			(yyval.tree) = (yyvsp[-1].tree); 
																		yyerrok;}
                     												else (yyval.tree) = NULL;
																	if((yyval.tree) != NULL)
																	{
																	  	if ((yyvsp[-2].expType) == Integer){(yyval.tree)->expType=Integer;}
													  				  	else if ((yyvsp[-2].expType) == Boolean){(yyval.tree)->expType=Boolean;}
													  				  	else if ((yyvsp[-2].expType) == Char){(yyval.tree)->expType=Char;}
																	}
                 												}
#line 1734 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 98 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok;}
#line 1740 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 99 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok;}
#line 1746 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 102 "parser.y" /* yacc.c:1646  */
    { TreeNode* t = (yyvsp[-1].tree);
                   										  			if (t != NULL)
                   										  			{	
																		t->isStatic = true;
																		while (t->sibling != NULL)
																		{
																			if ((yyvsp[-2].expType) == Integer){t->expType=Integer;}
												  				  			else if ((yyvsp[-2].expType) == Boolean){t->expType=Boolean;}
												  				  			else if ((yyvsp[-2].expType) == Char){t->expType=Char;}
																			
                        									    			t = t->sibling;
																			t->isStatic = true;
																		}
                     										    		(yyval.tree) = (yyvsp[-1].tree); 
																		yyerrok;}
                     										  		else (yyval.tree) = NULL;
																	if((yyval.tree) != NULL)
																	{
																		if ((yyvsp[-2].expType) == Integer){t->expType=Integer;}
													  				  	else if ((yyvsp[-2].expType) == Boolean){t->expType=Boolean;}
													  				  	else if ((yyvsp[-2].expType) == Char){t->expType=Char;}
																	}
																}
#line 1774 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 125 "parser.y" /* yacc.c:1646  */
    { TreeNode* t = (yyvsp[-1].tree);
                   										  			if (t != NULL)
                   										  		  	{	while (t->sibling != NULL)
																		{
                        									    			t = t->sibling;
																			if ((yyvsp[-2].expType) == Integer){t->expType=Integer;}
												  				  			else if ((yyvsp[-2].expType) == Boolean){t->expType=Boolean;}
												  				  			else if ((yyvsp[-2].expType) == Char){t->expType=Char;}
																		}
                     										    		(yyval.tree) = (yyvsp[-1].tree); 
																		yyerrok;}
                     										  		else (yyval.tree) = NULL;
																	if((yyval.tree) != NULL)
																	{
																		if ((yyvsp[-2].expType) == Integer){(yyval.tree)->expType=Integer;}
													  				  	else if ((yyvsp[-2].expType) == Boolean){(yyval.tree)->expType=Boolean;}
													  				  	else if ((yyvsp[-2].expType) == Char){(yyval.tree)->expType=Char;}
																	}
																}
#line 1798 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 144 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 1804 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 147 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree)); yyerrok;}
#line 1810 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 1816 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 149 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-2].tree); yyerrok;}
#line 1822 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 150 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 1828 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 1834 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 154 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].tree)->child[0] = (yyvsp[0].tree);
												  				  (yyval.tree) = (yyvsp[-2].tree);}
#line 1841 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 156 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok;}
#line 1847 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-2].tree); }
#line 1853 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 160 "parser.y" /* yacc.c:1646  */
    { //printf("IN THE ID GRAMMAR\n");
																  (yyval.tree) = newDeclNode(VarK);
												  				  (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
																}
#line 1863 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 165 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newDeclNode(VarK);
												  				  (yyval.tree)->linenum = (yyvsp[-3].tokenData)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
												  				  (yyval.tree)->isArray = true;
																  (yyval.tree)->memSize = (yyvsp[-1].tokenData)->numValue + 1;
																  //printf("tokenstr %s linenum %d\n", $1->tokenstr, $1->linenum);
																}
#line 1875 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 172 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 1881 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 173 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok;}
#line 1887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 176 "parser.y" /* yacc.c:1646  */
    {(yyval.expType) = Integer;}
#line 1893 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 177 "parser.y" /* yacc.c:1646  */
    {(yyval.expType) = Boolean;}
#line 1899 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 178 "parser.y" /* yacc.c:1646  */
    {(yyval.expType) = Char;}
#line 1905 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newDeclNode(FuncK);
												  				  (yyval.tree)->linenum = (yyvsp[-4].tokenData)->linenum;
												  				  (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				  (yyval.tree)->child[1] = (yyvsp[0].tree);
												  				  (yyval.tree)->subkind.decl = FuncK;
												  				  (yyval.tree)->attr.name = (yyvsp[-4].tokenData)->tokenstr;
												  				  if ((yyvsp[-5].expType) == Integer){(yyval.tree)->expType=Integer;}
												  				  else if ((yyvsp[-5].expType) == Boolean){(yyval.tree)->expType=Boolean;}
												  				  else if ((yyvsp[-5].expType) == Char){(yyval.tree)->expType=Char;} }
#line 1919 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 191 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newDeclNode(FuncK);
												  				  (yyval.tree)->linenum = (yyvsp[-4].tokenData)->linenum;
												  				  (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				  (yyval.tree)->child[1] = (yyvsp[0].tree);
												  				  (yyval.tree)->subkind.decl = FuncK;
												  				  (yyval.tree)->attr.name = (yyvsp[-4].tokenData)->tokenstr;
												  				  (yyval.tree)->expType = Void;}
#line 1931 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 198 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 1937 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 199 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 1943 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 1949 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 201 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 1955 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 204 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 1961 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 205 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 1967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 208 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree)); yyerrok;}
#line 1973 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 209 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 1979 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 210 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-2].tree);}
#line 1985 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 211 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 1991 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 214 "parser.y" /* yacc.c:1646  */
    { TreeNode* t = (yyvsp[0].tree);
                   										  		  if (t != NULL)
                   										  		  {		while (t->sibling != NULL)
																		{
                        									    			t = t->sibling;
																			if ((yyvsp[-1].expType) == Integer){t->expType=Integer;}
												  				  			else if ((yyvsp[-1].expType) == Boolean){t->expType=Boolean;}
												  				  			else if ((yyvsp[-1].expType) == Char){t->expType=Char;}
																		}
                     										    		(yyval.tree) = (yyvsp[0].tree); }
                     										  	  else (yyval.tree) = NULL;
																  if((yyval.tree) != NULL)
																  {
																	if ((yyvsp[-1].expType) == Integer){(yyval.tree)->expType=Integer;}
												  				  	else if ((yyvsp[-1].expType) == Boolean){(yyval.tree)->expType=Boolean;}
												  				  	else if ((yyvsp[-1].expType) == Char){(yyval.tree)->expType=Char;}
																  }
																}
#line 2014 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree)); yyerrok;}
#line 2020 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 235 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2026 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 236 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 2032 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 237 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 2038 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 240 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newDeclNode(ParamK);
												  				  (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
												  				  (yyval.tree)->subkind.decl = ParamK;}
#line 2047 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 244 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newDeclNode(ParamK);
												  				  (yyval.tree)->linenum = (yyvsp[-2].tokenData)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-2].tokenData)->tokenstr;
												  				  (yyval.tree)->subkind.decl = ParamK;
												  				  (yyval.tree)->attr.name = (yyvsp[-2].tokenData)->tokenstr;
												  				  (yyval.tree)->isArray = true;}
#line 2058 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 250 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok;}
#line 2064 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 254 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2070 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 255 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree); }
#line 2076 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 258 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(IfK);
												  				  (yyval.tree)->linenum = (yyvsp[-4].tree)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-5].tokenData)->tokenstr;
												  				  (yyval.tree)->child[0] = (yyvsp[-4].tree);
												  				  (yyval.tree)->child[1] = (yyvsp[-2].tree);
												  				  (yyval.tree)->child[2] = (yyvsp[0].tree);
																}
#line 2088 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 266 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(WhileK);
												  				  (yyval.tree)->linenum = (yyvsp[-3].tokenData)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
												  				  (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				  (yyval.tree)->child[1] = (yyvsp[0].tree);
																}
#line 2099 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 273 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(ForK);
												  				  (yyval.tree)->child[0] = newDeclNode(VarK);
																  (yyval.tree)->child[0]->attr.name = (yyvsp[-4].tokenData)->tokenstr;
																  (yyval.tree)->child[0]->linenum = (yyvsp[-4].tokenData)->linenum;
																  (yyval.tree)->child[0]->expType=Integer;
												  				  (yyval.tree)->child[1] = (yyvsp[-2].tree);
												  				  (yyval.tree)->linenum = (yyvsp[-5].tokenData)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-5].tokenData)->tokenstr;
												  				  (yyval.tree)->child[2] = (yyvsp[0].tree);
																}
#line 2114 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 284 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2120 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 285 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2126 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 286 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2132 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 287 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2138 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 288 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 2144 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 289 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2150 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 290 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2156 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 291 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok;}
#line 2162 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 292 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok;}
#line 2168 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 293 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2174 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 294 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2180 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 297 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(IfK); ///changed stmt to matched
												  				  (yyval.tree)->linenum = (yyvsp[-2].tree)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
												  				  (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				  (yyval.tree)->child[1] = (yyvsp[0].tree); }
#line 2190 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 303 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(IfK);
												  				  (yyval.tree)->linenum = (yyvsp[-4].tree)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-5].tokenData)->tokenstr;
												  				  (yyval.tree)->child[0] = (yyvsp[-4].tree);
												 			 	  (yyval.tree)->child[1] = (yyvsp[-2].tree); 
												  				  (yyval.tree)->child[2] = (yyvsp[0].tree); }
#line 2201 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 309 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(WhileK);
												  				  (yyval.tree)->linenum = (yyvsp[-2].tree)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
												  				  (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				  (yyval.tree)->child[1] = (yyvsp[0].tree);
																}
#line 2212 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 316 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(ForK);
												  				  (yyval.tree)->child[0] = newDeclNode(VarK);
																  (yyval.tree)->child[0]->attr.name = (yyvsp[-4].tokenData)->tokenstr;
																  (yyval.tree)->child[0]->linenum = (yyvsp[-4].tokenData)->linenum;
																  (yyval.tree)->child[0]->expType=Integer;
												  				  (yyval.tree)->child[1] = (yyvsp[-2].tree);
												  				  (yyval.tree)->linenum = (yyvsp[-5].tokenData)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-5].tokenData)->tokenstr;
												  				  (yyval.tree)->child[2] = (yyvsp[0].tree);
																}
#line 2227 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 326 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2233 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 327 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2239 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 328 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2245 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 331 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-1].tree);  }
#line 2251 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 332 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;  }
#line 2257 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 333 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2263 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 336 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(CompoundK);
																  (yyval.tree)->linenum = (yyvsp[-3].tokenData)->linenum;
												  				  (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				  (yyval.tree)->child[1] = (yyvsp[-1].tree); 
																  yyerrok;}
#line 2273 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 343 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree));}
#line 2279 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 344 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 2285 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 347 "parser.y" /* yacc.c:1646  */
    {if((yyvsp[0].tree) != NULL)
																{(yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree));}
																else
																{(yyval.tree) = (yyvsp[-1].tree);}}
#line 2294 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 351 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = NULL;}
#line 2300 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 372 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(RangeK);
												  				  (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
												  				  (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				  (yyval.tree)->child[1] = (yyvsp[0].tree); }
#line 2310 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 377 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(RangeK);
												  				  (yyval.tree)->linenum = (yyvsp[-3].tokenData)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
												  				  (yyval.tree)->child[0] = (yyvsp[-4].tree);
												  				  (yyval.tree)->child[1] = (yyvsp[-2].tree); 
																  (yyval.tree)->child[2] = (yyvsp[0].tree);}
#line 2321 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 383 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2327 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 384 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2333 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 385 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2339 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 388 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(ReturnK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;}
#line 2347 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 391 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(ReturnK);
																 (yyval.tree)->linenum = (yyvsp[-2].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-2].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-1].tree);
																 yyerrok;}
#line 2357 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 396 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2363 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 399 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newStmtNode(BreakK);
												  				  (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;}
#line 2371 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 404 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(AssignK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2381 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 409 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(AssignK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2391 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 414 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(AssignK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2401 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 419 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(AssignK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2411 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 424 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(AssignK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2421 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 429 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(AssignK);
																 (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-1].tree);}
#line 2430 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 433 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(AssignK);
																 (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-1].tree);}
#line 2439 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 437 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2445 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 438 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2451 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 439 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2457 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 440 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2463 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 441 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2469 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 442 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2475 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 443 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2481 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 444 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2487 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 445 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2493 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 446 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2499 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 447 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 448 "parser.y" /* yacc.c:1646  */
    { (yyval.tree)=NULL; yyerrok; }
#line 2511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 449 "parser.y" /* yacc.c:1646  */
    { (yyval.tree)=NULL; yyerrok; }
#line 2517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 452 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);//$1->avalue
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->avalue;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2527 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 457 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 458 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-2].tree); }
#line 2539 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 461 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->avalue;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2549 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 466 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2555 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 467 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2561 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 470 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->avalue;
												  				 (yyval.tree)->child[0] = (yyvsp[0].tree);}
#line 2570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 474 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 475 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2582 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 478 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2592 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 483 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2602 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 488 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2612 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 493 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2622 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 498 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2632 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 503 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2642 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 508 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2648 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 509 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2654 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 510 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2660 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 511 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2666 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 512 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2672 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 513 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2678 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 514 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2684 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 518 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2694 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 523 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2704 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 528 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2710 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 532 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 537 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2730 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 542 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2736 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 543 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2742 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 544 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok;}
#line 2748 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 548 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2758 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 553 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2768 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 558 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[-1].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-2].tree);
												  				 (yyval.tree)->child[1] = (yyvsp[0].tree);}
#line 2778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 563 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2784 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 564 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2790 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 565 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2796 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 566 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2802 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 580 "parser.y" /* yacc.c:1646  */
    { (yyval.tree)->child[0] = (yyvsp[0].tree);}
#line 2808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 581 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2814 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 582 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; }
#line 2820 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 585 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
																 (yyval.tree)->isUnarySub = true;}
#line 2829 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 589 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
																 (yyval.tree)->isUnaryStar = true;}
#line 2838 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 593 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;}
#line 2846 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 598 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2852 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 599 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2858 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 602 "parser.y" /* yacc.c:1646  */
    {//printf("Line: %d	Token: %s\n", $1->linenum, $1->tokenstr);
																(yyval.tree) = newExpNode(IdK);
																 (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
																//printf("Line: %d	Token: %s	subkind: %d\n", $1->linenum, $1->tokenstr, $$->exp);
																}
#line 2869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 608 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK);
																 (yyval.tree)->child[0] = newExpNode(IdK);
																 (yyval.tree)->child[0]->attr.name = (yyvsp[-3].tokenData)->tokenstr;
																 (yyval.tree)->child[0]->linenum = (yyvsp[-3].tokenData)->linenum;
																 (yyval.tree)->attr.name = (yyvsp[-2].tokenData)->tokenstr;
																 (yyval.tree)->linenum = (yyvsp[-3].tokenData)->linenum;
																 //$$->isArray = true;
																 (yyval.tree)->child[1] = (yyvsp[-1].tree); 
																}
#line 2883 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 620 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-1].tree); yyerrok;}
#line 2889 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 621 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2895 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 622 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2901 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 623 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok;}
#line 2907 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 626 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(CallK);
																 (yyval.tree)->linenum = (yyvsp[-3].tokenData)->linenum;
												  				 (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
																 (yyval.tree)->child[0] = (yyvsp[-1].tree);}
#line 2916 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 630 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; yyerrok; }
#line 2922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 633 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2928 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 634 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 2934 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 637 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree)); yyerrok;}
#line 2940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 638 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[0].tree);}
#line 2946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 639 "parser.y" /* yacc.c:1646  */
    { (yyval.tree)=NULL; }
#line 2952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 642 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ConstantK);
																 (yyval.tree)->expType = Integer;
												  				 (yyval.tree)->attr.value = (yyvsp[0].tokenData)->numValue;
																 (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
																 (yyval.tree)->isConst = true;
																 yyerrok;}
#line 2963 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 648 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ConstantK);
																 (yyval.tree)->expType = Char;
												  				 (yyval.tree)->attr.cvalue = (yyvsp[0].tokenData)->cvalue;
																 (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
																 (yyval.tree)->isConst = true;
																 yyerrok;}
#line 2974 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 654 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ConstantK);
																 (yyval.tree)->expType = Char;
												  				 (yyval.tree)->attr.string = (yyvsp[0].tokenData)->avalue;
																 (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum;
																 (yyval.tree)->isArray = true;
																 (yyval.tree)->stringLength = (yyvsp[0].tokenData)->countValue;
																 (yyval.tree)->memSize = (yyvsp[0].tokenData)->countValue - 1;
																 (yyval.tree)->isConst = true;
																 yyerrok;}
#line 2988 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 663 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ConstantK);
																 (yyval.tree)->expType = Boolean;
												  				 (yyval.tree)->attr.value = (yyvsp[0].tokenData)->numValue;
																 (yyval.tree)->linenum = (yyvsp[0].tokenData)->linenum; 
																 (yyval.tree)->isConst = true;
																 yyerrok;}
#line 2999 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 3003 "parser.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 670 "parser.y" /* yacc.c:1906  */


/*
statementlist      : statementlist statement
		   | statement
		   ;


statement     : '\n'
	      | STATIC { printf("Line %d Token: STATIC\n", $1->linenum); }
	      | ID     { printf("Line %d Token: ID Value: %s\n", $1->linenum, $1->tokenstr); }
	      | NUMBER { printf("Line %d Token: NUMCONST Value: %d Input: %s\n", $1->linenum, $1->numValue, $1->tokenstr); }
	      | OPERATOR { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
	      | KEYWORD { printf("Line %d Token: %s\n", $1->linenum, $1->avalue); }

	      | EQ 	{ printf("Line %d Token: EQ\n", $1->linenum); }
	      | NEQ 	{ printf("Line %d Token: NEQ\n", $1->linenum); }
	      | DEC 	{ printf("Line %d Token: DEC\n", $1->linenum); }
	      | INC 	{ printf("Line %d Token: INC\n", $1->linenum); }
	      | MIN 	{ printf("Line %d Token: MIN\n", $1->linenum); }
	      | MAX 	{ printf("Line %d Token: MAX\n", $1->linenum); }
	      | GEQ 	{ printf("Line %d Token: GEQ\n", $1->linenum); }
	      | LEQ 	{ printf("Line %d Token: LEQ\n", $1->linenum); }
	      | ADDASS  { printf("Line %d Token: ADDASS\n", $1->linenum); }

	      | STRINGCONST 	{ printf("Line %d Token: STRINGCONST Value: %s Len: %d Input: %s\n", $1->linenum, $1->avalue, $1->countValue-2, $1->tokenstr); }
	      | CHARCONST   	{ printf("Line %d Token: CHARCONST Value: '%s' Input: %s\n", $1->linenum, $1->avalue, $1->tokenstr); }
	      | BOOLCONST 	{ printf("Line %d Token: BOOLCONST Value: %d Input: %s\n", $1->linenum, $1->numValue, $1->tokenstr); }
              ;
*/

extern int yydebug;
char* outFile;
int main(int argc, char *argv[])
{
	initErrorProcessing();
    extern int   opterr;					
    extern int   optind;					
    extern char *optarg;
	FILE *fp;
    int printTreeFlag = 0, printTreeType = 0;
    int c = 0;
	numErrors = 0;

	if(argc == 1)
	{
		yyparse();         // parse and build the tree in the global var syntaxTree.
	}
    else if (argc > 1) {
		while ((c = ourGetopt(argc, argv, (char *)"dphgDPM")) != EOF)
     	{   
	    	switch (c) {
            case        'd': //Turn on parser debugging
                yydebug = 1;
                break;
			case        'D': //Turn on symbol table debugging
                //printf("debugging symbol table... please wait...");
				symbolTable.debug(1); 
			printTreeType= 1;
                break;
			case        'h': //this usage message
                printf("Usage: c- [options] [sourceFile]\noptions:\n-d		- turn on parser debugging\n-D		- turn on symbol table debugging\n-h	- this usage message\n-p 	- print the abstract syntax tree\n-P	- print the abstract syntax tree plus type information\n");
                break;
	   		case        'p': //Print the abstract syntax tree
                printTreeFlag = 1;
                break;
			case        'P': //Print the abstract syntax tree plus type information
                printTreeType= 1;
                break;
			case        'M':
                printOffsetFlag = true;
				printTreeType= 1;
                break;
		default:
			printTreeType= 1;
		break;
           }
		}
		if(argc > optind)
		{
			/*fp = fopen(argv[optind], "r");
         		if (!fp){
            			fprintf(stderr, "Cannot open file\n");
            			exit(1);
         		}
        		yyin = fp;
         		do{
            			yyparse();
         		} while (!feof(yyin));
         		fclose(fp);*/
            if ((yyin = fopen(argv[optind], "r"))) {
				do{ yyparse(); } while (!feof(yyin));
                // file open successful
            }
            else {
                // failed to open file
				numErrors++;
                printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[1]);
				printf("Number of warnings: %d\n", numWarning);   // Warn
   				printf("Number of errors: %d\n", numErrors);   // ERR
                exit(1);
            }
		}
    }

    // init variables a through z
    for (int i=0; i<26; i++) vars[i] = 0.0;

    // do the parsing
    if (printTreeFlag) //in treeNode.c make a printTree function, simular to util.c in tiny.
    {
		printTree(syntaxTree);  // printTreeFlag is set by -p option
    }
	else if (printTreeType && numErrors == 0)
	{
		addIOLibrary(syntaxTree);
		printTreeSemantic(syntaxTree);  // printTreeTypes is set by -P option
		if((TreeNode*)symbolTable.lookup("main") == NULL)
		{
			numErrors++;
			printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
		}
		
		if(numErrors == 0)
		{
			printTree(syntaxTree);
			if (printOffsetFlag)
			{
				printf("Offset for end of global space: %d\n", goffset);
			}
		}
	}
	else if (numErrors == 0){
		addIOLibrary(syntaxTree);
		printTreeSemantic(syntaxTree); 
	}
	printf("Number of warnings: %d\n", numWarning);   // Warn
    printf("Number of errors: %d\n", numErrors);   // ERR
	      // Extract the filename from argv if given

	
	
	if(numErrors == 0)	
		{
			int i = 0;
			int stringLen = strlen(argv[optind]);
			char tempOut[stringLen];
			char *out = argv[optind];
			while(out[i] != '.' || i> stringLen)
			{
				tempOut[i] = out[i]; 
				//printf("%c", tempOut[i]);
				i++;
			}
			tempOut[i] = '.';
			tempOut[i+1] = 't';
			tempOut[i+2] = 'm';
			tempOut[i+3] = '\0';
			
			outFile = tempOut;
			//printf("codegen\n");
			codegen(outFile, syntaxTree);
		}
	

    return 0;
}
