/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include<iostream>
#include<fstream>
#include<set>
#include "lib/symbolTable.h"
#include "lib/symbolInfo.h"
#include "lib/ast.h"
#include "lib/treeWalker.h"
#include "lib/printUtil.h"

using namespace std;

int yyparse(void);
int yylex(void);

extern FILE *yyin;
extern int yylineno;

ofstream logout("log.txt"), tokenout("token.txt"), errorout("error.txt");
ofstream treeout("parseTree.txt");
PrintUtil printUtil(tokenout, logout, errorout);
Printer printer(logout, false);
SymbolTable symbolTable(11, &printer);
TreeWalker treeWalker;

bool inFunction = false;

set<FunctionSymbolInfo *> funcDeclared, funcDefined;
int errorCount;

string errorString = "";

void yyerror(char *s)
{
	// printf(s);
	// errorout << errorString << endl;
	errorCount++;
}

std::string getDataType(AST *node){
	auto t = dynamic_cast<ExpressionAST *> (node);
	if(t != nullptr) return t->getDataType();
	
	return "";
}

SymbolInfo *getSymbol(AST *node){
	auto t = dynamic_cast<SymbolAST *>(node);
	if(t != nullptr){
		auto name = t->getSymbol()->getName();
		auto symbol = symbolTable.lookup(name);

		return symbol;
	}
	return nullptr;
}

bool isAssignopCorrect(string lhs, string rhs){
	return !(lhs == "INT" && rhs == "FLOAT");
}

string getAddopType(string lhs, string rhs){
	return (lhs == "FLOAT" || rhs == "FLOAT") ? "FLOAT" : "INT";
}

bool errorIfVoid(AST *exp){
	auto type = getDataType(exp);
	if(type == "VOID"){
		printUtil.printError("Void cannot be used in expression",  exp->getBeginLine());
		return true;
	}
	return false;
}


#line 146 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 77 "parser.y"

	#include "lib/ast.h"

#line 193 "parser.tab.c"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    FOR = 259,
    DO = 260,
    INT = 261,
    FLOAT = 262,
    VOID = 263,
    SWITCH = 264,
    DEFAULT = 265,
    ELSE = 266,
    WHILE = 267,
    BREAK = 268,
    CHAR = 269,
    DOUBLE = 270,
    RETURN = 271,
    CASE = 272,
    CONTINUE = 273,
    MAIN = 274,
    CONST_INT = 275,
    CONST_FLOAT = 276,
    CONST_CHAR = 277,
    ASSIGNOP = 278,
    NOT = 279,
    LPAREN = 280,
    RPAREN = 281,
    LTHIRD = 282,
    RTHIRD = 283,
    LCURL = 284,
    RCURL = 285,
    COMMA = 286,
    SEMICOLON = 287,
    ADDOP = 288,
    MULOP = 289,
    INCOP = 290,
    DECOP = 291,
    RELOP = 292,
    LOGICOP = 293,
    BITOP = 294,
    ID = 295,
    PRINTLN = 296,
    LOWER_THAN_ELSE = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef  AST*  YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   152

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

#define YYUNDEFTOK  2
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    96,    96,   110,   117,   126,   133,   140,   149,   175,
     199,   231,   258,   258,   282,   298,   326,   345,   352,   370,
     377,   392,   392,   406,   417,   456,   463,   470,   479,   486,
     493,   500,   507,   519,   526,   535,   542,   548,   555,   562,
     570,   581,   590,   600,   609,   616,   627,   634,   641,   653,
     674,   700,   707,   722,   729,   747,   754,   772,   779,   800,
     807,   841,   854,   867,   876,   884,   923,   930,   937,   944,
     958,   973,   981,   987,   994
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "FOR", "DO", "INT", "FLOAT",
  "VOID", "SWITCH", "DEFAULT", "ELSE", "WHILE", "BREAK", "CHAR", "DOUBLE",
  "RETURN", "CASE", "CONTINUE", "MAIN", "CONST_INT", "CONST_FLOAT",
  "CONST_CHAR", "ASSIGNOP", "NOT", "LPAREN", "RPAREN", "LTHIRD", "RTHIRD",
  "LCURL", "RCURL", "COMMA", "SEMICOLON", "ADDOP", "MULOP", "INCOP",
  "DECOP", "RELOP", "LOGICOP", "BITOP", "ID", "PRINTLN", "LOWER_THAN_ELSE",
  "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "func_first_part", "$@1", "func_first_part2",
  "common_func_first_part", "parameter_list", "compound_statement", "$@2",
  "var_declaration", "type_specifier", "declaration_list", "statements",
  "statement", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
# endif

