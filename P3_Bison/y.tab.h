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
    NUM = 258,
    ID = 259,
    ARCHIVO = 260,
    SENO = 261,
    COSENO = 262,
    TANGENTE = 263,
    ARCSENO = 264,
    ARCCOSENO = 265,
    ARCTANG = 266,
    LOG = 267,
    LOGNEP = 268,
    EXP = 269,
    SQRT = 270,
    MAS_IGUAL = 271,
    MENOS_IGUAL = 272,
    POR_IGUAL = 273,
    ENTRE_IGUAL = 274,
    LOAD = 275,
    HELP = 276,
    CLEAR = 277,
    WORKSPACE = 278,
    ECHO = 279,
    ON = 280,
    OFF = 281,
    INVALID = 282,
    EOL = 283,
    ENDOFFILE = 284,
    UMINUS = 285
  };
#endif
/* Tokens.  */
#define NUM 258
#define ID 259
#define ARCHIVO 260
#define SENO 261
#define COSENO 262
#define TANGENTE 263
#define ARCSENO 264
#define ARCCOSENO 265
#define ARCTANG 266
#define LOG 267
#define LOGNEP 268
#define EXP 269
#define SQRT 270
#define MAS_IGUAL 271
#define MENOS_IGUAL 272
#define POR_IGUAL 273
#define ENTRE_IGUAL 274
#define LOAD 275
#define HELP 276
#define CLEAR 277
#define WORKSPACE 278
#define ECHO 279
#define ON 280
#define OFF 281
#define INVALID 282
#define EOL 283
#define ENDOFFILE 284
#define UMINUS 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "bison.y"

    double  num;
    char    *str ;

#line 122 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
