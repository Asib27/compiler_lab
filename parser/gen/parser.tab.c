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
#include<cstdlib>
#include<cstring>
#include<cmath>
#include"lib/symbolTable.h"
#include "lib/symbolInfo.h"
#include "lib/ast.h"

using namespace std;

int yyparse(void);
int yylex(void);

extern FILE *yyin;
extern int yylineno;

ofstream logout("log.txt"), tokenout("token.txt");
// PrintUtil printUtil(tokenout, logout);
Printer printer(logout, true), noPrint(cout, false);
SymbolTable symbolTable(10, &printer), constTable(10, &noPrint);
SymbolInfo *curSymbol = nullptr;


void yyerror(char *s)
{
	//write your code
}

SymbolInfo int_symbol("int", "INT"), float_symbol("float", "FLOAT"),
		   void_symbol("void", "VOID"), lthird_symbol("[", "LTHIRD"),
		   rthird_symbol("]", "RTHIRD")
;

SymbolInfo* getSymbol(string name, string type){
	auto t = constTable.lookup(name);
	if(t == nullptr){
		SymbolInfo s(name, type);
		t = constTable.insert(s);
	}

	return t;
}



#line 118 "parser.tab.c"

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
#line 53 "parser.y"

	#include "lib/ast.h"

#line 165 "parser.tab.c"

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   176

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  125

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
       0,    72,    72,    82,    90,    99,   106,   113,   122,   142,
     162,   181,   201,   215,   228,   236,   246,   261,   276,   289,
     296,   305,   316,   326,   340,   347,   364,   372,   380,   386,
     393,   400,   407,   411,   418,   428,   435,   442,   450,   472,
     491,   516,   535,   553,   569,   578,   591,   598,   615,   622,
     636,   643,   654,   661,   672,   679,   691,   698,   709,   717,
     728,   737,   745,   760,   774,   781,   788,   799,   811,   819,
     825,   838
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
  "func_definition", "parameter_list", "compound_statement",
  "var_declaration", "type_specifier", "declaration_list", "int_const",
  "float_const", "addop", "logicop", "mulop", "relop", "identifier",
  "statements", "statement", "expression_statement", "variable",
  "expression", "logic_expression", "rel_expression", "simple_expression",
  "term", "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
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

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      76,   -69,   -69,   -69,     7,    76,   -69,   -69,   -69,   -69,
     -27,   -69,   -69,   -69,     5,    61,   -27,   -69,    47,     3,
      45,    16,    34,   -27,   -69,    50,     3,    73,   -69,   -69,
      39,    76,   -69,   -69,    59,    31,    66,    70,     1,   -69,
       1,     1,   -69,   -69,   -69,    71,   -69,   -69,   -27,   -69,
     -69,     1,    65,   104,   -69,   -69,    -7,    67,   -69,    62,
      29,    75,   -69,   -69,   -69,   -69,   -27,   -69,     1,   129,
       1,    69,    28,   -69,    78,   -27,    88,   -69,     1,     1,
     -69,   -69,     1,   -69,   -69,   -69,   -69,     1,   -69,     1,
       1,   -69,     1,   -69,    91,   129,    92,   -69,   -69,    93,
     -69,    95,    96,    94,   -69,   -69,    75,    90,   -69,   135,
       1,   135,    98,   -69,     1,   -69,   115,   105,   -69,   -69,
     -69,   135,   135,   -69,   -69
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    19,    20,    21,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    32,     0,    24,     0,    18,     0,     0,
      22,     0,     0,    15,    26,     0,     0,     0,     9,    11,
       0,     0,    14,    25,     0,     0,     0,     0,     0,    27,
       0,     0,    17,    44,    28,     0,    37,    35,     0,    64,
      65,     0,    46,     0,    33,    36,    61,     0,    48,    50,
      52,    54,    56,    60,     8,    10,    13,    23,     0,     0,
       0,     0,    61,    59,     0,     0,    24,    58,    69,     0,
      16,    34,     0,    66,    67,    45,    29,     0,    31,     0,
       0,    30,     0,    12,     0,     0,     0,    43,    63,     0,
      71,     0,    68,     0,    49,    51,    55,    53,    57,     0,
       0,     0,     0,    62,     0,    47,    39,     0,    41,    42,
      70,     0,     0,    40,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,   -69,   127,   -69,   -69,   -69,    -3,    19,    12,
     -69,    13,   -69,   -56,   -69,   -69,   -69,    -8,   -69,   -52,
     -64,   -40,   -35,   -68,    48,    56,    51,   -31,   -69,   -69,
     -69
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    22,    46,    47,    48,
      14,    49,    50,    51,    87,    92,    90,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,   101,
     102
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      72,    81,    15,    71,    89,    95,    74,    11,    20,    73,
     100,    72,    10,    13,   104,    32,    82,    10,    29,     9,
      77,    24,    39,    24,     9,    40,    41,    65,    83,    84,
      23,   110,    25,    94,    44,    96,    16,    17,    72,    34,
      76,    13,    72,    66,   103,    27,   120,    72,    28,    72,
      72,    89,    72,     1,     2,     3,    68,   116,    93,   118,
      30,   108,    44,    83,    84,    31,    88,    99,    27,   123,
     124,    64,    26,    21,    72,   117,    35,    36,    33,     1,
       2,     3,     1,     2,     3,    37,    18,    67,    19,    38,
      78,    69,    79,    24,    39,    70,    75,    40,    41,    85,
      86,    97,    27,    42,    98,    43,    44,    35,    36,    91,
       1,     2,     3,    13,    45,    19,    37,   109,   111,   112,
      38,   113,   115,    44,    24,    39,   121,   114,    40,    41,
     119,   122,    12,    27,    80,   105,    43,    44,    35,    36,
     106,     1,     2,     3,    13,    45,   107,    37,     0,    24,
      39,    38,     0,    40,    41,    24,    39,     0,     0,    40,
      41,    43,    44,     0,    27,     0,     0,    43,    44,    13,
       0,     0,     0,     0,     0,    13,    45
};