#define YYPACT_NINF (-65)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-16)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      50,   -65,   -65,   -65,    10,    50,   -65,   -65,   -65,   -11,
      -2,    -6,   -65,    26,   -65,   -65,    41,   -65,   -65,   -65,
     -65,    54,    56,    22,   -65,   107,   -65,    50,    73,   -65,
      57,   -65,    68,    76,    77,    78,    -9,   -65,   -65,    -9,
      -9,   -65,    -9,    67,    80,   -65,   -65,   -65,   -65,    66,
     -65,   -65,   -10,    72,   -65,    71,    31,    82,   -65,   -65,
       6,    81,    84,    90,   -65,    -9,    19,    -9,    86,    49,
     -65,    94,   -65,    -9,    -9,    85,   -65,   -65,    -9,   -65,
     -65,   -65,    -9,    -9,    -9,    -9,   -65,   -65,    50,   -65,
     -65,   102,    98,    19,   100,   -65,   -65,   -65,   103,    99,
     105,   108,   111,   -65,   -65,    82,   101,   -65,   104,   110,
     107,    -9,   107,   -65,    -9,   -65,   109,   -65,   -65,   131,
     117,   -65,   -65,   -65,   107,   107,   -65,   -65
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    25,    26,    27,     0,     2,     4,     6,     7,     0,
       0,     0,     5,     0,     1,     3,    21,     8,    10,     9,
      11,    12,    30,     0,    23,     0,    14,     0,     0,    32,
       0,    24,     0,     0,     0,     0,     0,    67,    68,     0,
       0,    46,     0,    49,     0,    36,    37,    39,    35,     0,
      33,    38,    64,     0,    51,    53,    55,    57,    59,    63,
       0,    19,     0,    28,    48,     0,     0,     0,     0,    64,
      62,     0,    61,    72,     0,     0,    22,    34,     0,    69,
      70,    47,     0,     0,     0,     0,    20,    13,     0,    18,
      31,     0,     0,     0,     0,    45,    66,    74,     0,    71,
       0,    49,     0,    52,    54,    58,    56,    60,    17,     0,
       0,     0,     0,    65,     0,    50,     0,    16,    29,    41,
       0,    43,    73,    44,     0,     0,    42,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -65,   -65,   -65,   140,    17,    29,   -65,   -65,   -65,   -65,
     -65,    79,   -65,    60,   -26,   -65,   -65,   -49,   -38,   -37,
     -32,   -64,    64,    65,    69,   -36,   -65,   -65,   -65
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    45,    46,     9,    27,    10,    11,
      60,    47,    25,    48,    13,    23,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    98,    99
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      77,    61,    69,    70,    68,    69,    72,    86,    71,    97,
      14,    37,    38,    78,   103,    39,    40,     7,    16,    21,
      32,    17,     7,    29,    42,    79,    80,    16,    93,     8,
      19,    43,    87,    92,     8,    94,    69,    88,   102,    37,
      38,    69,   100,    39,    40,    69,    69,    69,    69,   107,
     122,    41,    42,    30,    31,   111,     1,     2,     3,    43,
      12,   119,   108,   121,    83,    12,    22,    32,    84,    33,
      34,    24,     1,     2,     3,   126,   127,    69,    35,   120,
      26,   -15,    36,    28,    79,    80,    37,    38,    18,    20,
      39,    40,    73,    62,    74,    16,    76,    63,    41,    42,
      64,    65,    66,    67,    81,    75,    43,    44,    32,    82,
      33,    34,    90,     1,     2,     3,    85,    91,    95,    35,
      96,    89,   109,    36,   110,   101,   112,    37,    38,   113,
     114,    39,    40,   115,    83,    74,    16,   116,   118,    41,
      42,   123,   124,   125,   117,    15,   104,    43,    44,   106,
       0,     0,   105
};

