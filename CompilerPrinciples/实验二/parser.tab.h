
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     ID = 259,
     RELOP = 260,
     TYPE = 261,
     CHAR = 262,
     FLOAT = 263,
     STRING = 264,
     DPLUS = 265,
     DMINUS = 266,
     LP = 267,
     RP = 268,
     LB = 269,
     RB = 270,
     LC = 271,
     RC = 272,
     SEMI = 273,
     COMMA = 274,
     DOT = 275,
     ASSIGNOP_MINUS = 276,
     ASSIGNOP_PLUS = 277,
     ASSIGNOP_DIV = 278,
     ASSIGNOP_STAR = 279,
     PLUS = 280,
     MINUS = 281,
     STAR = 282,
     DIV = 283,
     ASSIGNOP = 284,
     AND = 285,
     OR = 286,
     NOT = 287,
     IF = 288,
     ELSE = 289,
     WHILE = 290,
     RETURN = 291,
     FOR = 292,
     SWITCH = 293,
     CASE = 294,
     COLON = 295,
     DEFAULT = 296,
     ARRAY = 297,
     STRUCT = 298,
     EXP_STRUCT = 299,
     UMINUS = 300,
     LOWER_THEN_ELSE = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 15 "parser.y"

	int    type_int;
	float  type_float;
	char   type_char[3];
        char   type_string[32];
	char   type_id[32];
	struct ASTNode *ptr;



/* Line 1676 of yacc.c  */
#line 109 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