static const yytype_int8 yycheck[] =
{
      40,    53,    10,    38,    60,    69,    41,     0,    16,    40,
      78,    51,     0,    40,    82,    23,    23,     5,    21,     0,
      51,    20,    21,    20,     5,    24,    25,    30,    35,    36,
      18,    95,    19,    68,    33,    70,    31,    32,    78,    26,
      48,    40,    82,    31,    79,    29,   114,    87,    32,    89,
      90,   107,    92,     6,     7,     8,    25,   109,    66,   111,
      26,    92,    33,    35,    36,    31,    37,    75,    29,   121,
     122,    32,    27,    26,   114,   110,     3,     4,    28,     6,
       7,     8,     6,     7,     8,    12,    25,    28,    27,    16,
      25,    25,    27,    20,    21,    25,    25,    24,    25,    32,
      38,    32,    29,    30,    26,    32,    33,     3,     4,    34,
       6,     7,     8,    40,    41,    27,    12,    26,    26,    26,
      16,    26,    28,    33,    20,    21,    11,    31,    24,    25,
      32,    26,     5,    29,    30,    87,    32,    33,     3,     4,
      89,     6,     7,     8,    40,    41,    90,    12,    -1,    20,
      21,    16,    -1,    24,    25,    20,    21,    -1,    -1,    24,
      25,    32,    33,    -1,    29,    -1,    -1,    32,    33,    40,
      -1,    -1,    -1,    -1,    -1,    40,    41
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,     8,    44,    45,    46,    47,    48,    51,
      52,     0,    46,    40,    53,    60,    31,    32,    25,    27,
      60,    26,    49,    52,    20,    54,    27,    29,    32,    50,
      26,    31,    60,    28,    54,     3,     4,    12,    16,    21,
      24,    25,    30,    32,    33,    41,    50,    51,    52,    54,
      55,    56,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    32,    50,    52,    28,    25,    25,
      25,    65,    64,    70,    65,    25,    60,    70,    25,    27,
      30,    62,    23,    35,    36,    32,    38,    57,    37,    56,
      59,    34,    58,    60,    65,    63,    65,    32,    26,    60,
      66,    72,    73,    65,    66,    67,    69,    68,    70,    26,
      63,    26,    26,    26,    31,    28,    62,    65,    62,    32,
      66,    11,    26,    62,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    47,    47,
      48,    48,    49,    49,    49,    49,    50,    50,    51,    52,
      52,    52,    53,    53,    53,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    61,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    63,    63,    64,    64,    65,    65,
      66,    66,    67,    67,    68,    68,    69,    69,    70,    70,
      70,    71,    71,    71,    71,    71,    71,    71,    72,    72,
      73,    73
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       6,     5,     4,     3,     2,     1,     3,     2,     3,     1,
       1,     1,     3,     6,     1,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     7,     5,
       7,     5,     5,     3,     1,     2,     1,     4,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     2,     2,
       1,     1,     4,     3,     1,     1,     2,     2,     1,     0,
       3,     1
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
#line 73 "parser.y"
        {
		yyval = new TokenAST(NodeType::UNIT, "var_declaration", yylineno);
		yyval->addChild(yyvsp[0]); 

		logout << "start : program" << endl;
		yyval->print(cout);
	}
#line 1498 "parser.tab.c"
    break;

  case 3:
#line 83 "parser.y"
                {
			yyval = new TokenAST(NodeType::PROGRAM, "program unit", yylineno);
			yyval->addChild(yyvsp[-1]);
			yyval->addChild(yyvsp[0]);

			logout << "program : program unit" << endl;
		}
#line 1510 "parser.tab.c"
    break;

  case 4:
#line 91 "parser.y"
                {
			yyval = new TokenAST(NodeType::PROGRAM, "unit", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "program : unit" << endl;
		}
#line 1521 "parser.tab.c"
    break;

  case 5:
#line 100 "parser.y"
        {
        yyval = new TokenAST(NodeType::UNIT, "var_declaration", yylineno);
		yyval->addChild(yyvsp[0]);

		logout << "unit : var_declaration" << endl;
	}
#line 1532 "parser.tab.c"
    break;

  case 6:
#line 107 "parser.y"
        {
        yyval = new TokenAST(NodeType::UNIT, "func_declaration", yylineno);
		yyval->addChild(yyvsp[0]);
		
		logout << "unit : func_declaration" << endl;
	}
#line 1543 "parser.tab.c"
    break;

  case 7:
#line 114 "parser.y"
        {
        yyval = new TokenAST(NodeType::UNIT, "func_definition", yylineno);
		yyval->addChild(yyvsp[0]);
		
		logout << "unit : func_definition" << endl;
	}
#line 1554 "parser.tab.c"
    break;

  case 8:
#line 123 "parser.y"
                        {
				yyval = new TokenAST(NodeType::FUNC_DECL, "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", yylineno);

				yyval->addChild(yyvsp[-5]);
				yyval->addChild(yyvsp[-4]);

				auto t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
				yyval->addChild(t);

				yyval->addChild(yyvsp[-2]);

				t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
				yyval->addChild(t);

				t = new SymbolAST(getSymbol(";", "SEMICOLON"), yylineno);
				yyval->addChild(t);

				logout << "func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON" << endl;
			}
#line 1578 "parser.tab.c"
    break;

  case 9:
#line 143 "parser.y"
                        {
				yyval = new TokenAST(NodeType::FUNC_DECL, "type_specifier ID LPAREN RPAREN SEMICOLON", yylineno);

				yyval->addChild(yyvsp[-4]);
				yyval->addChild(yyvsp[-3]);

				auto t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
				yyval->addChild(t);

				t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
				yyval->addChild(t);

				t = new SymbolAST(getSymbol(";", "SEMICOLON"), yylineno);
				yyval->addChild(t);

				logout << "func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON" << endl;
			}
#line 1600 "parser.tab.c"
    break;

  case 10:
#line 163 "parser.y"
                        {
				yyval = new TokenAST(NodeType::FUNC_DEF, "type_specifier ID LPAREN parameter_list RPAREN compound_statement", yylineno);

				yyval->addChild(yyvsp[-5]);
				yyval->addChild(yyvsp[-4]);

				auto t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
				yyval->addChild(t);

				yyval->addChild(yyvsp[-2]);

				t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
				yyval->addChild(t);

				yyval->addChild(yyvsp[0]);				

				logout << "func_definition: type_specifier ID LPAREN parameter_list RPAREN compound_statement" << endl;
			}
#line 1623 "parser.tab.c"
    break;

  case 11:
#line 182 "parser.y"
                        {
				yyval = new TokenAST(NodeType::FUNC_DEF, "type_specifier ID LPAREN RPAREN SEMICOLON", yylineno);

				yyval->addChild(yyvsp[-4]);
				yyval->addChild(yyvsp[-3]);

				auto t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
				yyval->addChild(t);

				t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
				yyval->addChild(t);

				yyval->addChild(yyvsp[0]);

				logout << "func_definition: type_specifier ID LPAREN RPAREN compound_statement" << endl;
			}
#line 1644 "parser.tab.c"
    break;

  case 12:
#line 202 "parser.y"
                        {
				yyval = new TokenAST(NodeType::PARAM_LIST, "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", yylineno);

				yyval->addChild(yyvsp[-3]);

				auto t = new SymbolAST(getSymbol(",", "COMMA"), yylineno);
				yyval->addChild(t);

				yyval->addChild(yyvsp[-1]);
				yyval->addChild(yyvsp[0]);

				logout << "parameter_list : parameter_list COMMA type_specifier ID" << endl;
			}
#line 1662 "parser.tab.c"
    break;

  case 13:
#line 216 "parser.y"
                        {
				yyval = new TokenAST(NodeType::PARAM_LIST, "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", yylineno);

				yyval->addChild(yyvsp[-2]);

				auto t = new SymbolAST(getSymbol(",", "COMMA"), yylineno);
				yyval->addChild(t);

				yyval->addChild(yyvsp[0]);

				logout << "parameter_list: parameter_list COMMA type_specifier" << endl;
			}
#line 1679 "parser.tab.c"
    break;

  case 14:
#line 229 "parser.y"
                        {
				yyval = new TokenAST(NodeType::PARAM_LIST, "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", yylineno);
				yyval->addChild(yyvsp[-1]);
				yyval->addChild(yyvsp[0]);

				logout << "parameter_list : type_specifier ID" << endl;
			}
#line 1691 "parser.tab.c"
    break;

  case 15:
#line 237 "parser.y"
                        {
				yyval = new TokenAST(NodeType::PARAM_LIST, "type_specifier", yylineno);
				yyval->addChild(yyvsp[0]);

				logout << "parameter_list : type_specifier" << endl;
			}
#line 1702 "parser.tab.c"
    break;

  case 16:
#line 247 "parser.y"
                        {
				yyval = new TokenAST(NodeType::COMPOUND_STATEMENT, "LCURL statement RCURL", yylineno);

				auto t = new SymbolAST(getSymbol("{", "LCURL"), yylineno);
				yyval->addChild(t);

				yyval->addChild(yyvsp[-1]);

				t = new SymbolAST(getSymbol("}", "RCURL"), yylineno);
				yyval->addChild(t);

				logout << "compound_statement: LCURL statements RCURL" << endl;

			}
#line 1721 "parser.tab.c"
    break;

  case 17:
#line 262 "parser.y"
                        {
				yyval = new TokenAST(NodeType::COMPOUND_STATEMENT, "LCURL RCURL", yylineno);

				auto t = new SymbolAST(getSymbol("{", "LCURL"), yylineno);
				yyval->addChild(t);

				t = new SymbolAST(getSymbol("}", "RCURL"), yylineno);
				yyval->addChild(t);	

				logout << "compound_statement : LCURL RCURL" << endl;	

			}
#line 1738 "parser.tab.c"
    break;

  case 18:
#line 277 "parser.y"
                {	
			yyval = new TokenAST(NodeType::VAR_DECL, "type_specifier declaration_list SEMICOLON", yylineno);
			yyval->addChild(yyvsp[-2]);
			yyval->addChild(yyvsp[-1]);

			auto t = new SymbolAST(getSymbol(";", "SEMICOLON"), yylineno);
			yyval->addChild(t);

			logout << "var_declaration : type_specifier declaration_list SEMICOLON" << endl;
		}
#line 1753 "parser.tab.c"
    break;

  case 19:
#line 290 "parser.y"
        {
		yyval = new TokenAST(NodeType::TYPE_SPECIFIER, "INT", yylineno);
		yyval->addChild(yyvsp[0]);

		logout << "type_specifier : INT" << endl;
	}
#line 1764 "parser.tab.c"
    break;

  case 20:
#line 297 "parser.y"
        {
		auto s = getSymbol("float", "FLOAT");
		auto t = new SymbolAST(s, yylineno);
		yyval = new TokenAST(NodeType::TYPE_SPECIFIER, "FLOAT", yylineno);
		yyval->addChild(t);

		logout << "type_specifier : FLOAT" << endl;
	}
#line 1777 "parser.tab.c"
    break;

  case 21:
#line 306 "parser.y"
        {
		auto s = getSymbol("void", "VOID");
		auto t = new SymbolAST(s, yylineno);
		yyval = new TokenAST(NodeType::TYPE_SPECIFIER, "VOID", yylineno);
		yyval->addChild(t);

		logout << "type_specifier : VOID" << endl;
	}
#line 1790 "parser.tab.c"
    break;

  case 22:
#line 317 "parser.y"
                        {
				yyval = new TokenAST(NodeType::DECL_LIST, "declaration_list COMMA ID", yylineno);
				yyval->addChild(yyvsp[-2]);

				yyval->addChild(new SymbolAST(getSymbol(",", "COMMA"), yylineno));
				yyval->addChild(yyvsp[0]);

				logout << "declaration_list : declaration_list COMMA identifier" << endl;
			}
#line 1804 "parser.tab.c"
    break;

  case 23:
#line 327 "parser.y"
                  {
			yyval = new TokenAST(NodeType::DECL_LIST, "declaration_list COMMA ID LTHIRD CONST_INT RTHIRD", yylineno);
			yyval->addChild(yyvsp[-5]);

			yyval->addChild(new SymbolAST(getSymbol(",", "COMMA"), yylineno));
			yyval->addChild(yyvsp[-3]);

			yyval->addChild(new SymbolAST(getSymbol("[", "LTHIRD"), yylineno));
			yyval->addChild(yyvsp[-1]);
			yyval->addChild(new SymbolAST(getSymbol("]", "RTHIRD"), yylineno));

 		  	logout << "declaration_list : declaration_list COMMA identifier LTHIRD int_const RTHIRD" << endl;
		  }
#line 1822 "parser.tab.c"
    break;

  case 24:
#line 341 "parser.y"
                  {
			yyval = new TokenAST(NodeType::DECL_LIST, "ID", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "declaration_list : identifier" << endl;
		  }
#line 1833 "parser.tab.c"
    break;

  case 25:
#line 348 "parser.y"
                  {
			yyval = new TokenAST(NodeType::DECL_LIST, "ID LTHIRD CONST_INT RTHIRD", yylineno);
			yyval->addChild(yyvsp[-3]);

			auto t = new SymbolAST(getSymbol("[", "LTHIRD"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-1]);

			t = new SymbolAST(getSymbol("]", "RTHIRD"), yylineno);
			yyval->addChild(t);

			logout << "declaration_list : identifier LTHIRD CONST_INT RTHIRD" << endl;
		  }
#line 1852 "parser.tab.c"
    break;

  case 26:
#line 365 "parser.y"
                {
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			yyval = new SymbolAST(t, yylineno);
			
		}
#line 1863 "parser.tab.c"
    break;

  case 27:
#line 373 "parser.y"
                {
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			yyval = new SymbolAST(t, yylineno);
			
		}
#line 1874 "parser.tab.c"
    break;

  case 28:
#line 381 "parser.y"
                {
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			yyval = new SymbolAST(t, yylineno);	
		}
#line 1884 "parser.tab.c"
    break;

  case 29:
#line 387 "parser.y"
                {
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			yyval = new SymbolAST(t, yylineno);	
		}
#line 1894 "parser.tab.c"
    break;

  case 30:
#line 394 "parser.y"
                {
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			yyval = new SymbolAST(t, yylineno);	
		}
#line 1904 "parser.tab.c"
    break;

  case 31:
#line 401 "parser.y"
                {
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			yyval = new SymbolAST(t, yylineno);	
		}
#line 1914 "parser.tab.c"
    break;

  case 32:
#line 408 "parser.y"
                {
			yyval = new SymbolAST(curSymbol, yylineno);
		}
#line 1922 "parser.tab.c"
    break;

  case 33:
#line 412 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENTS, "statement", yylineno);
			yyval->addChild(yyvsp[0]);		

			logout << "statements : statement" << endl;
		}
#line 1933 "parser.tab.c"
    break;

  case 34:
#line 419 "parser.y"
           {
			yyval = new TokenAST(NodeType::STATEMENTS, "statements statement", yylineno);
			yyval->addChild(yyvsp[-1]);
			yyval->addChild(yyvsp[0]);

			logout << "statements : statements statement" << endl;
	   }
#line 1945 "parser.tab.c"
    break;

  case 35:
#line 429 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "var_declaration", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "statement : var_declaration" << endl;
		}
#line 1956 "parser.tab.c"
    break;

  case 36:
#line 436 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "expression_statement", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "statement : expression_statement" << endl;
		}