static const yytype_int8 yycheck[] =
{
      49,    27,    39,    39,    36,    42,    42,     1,    40,    73,
       0,    20,    21,    23,    78,    24,    25,     0,    29,    25,
       1,    32,     5,     1,    33,    35,    36,    29,    66,     0,
      32,    40,    26,    65,     5,    67,    73,    31,    75,    20,
      21,    78,    74,    24,    25,    82,    83,    84,    85,    85,
     114,    32,    33,    31,    32,    93,     6,     7,     8,    40,
       0,   110,    88,   112,    33,     5,    40,     1,    37,     3,
       4,    30,     6,     7,     8,   124,   125,   114,    12,   111,
      26,    25,    16,    27,    35,    36,    20,    21,     9,    10,
      24,    25,    25,    20,    27,    29,    30,    40,    32,    33,
      32,    25,    25,    25,    32,    25,    40,    41,     1,    38,
       3,     4,    28,     6,     7,     8,    34,    27,    32,    12,
      26,    40,    20,    16,    26,    40,    26,    20,    21,    26,
      31,    24,    25,    28,    33,    27,    29,    26,    28,    32,
      33,    32,    11,    26,    40,     5,    82,    40,    41,    84,
      -1,    -1,    83
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,     8,    44,    45,    46,    47,    48,    49,
      51,    52,    56,    57,     0,    46,    29,    32,    54,    32,
      54,    25,    40,    58,    30,    55,    26,    50,    27,     1,
      31,    32,     1,     3,     4,    12,    16,    20,    21,    24,
      25,    32,    33,    40,    41,    47,    48,    54,    56,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      53,    57,    20,    40,    32,    25,    25,    25,    63,    62,
      68,    63,    68,    25,    27,    25,    30,    60,    23,    35,
      36,    32,    38,    33,    37,    34,     1,    26,    31,    40,
      28,    27,    63,    61,    63,    32,    26,    64,    70,    71,
      63,    40,    62,    64,    65,    67,    66,    68,    57,    20,
      26,    61,    26,    26,    31,    28,    26,    40,    28,    60,
      63,    60,    64,    32,    11,    26,    60,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    47,    47,
      48,    48,    50,    49,    51,    52,    53,    53,    53,    53,
      53,    55,    54,    54,    56,    57,    57,    57,    58,    58,
      58,    58,    58,    59,    59,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    61,    61,    61,    62,
      62,    63,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    68,    68,    68,    69,    69,    69,    69,    69,    69,
      69,    70,    70,    71,    71
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       2,     2,     0,     5,     3,     2,     4,     3,     2,     1,
       2,     0,     4,     2,     3,     1,     1,     1,     3,     6,
       1,     4,     2,     1,     2,     1,     1,     1,     1,     1,
       7,     5,     7,     5,     5,     3,     1,     2,     2,     1,
       4,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     2,     2,     1,     1,     4,     3,     1,     1,     2,
       2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 97 "parser.y"
        {
		yyval = new TokenAST(NodeType::START, "program", yylineno);
		yyval->addChild(yyvsp[0]); 

		logout << "start : program" << endl;
		yyval->print(treeout);
		delete yyval;

		logout << "Total Lines: " << yylineno << endl;
		logout << "Total Errors: " << printUtil.getErrorCount() << endl;
	}
#line 1524 "parser.tab.c"
    break;

  case 3:
#line 111 "parser.y"
                {
			yyval = new TokenAST(NodeType::PROGRAM, "program unit", yylineno);
			yyval->addChild({yyvsp[-1], yyvsp[0]});

			logout << "program : program unit" << endl;
		}
#line 1535 "parser.tab.c"
    break;

  case 4:
#line 118 "parser.y"
                {
			yyval = new TokenAST(NodeType::PROGRAM, "unit", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "program : unit" << endl;
		}
#line 1546 "parser.tab.c"
    break;

  case 5:
#line 127 "parser.y"
        {
        yyval = new TokenAST(NodeType::UNIT, "var_declaration", yylineno);
		yyval->addChild(yyvsp[0]);

		logout << "unit : var_declaration" << endl;
	}
#line 1557 "parser.tab.c"
    break;

  case 6:
#line 134 "parser.y"
        {
        yyval = new TokenAST(NodeType::UNIT, "func_declaration", yylineno);
		yyval->addChild(yyvsp[0]);
		
		logout << "unit : func_declaration" << endl;
	}
#line 1568 "parser.tab.c"
    break;

  case 7:
#line 141 "parser.y"
        {
        yyval = new TokenAST(NodeType::UNIT, "func_definition", yylineno);
		yyval->addChild(yyvsp[0]);
		
		logout << "unit : func_definition" << endl;
	}
#line 1579 "parser.tab.c"
    break;

  case 8:
#line 150 "parser.y"
                        {
				// TODO : Function redeclaration checking
				yyval = new TokenAST(NodeType::FUNC_DECL, "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", yylineno);
				yyval->addChild(yyvsp[-1]->getChilds());	

				yyvsp[-1]->removeAllChild();
				delete yyvsp[-1];

				yyval->addChild(yyvsp[0]);
		
				
				auto funcName = treeWalker.walkID(yyval->getChilds()[1]);
				auto id = symbolTable.lookup(funcName);
				auto funcId = dynamic_cast<FunctionSymbolInfo *> (id);
				if(funcDeclared.count(funcId) || funcDefined.count(funcId)){
					printUtil.printError("redeclaration of function", "",yylineno);
				}
				else funcDeclared.insert(funcId);

			
				symbolTable.exitScope();
				// symbolTable.decreaseScopeCount(1);

				logout << "func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON" << endl;
			}
#line 1609 "parser.tab.c"
    break;

  case 9:
#line 176 "parser.y"
                        {
				yyval = new TokenAST(NodeType::FUNC_DECL, "type_specifier ID LPAREN RPAREN SEMICOLON", yylineno);
				yyval->addChild(yyvsp[-1]->getChilds());	

				yyvsp[-1]->removeAllChild();
				delete yyvsp[-1];

				yyval->addChild(yyvsp[0]);
				symbolTable.exitScope();
				// symbolTable.decreaseScopeCount(1);
				
				auto funcName = treeWalker.walkID(yyval->getChilds()[1]);
				auto id = symbolTable.lookup(funcName);
				auto funcId = dynamic_cast<FunctionSymbolInfo *> (id);
				if(funcDeclared.count(funcId) || funcDefined.count(funcId)){
					printUtil.printError("redeclaration of function", "",yylineno);
				}
				else funcDeclared.insert(funcId);

				logout << "func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON" << endl;
			}
#line 1635 "parser.tab.c"
    break;

  case 10:
#line 200 "parser.y"
                        {
				yyval = new TokenAST(NodeType::FUNC_DEF, "type_specifier ID LPAREN parameter_list RPAREN compound_statement", yylineno);
				yyval->addChild(yyvsp[-1]->getChilds());

				yyvsp[-1]->removeAllChild();
				delete yyvsp[-1];

				yyval->addChild(yyvsp[0]);

				// logout << symbolTable;
				// symbolTable.exitScope();
				
				
				auto types = treeWalker.walkParameterList(yyval->getChilds()[3]);
				auto funcName = treeWalker.walkID(yyval->getChilds()[1]);
				auto id = symbolTable.lookup(funcName);
				auto funcId = dynamic_cast<FunctionSymbolInfo *> (id);

				if(funcDefined.count(funcId)){
					printUtil.printError("redefination of function", "",yylineno);
				}
				else if(funcDeclared.count(funcId) && !funcId->matchParam(types)){
					printUtil.printError("Conflicting types for \'" + funcName + "\'", yyval->getChilds()[1]->getBeginLine());
				}
				else {
					funcDefined.insert(funcId);
					funcDeclared.insert(funcId);
				}

				logout << "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement" << endl;
			}
#line 1671 "parser.tab.c"
    break;

  case 11:
#line 232 "parser.y"
                        {
				yyval = new TokenAST(NodeType::FUNC_DEF, "type_specifier ID LPAREN RPAREN compound_statement", yylineno);
				yyval->addChild(yyvsp[-1]->getChilds());

				yyvsp[-1]->removeAllChild();
				delete yyvsp[-1];

				yyval->addChild(yyvsp[0]);

				// logout << symbolTable;
				// symbolTable.exitScope();
				
				auto funcName = treeWalker.walkID(yyval->getChilds()[1]);
				auto id = symbolTable.lookup(funcName);
				auto funcId = dynamic_cast<FunctionSymbolInfo *> (id);
				if(funcDefined.count(funcId)){
					printUtil.printError("redefination of function", "",yylineno);
				}else if(funcDeclared.count(funcId) && !funcId->matchParam({})){
					printUtil.printError("defination doesnt match to declaration", "", yylineno);
				}else funcDeclared.insert(funcId);

				logout << "func_definition : type_specifier ID LPAREN RPAREN compound_statement" << endl;
			}
#line 1699 "parser.tab.c"
    break;

  case 12:
#line 258 "parser.y"
                                                {symbolTable.enterScope();}
#line 1705 "parser.tab.c"
    break;

  case 13:
#line 259 "parser.y"
        {
		yyval = new TokenAST(NodeType::TOKEN, "token", yylineno);

		yyval->addChild(yyvsp[-4]->getChilds());
		yyvsp[-4]->removeAllChild();
		delete yyvsp[-4];

		yyval->addChild(yyvsp[-3]);		
		yyval->addChild(yyvsp[-1]);
		yyval->addChild(yyvsp[0]);

		inFunction = true;

		// setting parameter list the function
		auto types = treeWalker.walkParameterList(yyvsp[-1]);
		auto funcName = treeWalker.walkID(yyval->getChilds()[1]);
		auto id = symbolTable.lookup(funcName);
		auto funcId = dynamic_cast<FunctionSymbolInfo *> (id);
		if(funcId != nullptr && !funcDeclared.count(funcId)){
			funcId->setParam(types);
		}
	}
#line 1732 "parser.tab.c"
    break;

  case 14:
#line 283 "parser.y"
        {
		yyval = new TokenAST(NodeType::TOKEN, "token", yylineno);
		
		yyval->addChild(yyvsp[-2]->getChilds());
		yyvsp[-2]->removeAllChild();
		delete yyvsp[-2];

		yyval->addChild(yyvsp[-1]);		
		yyval->addChild(yyvsp[0]);

		inFunction = true;
		symbolTable.enterScope();
	}
#line 1750 "parser.tab.c"
    break;

  case 15:
#line 299 "parser.y"
        {
		yyval = new TokenAST(NodeType::TOKEN, "token", yylineno);
		yyval->addChild({yyvsp[-1], yyvsp[0]});

		auto type = treeWalker.walkTypeSpecifier(yyvsp[-1]);
		auto name = treeWalker.walkID(yyvsp[0]);
		auto symbol = new FunctionSymbolInfo(name, type, {});
		auto isInserted = symbolTable.insert(symbol);

		if(!isInserted){
			auto prev = symbolTable.lookup(name);
			if(prev->getType() == "FUNCTION"){
				auto t = dynamic_cast<FunctionSymbolInfo *> (prev);
				if(t->getReturnType() != type){
					printUtil.printError("Conflicting types for \'" + name + "\'" , yylineno);
				}
			}else{
				printUtil.printError("\'" + name + "\' redeclared as different kind of symbol", yylineno);
			}

			delete symbol;
		}

		// cout << symbolTable << endl;
	}
#line 1780 "parser.tab.c"
    break;

  case 16:
#line 327 "parser.y"
                        {
				yyval = new TokenAST(NodeType::PARAM_LIST, "parameter_list COMMA type_specifier ID", yylineno);
				yyval->addChild({yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]});
				
				auto type = treeWalker.walkTypeSpecifier(yyvsp[-1]);
				auto symbolAST = dynamic_cast<SymbolAST *>(yyvsp[0]);
				auto newSymbl = new SymbolInfo(symbolAST->getSymbol()->getName(), type);
				auto isInserted = symbolTable.insert(newSymbl);
				if(!isInserted){
					printUtil.printError("Redefinition of parameter \'" + newSymbl->getName() + "\'", symbolAST->getBeginLine());
					delete newSymbl;
				}

				// cout << symbolTable << endl;


				logout << "parameter_list : parameter_list COMMA type_specifier ID" << endl;
			}
#line 1803 "parser.tab.c"
    break;

  case 17:
#line 346 "parser.y"
                        {
				yyval = new TokenAST(NodeType::PARAM_LIST, "parameter_list COMMA type_specifier", yylineno);
				yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});

				logout << "parameter_list: parameter_list COMMA type_specifier" << endl;
			}
