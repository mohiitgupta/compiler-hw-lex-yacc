/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 53 "hw6.y"
{
        int number;
        int boolean;
        struct ast_node * ast;
        struct symbol_node * symbol;
        char * string;
}
/* Line 1529 of yacc.c.  */
#line 107 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

