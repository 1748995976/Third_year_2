%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"
int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int type_int;
	float type_float;
    char type_char;
	char type_id[32];
	struct ASTNode *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL

%}
%option yylineno

id      [A-Za-z][A-Za-z0-9]*  
int     [+-]*[0-9]+|[0-9]+
float   ([0-9]*\.[0-9]+)|([0-9]+\.)
char  	('[A-Za-z0-9]')

%%
{int}        {yylval.type_int=atoi(yytext); return INT;}
{float}      {yylval.type_float=atof(yytext); return FLOAT;}
{char}       {yylval.type_char = (char)atoi(yytext);return CHAR;}   
"int"        {strcpy(yylval.type_id,  yytext);printf("< TYPE,%s >\n",yytext);return TYPE;return TYPE;}
"float"      {strcpy(yylval.type_id,  yytext);printf("< TYPE,%s >\n",yytext);return TYPE;return TYPE;}
"char"       {strcpy(yylval.type_id,  yytext);printf("< TYPE,%s >\n",yytext);return TYPE;return TYPE;}

"return"     {printf("< RETURN,%s >\n",yytext);return RETURN;}
"if"         {printf("< IF,%s >\n",yytext);return IF;}
"else"       {printf("< ELSE,%s >\n",yytext);return ELSE;}
"while"      {printf("< WHILE,%s >\n",yytext);return WHILE;}
"for"        {printf("< FOR,%s >\n",yytext);return FOR;}
"struct"     {printf("< FOR,%s >\n",yytext);return STRUCT;}

{id}       {strcpy(yylval.type_id,  yytext); return ID;/*由于关键字的形式也符合表示符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			{return SEMI;}
","			{return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);;return RELOP;}
"="			{return ASSIGNOP;}
"--"        {return MINUSONE;}
"++"        {return PLUSONE;}
"+"			{return PLUS;}
"-"			{return MINUS;}
"*"			{return STAR;}
"/"			{return DIV;}
"&&"        {return AND;}
"||"        {return OR;}
"."         {return DOT;}
"!"			{return NOT;}
"("			{return LP;}
")"			{return RP;}
"{"			{return LC;}
"}"			{return RC;}
"["         {return LB;}
"]"         {return RB;}
[\n]        {yycolumn=1;}   
[ \r\t]     {}   
"/*"(.|\n)*"*/" {;}
"\/\/".*        {;}
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}

%%

//


/* 和bison联用时，不需要这部分
void main()
{
yylex();
return 0;
}

*/
int yywrap()
{
return 1;
}