#line 1814 "parser.tab.c"
    break;

  case 18:
#line 353 "parser.y"
                        {
				yyval = new TokenAST(NodeType::PARAM_LIST, "type_specifier ID", yylineno);
				yyval->addChild({yyvsp[-1], yyvsp[0]});

				auto type = treeWalker.walkTypeSpecifier(yyvsp[-1]);
				auto symbolAST = dynamic_cast<SymbolAST *>(yyvsp[0]);
				auto newSymbl = new SymbolInfo(symbolAST->getSymbol()->getName(), type);
				auto isInserted = symbolTable.insert(newSymbl);
				if(!isInserted){
					printUtil.printError("redefination of parameter \'" + newSymbl->getName() + "\'", "", symbolAST->getBeginLine());
					delete newSymbl;
				}

				// cout << symbolTable << endl;

				logout << "parameter_list : type_specifier ID" << endl;
			}
#line 1836 "parser.tab.c"
    break;

  case 19:
#line 371 "parser.y"
                        {
				yyval = new TokenAST(NodeType::PARAM_LIST, "type_specifier", yylineno);
				yyval->addChild(yyvsp[0]);

				logout << "parameter_list : type_specifier" << endl;
			}
#line 1847 "parser.tab.c"
    break;

  case 20:
#line 378 "parser.y"
                        {
				yyval = new TokenAST(NodeType::PARAM_LIST, "parameter_list error", yylineno);

				delete yyvsp[0];
				yyvsp[0] = new TokenAST(NodeType::PARAM_LIST, "error", yylineno);
				yyval->addChild({yyvsp[-1], yyvsp[0]});

				yyclearin;
				
				printUtil.printError("Syntax error at parameter list of function definition", "", yylineno);
			}