#line 1967 "parser.tab.c"
    break;

  case 37:
#line 443 "parser.y"
          {
			yyval = new TokenAST(NodeType::STATEMENT, "compound_statement", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "statement : compound_statement" << endl;

	  }
#line 1979 "parser.tab.c"
    break;

  case 38:
#line 451 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "FOR LPAREN expression_statement expression_statement expression RPAREN statement", yylineno);

			auto t = new SymbolAST(getSymbol("for", "FOR"), yylineno);
			yyval->addChild(t);

			t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-4]);
			yyval->addChild(yyvsp[-3]);
			yyval->addChild(yyvsp[-2]);


			t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[0]);

			logout << "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement" << endl;
		}
#line 2005 "parser.tab.c"
    break;

  case 39:
#line 473 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "IF LPAREN expression RPAREN statement", yylineno);

			auto t = new SymbolAST(getSymbol("if", "IF"), yylineno);
			yyval->addChild(t);

			t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-2]);

			t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[0]);

			logout << "statement : IF LPAREN expression RPAREN statement" << endl;
		}
#line 2028 "parser.tab.c"
    break;

  case 40:
#line 492 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "IF LPAREN expression RPAREN statement ELSE statement", yylineno);

			auto t = new SymbolAST(getSymbol("if", "IF"), yylineno);
			yyval->addChild(t);

			t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-4]);

			t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-2]);

			t = new SymbolAST(getSymbol("else", "ELSE"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[0]);

			logout << "statement : IF LPAREN expression RPAREN statement ELSE statement" << endl;
		}
