/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
#line 123 "parser.y"

	#include "lib/ast.h"

#line 53 "parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    FOR = 259,                     /* FOR  */
    DO = 260,                      /* DO  */
    INT = 261,                     /* INT  */
    FLOAT = 262,                   /* FLOAT  */
    VOID = 263,                    /* VOID  */
    SWITCH = 264,                  /* SWITCH  */
    DEFAULT = 265,                 /* DEFAULT  */
    ELSE = 266,                    /* ELSE  */
    WHILE = 267,                   /* WHILE  */
    BREAK = 268,                   /* BREAK  */
    CHAR = 269,                    /* CHAR  */
    DOUBLE = 270,                  /* DOUBLE  */
    RETURN = 271,                  /* RETURN  */
    CASE = 272,                    /* CASE  */
    CONTINUE = 273,                /* CONTINUE  */
    MAIN = 274,                    /* MAIN  */
    CONST_INT = 275,               /* CONST_INT  */
    CONST_FLOAT = 276,             /* CONST_FLOAT  */
    CONST_CHAR = 277,              /* CONST_CHAR  */
    ASSIGNOP = 278,                /* ASSIGNOP  */
    NOT = 279,                     /* NOT  */
    LPAREN = 280,                  /* LPAREN  */
    RPAREN = 281,                  /* RPAREN  */
    LTHIRD = 282,                  /* LTHIRD  */
    RTHIRD = 283,                  /* RTHIRD  */
    LCURL = 284,                   /* LCURL  */
    RCURL = 285,                   /* RCURL  */
    COMMA = 286,                   /* COMMA  */
    SEMICOLON = 287,               /* SEMICOLON  */
    ADDOP = 288,                   /* ADDOP  */
    MULOP = 289,                   /* MULOP  */
    INCOP = 290,                   /* INCOP  */
    DECOP = 291,                   /* DECOP  */
    RELOP = 292,                   /* RELOP  */
    LOGICOP = 293,                 /* LOGICOP  */
    BITOP = 294,                   /* BITOP  */
    ID = 295,                      /* ID  */
    PRINTLN = 296,                 /* PRINTLN  */
    LOWER_THAN_ELSE = 297          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
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