#line 1863 "parser.tab.c"
    break;

  case 21:
#line 392 "parser.y"
                           {
		if(!inFunction)
			symbolTable.enterScope();
		inFunction = false;
	}
#line 1873 "parser.tab.c"
    break;

  case 22:
#line 397 "parser.y"
                        {
				yyval = new TokenAST(NodeType::COMPOUND_STATEMENT, "LCURL statement RCURL", yylineno);
				yyval->addChild({yyvsp[-3], yyvsp[-1], yyvsp[0]});

				logout << "compound_statement: LCURL statements RCURL" << endl;
				logout << symbolTable;
				symbolTable.exitScope();

			}
#line 1887 "parser.tab.c"
    break;

  case 23:
#line 407 "parser.y"
                        {
				yyval = new TokenAST(NodeType::COMPOUND_STATEMENT, "LCURL RCURL", yylineno);
				yyval->addChild({yyvsp[-1], yyvsp[0]});

				logout << "compound_statement : LCURL RCURL" << endl;	

			}
#line 1899 "parser.tab.c"
    break;

  case 24:
#line 418 "parser.y"
                {	
			yyval = new TokenAST(NodeType::VAR_DECL, "type_specifier declaration_list SEMICOLON", yylineno);
			yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});

			auto symbols = treeWalker.walkDeclarationList(yyvsp[-1]);
			auto type = treeWalker.walkTypeSpecifier(yyvsp[-2]);

			if(type == "VOID"){
				for(auto symbol: symbols){
					printUtil.printError("Variable or field \'" + symbol->getSymbol()->getName()  + "\' declared void", yylineno);
					delete symbol;
				}

				symbols.clear();
			}

			for(int ii = symbols.size()-1; ii >= 0; ii--){
				auto symbol = symbols[ii];

				auto i = symbol->getSymbol();
        		i->setType(type);
				auto isInserted = symbolTable.insert(i);

				if(!isInserted){
					printUtil.printError("Conflicting types for\'" + i->getName() + "\'", symbol->getBeginLine());
					delete i;
				}

				symbol->setSymbol(nullptr);
				delete symbol;
			}

			// cout << symbolTable << endl;

			logout << "var_declaration : type_specifier declaration_list SEMICOLON" << endl;
		}
#line 1940 "parser.tab.c"
    break;

  case 25:
#line 457 "parser.y"
        {
		yyval = new TokenAST(NodeType::TYPE_SPECIFIER, "INT", yylineno);
		yyval->addChild(yyvsp[0]);

		logout << "type_specifier : INT" << endl;
	}
#line 1951 "parser.tab.c"
    break;

  case 26:
#line 464 "parser.y"
        {
		yyval = new TokenAST(NodeType::TYPE_SPECIFIER, "FLOAT", yylineno);
		yyval->addChild(yyvsp[0]);

		logout << "type_specifier : FLOAT" << endl;
	}
#line 1962 "parser.tab.c"
    break;

  case 27:
#line 471 "parser.y"
        {
		yyval = new TokenAST(NodeType::TYPE_SPECIFIER, "VOID", yylineno);
		yyval->addChild(yyvsp[0]);

		logout << "type_specifier : VOID" << endl;
	}
#line 1973 "parser.tab.c"
    break;

  case 28:
#line 480 "parser.y"
                        {
				yyval = new TokenAST(NodeType::DECL_LIST, "declaration_list COMMA ID", yylineno);
				yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});

				logout << "declaration_list : declaration_list COMMA ID" << endl;
			}
#line 1984 "parser.tab.c"
    break;

  case 29:
#line 487 "parser.y"
                  {
			yyval = new TokenAST(NodeType::DECL_LIST, "declaration_list COMMA ID LSQUARE CONST_INT RSQUARE", yylineno);
			yyval->addChild({yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]});

 		  	logout << "declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE" << endl;
		  }
#line 1995 "parser.tab.c"
    break;

  case 30:
#line 494 "parser.y"
                  {
			yyval = new TokenAST(NodeType::DECL_LIST, "ID", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "declaration_list : ID" << endl;
		  }
#line 2006 "parser.tab.c"
    break;

  case 31:
#line 501 "parser.y"
                  {
			yyval = new TokenAST(NodeType::DECL_LIST, "ID LSQUARE CONST_INT RSQUARE", yylineno);
			yyval->addChild({yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]});

			logout << "declaration_list : ID LSQUARE CONST_INT RSQUARE" << endl;
		  }
#line 2017 "parser.tab.c"
    break;

  case 32:
#line 508 "parser.y"
                  {
			yyval =  new TokenAST(NodeType::DECL_LIST, "error", yylineno);
			yyclearin;

			delete yyvsp[0];
			delete yyvsp[-1];

			printUtil.printError("Syntax error at declaration list of variable declaration", "", yylineno);
		  }
#line 2031 "parser.tab.c"
    break;

  case 33:
#line 520 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENTS, "statement", yylineno);
			yyval->addChild(yyvsp[0]);		

			logout << "statements : statement" << endl;
		}
#line 2042 "parser.tab.c"
    break;

  case 34:
#line 527 "parser.y"
           {
			yyval = new TokenAST(NodeType::STATEMENTS, "statements statement", yylineno);
			yyval->addChild({yyvsp[-1], yyvsp[0]});

			logout << "statements : statements statement" << endl;
	   }
#line 2053 "parser.tab.c"
    break;

  case 35:
#line 536 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "var_declaration", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "statemenparameter_listt : var_declaration" << endl;
		}
#line 2064 "parser.tab.c"
    break;

  case 36:
#line 543 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "error", yylineno);

			printUtil.printError("Nested function declaration is not allowed", yylineno);
		}
#line 2074 "parser.tab.c"
    break;

  case 37:
#line 549 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "error", yylineno);

			printUtil.printError("Nested function definition is not allowed", yylineno);
		}
#line 2084 "parser.tab.c"
    break;

  case 38:
#line 556 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "expression_statement", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "statement : expression_statement" << endl;
		}
#line 2095 "parser.tab.c"
    break;

  case 39:
#line 563 "parser.y"
          {
			yyval = new TokenAST(NodeType::STATEMENT, "compound_statement", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "statement : compound_statement" << endl;

	  }
#line 2107 "parser.tab.c"
    break;

  case 40:
#line 571 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "FOR LPAREN expression_statement expression_statement expression RPAREN statement", yylineno);
			yyval->addChild({yyvsp[-6], yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]});

			errorIfVoid(yyvsp[-4]->getChilds()[0]);
			errorIfVoid(yyvsp[-3]->getChilds()[0]);
			errorIfVoid(yyvsp[-2]);

			logout << "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement" << endl;
		}
#line 2122 "parser.tab.c"
    break;

  case 41:
#line 582 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "IF LPAREN expression RPAREN statement", yylineno);
			yyval->addChild({yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]});

			errorIfVoid(yyvsp[-2]);

			logout << "statement : IF LPAREN expression RPAREN statement" << endl;
		}
#line 2135 "parser.tab.c"
    break;

  case 42:
#line 591 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "IF LPAREN expression RPAREN statement ELSE statement", yylineno);
			yyval->addChild({yyvsp[-6], yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]});

			errorIfVoid(yyvsp[-4]);

			logout << "statement : IF LPAREN expression RPAREN statement ELSE statement" << endl;
		}
#line 2148 "parser.tab.c"
    break;

  case 43:
#line 601 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "WHILE LPAREN expression RPAREN statement", yylineno);
			yyval->addChild({yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]});

			errorIfVoid(yyvsp[-2]);

			logout << "statement : WHILE LPAREN expression RPAREN statement" << endl;
		}
#line 2161 "parser.tab.c"
    break;

  case 44:
#line 610 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "PRINTLN LPAREN ID RPAREN SEMICOLON", yylineno);
			yyval->addChild({yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]});

			logout << "statement: PRINTLN LPAREN ID RPAREN SEMICOLON";
		}
#line 2172 "parser.tab.c"
    break;

  case 45:
#line 617 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "RETURN expression SEMICOLON", yylineno);
			yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});

			errorIfVoid(yyvsp[-1]);
			
			logout << "statement : RETURN expression SEMICOLON" << endl;
		}
#line 2185 "parser.tab.c"
    break;

  case 46:
#line 628 "parser.y"
                        {
				yyval = new TokenAST(NodeType::EXPR_STMNT, "SEMICOLON", yylineno);
				yyval->addChild(yyvsp[0]);

				logout << "expression_statement : SEMICOLON" << endl;
			}
#line 2196 "parser.tab.c"
    break;

  case 47:
#line 635 "parser.y"
                        {
				yyval = new TokenAST(NodeType::EXPR_STMNT, "expression SEMICOLON", yylineno);
				yyval->addChild({yyvsp[-1], yyvsp[0]});

				logout << "expression_statement : expression SEMICOLON" << endl;
			}
#line 2207 "parser.tab.c"
    break;

  case 48:
#line 642 "parser.y"
                {
			yyval = new TokenAST(NodeType::EXPR_STMNT, "expression SEMICOLON", yylineno);
			delete yyvsp[-1];
			yyvsp[-1] = new TokenAST(NodeType::EXP, "error", yylineno);
			yyval->addChild({yyvsp[-1], yyvsp[0]});


			printUtil.printError("Syntax error at expression of expression statement", yylineno);
		}
#line 2221 "parser.tab.c"
    break;

  case 49:
#line 654 "parser.y"
                {
			auto symbol = getSymbol(yyvsp[0]);
			string type = "INT";
			if(symbol == nullptr){
				printUtil.printError("Undeclared variable \'" + treeWalker.walkID(yyvsp[0]) + "\'", yylineno);
			}else if(symbol->getType() == "FUNCTION"){
				printUtil.printError("Function cannot used as variable", yylineno);
			}else if(dynamic_cast<VariableSymbolInfo *>(symbol) != nullptr){
				// printUtil.printError("array used as normal variable", yylineno);
				printUtil.printError("\'" + symbol->getName() + "\' is an array", yylineno);
				type = symbol->getType();
			}else{
				type = symbol->getType();
			}
			
			yyval = new ExpressionAST(NodeType::VARIABLE, "ID", type, yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "variable : ID" << endl;
		}
#line 2246 "parser.tab.c"
    break;

  case 50:
#line 675 "parser.y"
                {
			auto symbol = getSymbol(yyvsp[-3]);
			string type = "INT";
			if(symbol == nullptr){
				printUtil.printError("Undeclared variable \'" + treeWalker.walkID(yyvsp[-3]) + "\'", yylineno);
			}else if(symbol->getType() == "FUNCTION"){
				printUtil.printError("function cannot used as variable", "", yylineno);
			}else if( dynamic_cast<VariableSymbolInfo *>(symbol) == nullptr){
				printUtil.printError("\'" + symbol->getName() + "\' is not an array", yylineno);
				type = symbol->getType();
			}else{
				type = symbol->getType();
			}

			if(getDataType(yyvsp[-1]) != "INT"){
				printUtil.printError("Array subscript is not an integer", yylineno);
			}
			
			yyval = new ExpressionAST(NodeType::VARIABLE, "ID LSQUARE expression RSQUARE", type, yylineno);
			yyval->addChild({yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]});

			logout << "variable : ID LSQUARE expression RSQUARE" << endl;
		}