#line 2056 "parser.tab.c"
    break;

  case 41:
#line 517 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "WHILE LPAREN expression RPAREN statement", yylineno);

			auto t = new SymbolAST(getSymbol("while", "WHILE"), yylineno);
			yyval->addChild(t);

			t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-2]);

			t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[0]);

			logout << "statement : WHILE LPAREN expression RPAREN statement" << endl;
		}
#line 2079 "parser.tab.c"
    break;

  case 42:
#line 536 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "PRINTLN LPAREN ID RPAREN SEMICOLON", yylineno);

			auto t = new SymbolAST(getSymbol("while", "WHILE"), yylineno);
			yyval->addChild(t);

			t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-2]);
			
			t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
			yyval->addChild(t);
			
			t = new SymbolAST(getSymbol(";", "SEMICOLON"), yylineno);
			yyval->addChild(t);
		}
#line 2101 "parser.tab.c"
    break;

  case 43:
#line 554 "parser.y"
                {
			yyval = new TokenAST(NodeType::STATEMENT, "RETURN expression SEMICOLON", yylineno);

			auto t = new SymbolAST(getSymbol("return", "RETURN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-1]);

			t = new SymbolAST(getSymbol(";", "SEMICOLON"), yylineno);
			yyval->addChild(t);

			
		}
#line 2119 "parser.tab.c"
    break;

  case 44:
#line 570 "parser.y"
                        {
				yyval = new TokenAST(NodeType::EXPR_STMNT, "SEMICOLON", yylineno);
				
				auto t = new SymbolAST(getSymbol(";", "SEMICOLON"), yylineno);
				yyval->addChild(t);

				logout << "expression_statement : SEMICOLON" << endl;
			}
#line 2132 "parser.tab.c"
    break;

  case 45:
#line 579 "parser.y"
                        {
				yyval = new TokenAST(NodeType::EXPR_STMNT, "SEMICOLON", yylineno);

				yyval->addChild(yyvsp[-1]);
				
				auto t = new SymbolAST(getSymbol(";", "SEMICOLON"), yylineno);
				yyval->addChild(t);

				logout << "expression_statement : expression SEMICOLON" << endl;
			}
#line 2147 "parser.tab.c"
    break;

  case 46:
#line 592 "parser.y"
                {
			yyval = new TokenAST(NodeType::VARIABLE, "ID", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "variable : identifier" << endl;
		}
#line 2158 "parser.tab.c"
    break;

  case 47:
#line 599 "parser.y"
                {
			yyval = new TokenAST(NodeType::VARIABLE, "identifier LTHIRD expression RTHIRD", yylineno);
			yyval->addChild(yyvsp[-3]);

			auto t = new SymbolAST(getSymbol("[", "LTHIRD"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-1]);

			t = new SymbolAST(getSymbol("]", "RTHIRD"), yylineno);
			yyval->addChild(t);

			logout << "variable : ID LTHIRD expression RTHIRD" << endl;
		}
#line 2177 "parser.tab.c"
    break;

  case 48:
#line 616 "parser.y"
                {
			yyval = new TokenAST(NodeType::EXP, "logic_expression", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "expression : logic_expression" << endl;
		}
#line 2188 "parser.tab.c"
    break;

  case 49:
#line 623 "parser.y"
           {
			yyval = new TokenAST(NodeType::EXP, "variable ASSIGNOP logic_expression", yylineno);
			yyval->addChild(yyvsp[-2]);

			auto t = new SymbolAST(getSymbol("=", "ASSIGNOP"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[0]);

			logout << "expression : variable ASSIGNOP logic_expression" << endl;
	   }
#line 2204 "parser.tab.c"
    break;

  case 50:
#line 637 "parser.y"
                {
			yyval = new TokenAST(NodeType::LOGIC_EXP, "rel_expression", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "logic_expression : rel_expression" << endl;
		}
#line 2215 "parser.tab.c"
    break;

  case 51:
#line 644 "parser.y"
                {
			yyval = new TokenAST(NodeType::LOGIC_EXP, "rel_expression LOGICOP rel_expression", yylineno);
			yyval->addChild(yyvsp[-2]);
			yyval->addChild(yyvsp[-1]);
			yyval->addChild(yyvsp[0]);

			logout << "logic_expression : rel_expression LOGICOP rel_expression" << endl;
		}
#line 2228 "parser.tab.c"
    break;

  case 52:
#line 655 "parser.y"
                {
			yyval = new TokenAST(NodeType::REL_EXP, "simple_expression", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "rel_expression : simple_expression" << endl;
		}
#line 2239 "parser.tab.c"
    break;

  case 53:
#line 662 "parser.y"
                {
			yyval = new TokenAST(NodeType::REL_EXP, "simple_expression RELOP simple_expression", yylineno);
			yyval->addChild(yyvsp[-2]);
			yyval->addChild(yyvsp[-1]);
			yyval->addChild(yyvsp[0]);

			logout << "rel_expression : simple_expression RELOP simple_expression" << endl;
		}
#line 2252 "parser.tab.c"
    break;

  case 54:
#line 673 "parser.y"
                {
			yyval = new TokenAST(NodeType::SIMPLE_EXP, "term", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "simple_expression : term" << endl;
		}
#line 2263 "parser.tab.c"
    break;

  case 55:
#line 680 "parser.y"
                {
			yyval = new TokenAST(NodeType::REL_EXP, "simple_expression ADDOP term", yylineno);
			yyval->addChild(yyvsp[-2]);
			yyval->addChild(yyvsp[-1]);
			yyval->addChild(yyvsp[0]);
			
			logout << "simple_expression : simple_expression ADDOP term" << endl;
		}
#line 2276 "parser.tab.c"
    break;

  case 56:
#line 692 "parser.y"
                {
			yyval = new TokenAST(NodeType::TERM, "unary_expression", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "term : unary_expression" << endl;
		}
#line 2287 "parser.tab.c"
    break;

  case 57:
#line 699 "parser.y"
                {
			yyval = new TokenAST(NodeType::TERM, "term MULOP unary_expression", yylineno);
			yyval->addChild(yyvsp[-2]);
			yyval->addChild(yyvsp[-1]);
			yyval->addChild(yyvsp[0]);

			logout << "term : term MULOP unary_expression" << endl;
		}
#line 2300 "parser.tab.c"
    break;

  case 58:
#line 710 "parser.y"
                {
			yyval = new TokenAST(NodeType::UNARY_EXP, "ADDOP unary_expression", yylineno);
			yyval->addChild(yyvsp[-1]);
			yyval->addChild(yyvsp[0]);

			logout << "unary_expression : ADDOP unary_expression" << endl;
		}
#line 2312 "parser.tab.c"
    break;

  case 59:
#line 718 "parser.y"
                {
			yyval = new TokenAST(NodeType::UNARY_EXP, "NOT unary_expression", yylineno);

			auto t = new SymbolAST(getSymbol("!", "NOT"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[0]);

			logout << "NOT unary_expression" << endl;
		}
#line 2327 "parser.tab.c"
    break;

  case 60:
#line 729 "parser.y"
                {
			yyval = new TokenAST(NodeType::UNARY_EXP, "factor", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "unary_expression : factor" << endl;
		}
#line 2338 "parser.tab.c"
    break;

  case 61:
#line 738 "parser.y"
                {
			yyval = new TokenAST(NodeType::FACTOR, "variable", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "factor : variable" << endl;
		}
#line 2349 "parser.tab.c"
    break;

  case 62:
#line 746 "parser.y"
                {
			yyval = new TokenAST(NodeType::FACTOR, "ID LPAREN argument_list RPAREN", yylineno);
			yyval->addChild(yyvsp[-3]);

			auto t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-1]);

			t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
			yyval->addChild(t);

			logout << "factor : ID LPAREN expression RPAREN" << endl;
		}
#line 2368 "parser.tab.c"
    break;

  case 63:
#line 761 "parser.y"
                {
			yyval = new TokenAST(NodeType::FACTOR, "LPAREN expression RPAREN", yylineno);

			auto t = new SymbolAST(getSymbol("(", "LPAREN"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[-1]);

			t = new SymbolAST(getSymbol(")", "RPAREN"), yylineno);
			yyval->addChild(t);

			logout << "factor : LPAREN expression RPAREN" << endl;
		}
#line 2386 "parser.tab.c"
    break;

  case 64:
#line 775 "parser.y"
                {
			yyval = new TokenAST(NodeType::FACTOR, "CONST_INT", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "factor : CONST_INT" << endl;
		}
#line 2397 "parser.tab.c"
    break;

  case 65:
#line 782 "parser.y"
                {
			yyval = new TokenAST(NodeType::FACTOR, "CONST_FLOAT", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "factor : CONST_FLOAT" << endl;
		}
#line 2408 "parser.tab.c"
    break;

  case 66:
#line 789 "parser.y"
                {
			yyval = new TokenAST(NodeType::FACTOR, "variable INCOP", yylineno);
			yyval->addChild(yyvsp[-1]);

			auto t = new SymbolAST(getSymbol("++", "INCOP"), yylineno);
			yyval->addChild(t);

			logout << "factor : variable INCOP" << endl;
		}
#line 2422 "parser.tab.c"
    break;

  case 67:
#line 800 "parser.y"
                {
			yyval = new TokenAST(NodeType::FACTOR, "variable DECOP", yylineno);
			yyval->addChild(yyvsp[-1]);

			auto t = new SymbolAST(getSymbol("--", "DECOP"), yylineno);
			yyval->addChild(t);

			logout << "factor : variable DECOP" << endl;
		}
#line 2436 "parser.tab.c"
    break;

  case 68:
#line 812 "parser.y"
                {
			yyval = new TokenAST(NodeType::ARG_LIST, "arguments", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "argument_list : arguments" << endl;
		}
#line 2447 "parser.tab.c"
    break;

  case 69:
#line 819 "parser.y"
                {
			yyval = new TokenAST(NodeType::ARG_LIST, "", yylineno);
			logout << "argument_list : " << endl;
		}
#line 2456 "parser.tab.c"
    break;

  case 70:
#line 826 "parser.y"
                {
			yyval = new TokenAST(NodeType::ARGS, "arguments COMMA logic_expression", yylineno);
			yyval->addChild(yyvsp[-2]);


			auto t = new SymbolAST(getSymbol(",", "COMMA"), yylineno);
			yyval->addChild(t);

			yyval->addChild(yyvsp[0]);

			logout << "arguments : arguments COMMA logic_expression" << endl;
		}
#line 2473 "parser.tab.c"
    break;

  case 71:
#line 839 "parser.y"
                {
			yyval = new TokenAST(NodeType::ARGS, "logic_expression", yylineno);
			yyval->addChild(yyvsp[0]);

			logout << "arguments : logic_expression" << endl;
		}
#line 2484 "parser.tab.c"
    break;


#line 2488 "parser.tab.c"

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
#line 847 "parser.y"

int main(int argc,char *argv[])
{
	auto fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	// auto fp2= fopen(argv[2],"w");
	// fclose(fp2);
	// auto fp3= fopen(argv[3],"w");
	// fclose(fp3);
	
	// fp2= fopen(argv[2],"a");
	// fp3= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	

	// fclose(fp2);
	// fclose(fp3);
	fclose(fp);
	
	return 0;
}

