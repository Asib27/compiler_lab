/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

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
    PRINTLN = 296
  };
#endif
/* Tokens.  */
#define IF 258
#define FOR 259
#define DO 260
#define INT 261
#define FLOAT 262
#define VOID 263
#define SWITCH 264
#define DEFAULT 265
#define ELSE 266
#define WHILE 267
#define BREAK 268
#define CHAR 269
#define DOUBLE 270
#define RETURN 271
#define CASE 272
#define CONTINUE 273
#define MAIN 274
#define CONST_INT 275
#define CONST_FLOAT 276
#define CONST_CHAR 277
#define ASSIGNOP 278
#define NOT 279
#define LPAREN 280
#define RPAREN 281
#define LTHIRD 282
#define RTHIRD 283
#define LCURL 284
#define RCURL 285
#define COMMA 286
#define SEMICOLON 287
#define ADDOP 288
#define MULOP 289
#define INCOP 290
#define DECOP 291
#define RELOP 292
#define LOGICOP 293
#define BITOP 294
#define ID 295
#define PRINTLN 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