#line 2274 "parser.tab.c"
    break;

  case 51:
#line 701 "parser.y"
                {
			yyval = new ExpressionAST(NodeType::EXP, "logic_expression", getDataType(yyvsp[0]), yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "expression : logic_expression" << endl;
		}
#line 2285 "parser.tab.c"
    break;

  case 52:
#line 708 "parser.y"
           {
			if(getDataType(yyvsp[0]) == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
			}else if(!isAssignopCorrect(getDataType(yyvsp[-2]), getDataType(yyvsp[0]))){
				printUtil.printError("Warning: possible loss of data in assignment of FLOAT to INT", yylineno);
			}

			yyval = new ExpressionAST(NodeType::EXP, "variable ASSIGNOP logic_expression", getDataType(yyvsp[-2]), yylineno);
			yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});

			logout << "expression : variable ASSIGNOP logic_expression" << endl;
	   }
#line 2302 "parser.tab.c"
    break;

  case 53:
#line 723 "parser.y"
                {
			yyval = new ExpressionAST(NodeType::LOGIC_EXP, "rel_expression", getDataType(yyvsp[0]), yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "logic_expression : rel_expression" << endl;
		}
#line 2313 "parser.tab.c"
    break;

  case 54:
#line 730 "parser.y"
                {
			auto lhsType = getDataType(yyvsp[-2]);
			auto rhsType = getDataType(yyvsp[0]);

			if(lhsType == "VOID" || rhsType == "VOID"){
				printUtil.printError("Void cannot be used in expression",  yylineno);
				if(lhsType == "VOID") lhsType = "INT";
				if(rhsType == "VOID") rhsType = "INT";
			}

			yyval = new ExpressionAST(NodeType::LOGIC_EXP, "rel_expression LOGICOP rel_expression", "INT", yylineno);
			yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});

			logout << "logic_expression : rel_expression LOGICOP rel_expression" << endl;
		}
#line 2333 "parser.tab.c"
    break;

  case 55:
#line 748 "parser.y"
                {
			yyval = new ExpressionAST(NodeType::REL_EXP, "simple_expression", getDataType(yyvsp[0]), yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "rel_expression : simple_expression" << endl;
		}
#line 2344 "parser.tab.c"
    break;

  case 56:
#line 755 "parser.y"
                {
			auto lhsType = getDataType(yyvsp[-2]);
			auto rhsType = getDataType(yyvsp[0]);

			if(lhsType == "VOID" || rhsType == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
				if(lhsType == "VOID") lhsType = "INT";
				if(rhsType == "VOID") rhsType = "INT";
			}

			yyval = new ExpressionAST(NodeType::REL_EXP, "simple_expression RELOP simple_expression", "INT", yylineno);
			yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});

			logout << "rel_expression : simple_expression RELOP simple_expression" << endl;
		}
#line 2364 "parser.tab.c"
    break;

  case 57:
#line 773 "parser.y"
                {
			yyval = new ExpressionAST(NodeType::SIMPLE_EXP, "term", getDataType(yyvsp[0]), yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "simple_expression : term" << endl;
		}
#line 2375 "parser.tab.c"
    break;

  case 58:
#line 780 "parser.y"
                {
			auto lhsType = getDataType(yyvsp[-2]);
			auto rhsType = getDataType(yyvsp[0]);

			if(lhsType == "VOID" || rhsType == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
				if(lhsType == "VOID") lhsType = "INT";
				if(rhsType == "VOID") rhsType = "INT";
			}

			auto type = getAddopType(lhsType, rhsType);

			yyval = new ExpressionAST(NodeType::SIMPLE_EXP, "simple_expression ADDOP term", type, yylineno);
			yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});
			
			logout << "simple_expression : simple_expression ADDOP term" << endl;
		}
#line 2397 "parser.tab.c"
    break;

  case 59:
#line 801 "parser.y"
                {
			yyval = new ExpressionAST(NodeType::TERM, "unary_expression", getDataType(yyvsp[0]), yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "term : unary_expression" << endl;
		}
#line 2408 "parser.tab.c"
    break;

  case 60:
#line 808 "parser.y"
                {
			auto lhsType = getDataType(yyvsp[-2]);
			auto rhsType = getDataType(yyvsp[0]);

			if(lhsType == "VOID" || rhsType == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
				if(lhsType == "VOID") lhsType = "INT";
				if(rhsType == "VOID") rhsType = "INT";
			}

			auto type = getAddopType(lhsType, rhsType);
			auto opType = treeWalker.walkID(yyvsp[-1]);
			if(opType == "%"){
				if(lhsType != "INT" || rhsType != "INT"){
					printUtil.printError("Operands of modulus must be integers", yylineno);
				}
				type = "INT";
			}

			int value = treeWalker.walkUnaryExpressionValue(yyvsp[0]);
			if(opType == "%" || opType == "/"){
				if(value == 0){
					printUtil.printError("Warning: division by zero i=0f=1Const=0", yylineno);
				}				
			}

			yyval = new ExpressionAST(NodeType::TERM, "term MULOP unary_expression", type, yylineno);
			yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});

			logout << "term : term MULOP unary_expression" << endl;
		}
#line 2444 "parser.tab.c"
    break;

  case 61:
#line 842 "parser.y"
                {
			auto type = getDataType(yyvsp[0]);
			if(type == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
				type = "INT";
			}

			yyval = new ExpressionAST(NodeType::UNARY_EXP, "ADDOP unary_expression", type, yylineno);
			yyval->addChild({yyvsp[-1], yyvsp[0]});

			logout << "unary_expression : ADDOP unary_expression" << endl;
		}
