/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 53 "parser.y" /* yacc.c:1909  */
 
    ExpType expType;            // for passing types.  typespec to pass up a type in decl like int or bool
    DeclKind declKind;
    TokenData *tokenData;    // for terminals.  token data comes from yylex() in the $ variables
    TreeNode *tree;          // for nonterminals.   these tree nodes as you build the tree

#line 112 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