#line 2461 "parser.tab.c"
    break;

  case 62:
#line 855 "parser.y"
                {
			auto type = getDataType(yyvsp[0]);
			if(type == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
				type = "INT";
			}

			yyval = new ExpressionAST(NodeType::UNARY_EXP, "NOT unary_expression", "INT", yylineno);
			yyval->addChild({yyvsp[-1], yyvsp[0]});

			logout << "NOT unary_expression" << endl;
		}
#line 2478 "parser.tab.c"
    break;

  case 63:
#line 868 "parser.y"
                {
			yyval = new ExpressionAST(NodeType::UNARY_EXP, "factor", getDataType(yyvsp[0]), yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "unary_expression : factor" << endl;
		}
#line 2489 "parser.tab.c"
    break;

  case 64:
#line 877 "parser.y"
                {
			yyval = new ExpressionAST(NodeType::FACTOR, "variable", getDataType(yyvsp[0]), yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "factor : variable" << endl;
		}
#line 2500 "parser.tab.c"
    break;

  case 65:
#line 885 "parser.y"
                {
			auto name = treeWalker.walkID(yyvsp[-3]);
			auto symbol = symbolTable.lookup(name);
			auto arguments = treeWalker.walkArgumentList(yyvsp[-1]);
			string type = "INT";

			if(symbol == nullptr){
				printUtil.printError("Undeclared function '" + name + "'", yylineno);
			}else if(symbol->getType() != "FUNCTION"){
				printUtil.printError("'" + name + "'' is not a function", "", yylineno);
			}else{
				auto functionSymbol = dynamic_cast<FunctionSymbolInfo *>(symbol);

				vector<int> errors;	
				if(!functionSymbol->matchParam(arguments, errors)){
					if(errors.size() == 0){
						if(functionSymbol->getNoParam() > arguments.size()){
							printUtil.printError("Too few arguments to function \'" + name + "\'", yylineno);
						}
						else{
							printUtil.printError("Too many arguments to function \'" + name + "\'", yylineno);
						}
					}
					else{
						for(auto i : errors){
							printUtil.printError(string("Type mismatch for argument ") + to_string(i) + string(" of \'") + name + "\'", yylineno);
						}
					}
				}else{
					type = functionSymbol->getReturnType();
				}
			}

			yyval = new ExpressionAST(NodeType::FACTOR, "ID LPAREN argument_list RPAREN", type, yylineno);
			yyval->addChild({yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]});

			logout << "factor : ID LPAREN argument_list RPAREN" << endl;
		}
#line 2543 "parser.tab.c"
    break;

  case 66:
#line 924 "parser.y"
                {
			yyval = new ExpressionAST(NodeType::FACTOR, "LPAREN expression RPAREN", getDataType(yyvsp[-1]), yylineno);
			yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});

			logout << "factor : LPAREN expression RPAREN" << endl;
		}
#line 2554 "parser.tab.c"
    break;

  case 67:
#line 931 "parser.y"
                {
			yyval = new ExpressionAST(NodeType::FACTOR, "CONST_INT", "INT", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "factor : CONST_INT" << endl;
		}
#line 2565 "parser.tab.c"
    break;

  case 68:
#line 938 "parser.y"
                {
			yyval = new ExpressionAST(NodeType::FACTOR, "CONST_FLOAT", "FLOAT", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "factor : CONST_FLOAT" << endl;
		}
#line 2576 "parser.tab.c"
    break;

  case 69:
#line 945 "parser.y"
                {
			auto type = getDataType(yyvsp[-1]);
			if(type == "VOID"){
				printUtil.printError("void function cannot be used in expression", "", yylineno);
				type = "INT";
			}

			yyval = new ExpressionAST(NodeType::FACTOR, "variable INCOP", type, yylineno);
			yyval->addChild({yyvsp[-1], yyvsp[0]});

			logout << "factor : variable INCOP" << endl;
		}
#line 2593 "parser.tab.c"
    break;

  case 70:
#line 959 "parser.y"
                {
			auto type = getDataType(yyvsp[-1]);
			if(type == "VOID"){
				printUtil.printError("void function cannot be used in expression", "", yylineno);
				type = "INT";
			}

			yyval = new ExpressionAST(NodeType::FACTOR, "variable DECOP", type, yylineno);
			yyval->addChild({yyvsp[-1], yyvsp[0]});

			logout << "factor : variable DECOP" << endl;
		}
#line 2610 "parser.tab.c"
    break;

  case 71:
#line 974 "parser.y"
                {
			yyval = new TokenAST(NodeType::ARG_LIST, "arguments", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "argument_list : arguments" << endl;
		}
#line 2621 "parser.tab.c"
    break;

  case 72:
#line 981 "parser.y"
                {
			yyval = new TokenAST(NodeType::ARG_LIST, "", yylineno);
			logout << "argument_list : " << endl;
		}
#line 2630 "parser.tab.c"
    break;

  case 73:
#line 988 "parser.y"
                {
			yyval = new TokenAST(NodeType::ARGS, "arguments COMMA logic_expression", yylineno);
			yyval->addChild({yyvsp[-2], yyvsp[-1], yyvsp[0]});

			logout << "arguments : arguments COMMA logic_expression" << endl;
		}
#line 2641 "parser.tab.c"
    break;

  case 74:
#line 995 "parser.y"
                {
			yyval = new TokenAST(NodeType::ARGS, "logic_expression", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "arguments : logic_expression" << endl;
		}
#line 2652 "parser.tab.c"
    break;


#line 2656 "parser.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 1003 "parser.y"

int main(int argc,char *argv[])
{
	auto fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	yyin=fp;
	yyparse();
	
	fclose(fp);
	
	return 0;
}

