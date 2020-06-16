%error-verbose
%locations
%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(struct ASTNode *,int);
%}

%union {
	int    type_int;
	float  type_float;
        char   type_char; 
	char   type_id[32];
	struct ASTNode *ptr;
};

//  %type 定义非终结符的语义值类型
%type  <ptr> program ExtDefList ExtDef  Specifier ExtDecList FuncDec CompSt VarList VarDec ParamDec Stmt StmList DefList Def DecList Dec Exp Args  //ArrayDec
%type  <ptr> ARRAY_D  ArrayIndex ForDec Specifier_STRUCT CompSt_STRUCT STRUCT_TYPE

//% token 定义终结符的语义值类型
%token <type_int> INT              //指定INT的语义值是type_int，有词法分析得到的数值
%token <type_id> ID RELOP TYPE  //指定ID,RELOP 的语义值是type_id，有词法分析得到的标识符字符串
%token <type_float> FLOAT         //指定ID的语义值是type_id，有词法分析得到的标识符字符串
%token <type_char> CHAR

%token LP RP LC RC LB RB SEMI COMMA DOT STRUCT   //用bison对该文件编译时，带参数-d，生成的exp.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码
%token ASSIGNOP_MINUS ASSIGNOP_PLUS ASSIGNOP_DIV ASSIGNOP_STAR PLUS MINUS STAR DIV ASSIGNOP AND OR NOT IF ELSE WHILE RETURN FOR


%left ASSIGNOP ASSIGNOP_MINUS ASSIGNOP_PLUS ASSIGNOP_DIV ASSIGNOP_STAR
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%left MOD
%right UMINUS NOT
%left PLUSONE MINUSONE 
%left SEMI DOT

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%

program: ExtDefList    { display($1,0); }     /*显示语法树,语义分析*/
         ; 
ExtDefList: {$$=NULL;}
          | ExtDef ExtDefList {$$=mknode(2,EXT_DEF_LIST,yylineno,$1,$2);}   //每一个EXTDEFLIST的结点，其第1棵子树对应一个外部变量声明或函数
          ;  
ExtDef:   Specifier ExtDecList SEMI   {$$=mknode(2,EXT_VAR_DEF,yylineno,$1,$2);}   //该结点对应一个外部变量声明
         | Specifier_STRUCT SEMI {$$=mknode(1,STRUCT_DEF,yylineno,$1);}
         | Specifier FuncDec CompSt    {$$=mknode(3,FUNC_DEF,yylineno,$1,$2,$3);}         //该结点对应一个函数定义
         | error SEMI   {$$=NULL; }
         ;
Specifier:  TYPE    {$$=mknode(0,TYPE,yylineno);strcpy($$->type_id,$1);$$->type=!strcmp($1,"int")?INT:!strcmp($1,"float")?FLOAT:CHAR;}   
           ;    
Specifier_STRUCT: 
         STRUCT ID CompSt_STRUCT  {$$=mknode(1,STRUCT_DEC,yylineno,$3);strcpy($$->type_id,$2);}//结构体名存放在$$->type_id
        | STRUCT ID STRUCT_TYPE {$$=mknode(1,STRUCT_D,yylineno,$3);strcpy($$->type_id,$2);}
        ;
CompSt_STRUCT: LC DefList RC    {$$=mknode(1,COMP_STM_STRUCT,yylineno,$2);}
        ;
STRUCT_TYPE:
        ID {$$=mknode(0,STRUCT_NAME,yylineno);strcpy($$->type_id,$1);}
        ;
ExtDecList:  VarDec      {$$=$1;}       /*每一个EXT_DECLIST的结点，其第一棵子树对应一个变量名(ID类型的结点),第二棵子树对应剩下的外部变量名*/
           | VarDec COMMA ExtDecList {$$=mknode(2,EXT_DEC_LIST,yylineno,$1,$3);}
           ;  
VarDec:  ID          {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}   //ID结点，标识符符号串存放结点的type_id
        | ID ARRAY_D ArrayIndex {$$=mknode(2,ARRAY_ID,yylineno,$2,$3);strcpy($$->type_id,$1);}
        ;
ARRAY_D : {$$=NULL;}
        | ARRAY_D ArrayIndex {$$ = mknode(2,ARRAY_D,yylineno,$1,$2);}
        ;
ArrayIndex: LB INT RB {$$=mknode(0,ARRAY_INDEX,yylineno); $$->type_int = $2;}     
        ;   

FuncDec: ID LP VarList RP   {$$=mknode(1,FUNC_DEC,yylineno,$3);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
        | ID LP  RP   {$$=mknode(0,FUNC_DEC,yylineno);strcpy($$->type_id,$1);}//函数名存放在$$->type_id

        ;  
VarList: ParamDec  {$$=mknode(1,PARAM_LIST,yylineno,$1);}
        | ParamDec COMMA  VarList  {$$=mknode(2,PARAM_LIST,yylineno,$1,$3);}
        ;
ParamDec: Specifier VarDec         {$$=mknode(2,PARAM_DEC,yylineno,$1,$2);}
         ;
CompSt: LC DefList StmList RC    {$$=mknode(2,COMP_STM,yylineno,$2,$3);}
        ;
StmList: {$$=NULL; }  
        | Stmt StmList  {$$=mknode(2,STM_LIST,yylineno,$1,$2);}
        ;
Stmt:   Exp SEMI    {$$=mknode(1,EXP_STMT,yylineno,$1);}
      | CompSt      {$$=$1;}      //复合语句结点直接最为语句结点，不再生成新的结点 
      | RETURN Exp SEMI   {$$=mknode(1,RETURN,yylineno,$2);}
      | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   {$$=mknode(2,IF_THEN,yylineno,$3,$5);}
      | IF LP Exp RP Stmt ELSE Stmt   {$$=mknode(3,IF_THEN_ELSE,yylineno,$3,$5,$7);}
      | WHILE LP Exp RP Stmt {$$=mknode(2,WHILE,yylineno,$3,$5);}
      | FOR LP ForDec RP Stmt {$$=mknode(2,FOR_DEF,yylineno,$3,$5);}
      ;
ForDec:   Exp SEMI Exp SEMI Exp{$$=mknode(3,FOR_CON,yylineno,$1,$3,$5);}
        | SEMI Exp SEMI {$$=mknode(1,FOR_CON,yylineno,$2);}
        ;
  
DefList: {$$=NULL; }
        | Def DefList {$$=mknode(2,DEF_LIST,yylineno,$1,$2);
        ;
Def:    Specifier DecList SEMI {$$=mknode(2,VAR_DEF,yylineno,$1,$2);}
        | Specifier_STRUCT SEMI{$$ = $1};
        ;
DecList: Dec  {$$=mknode(1,DEC_LIST,yylineno,$1);}
       | Dec COMMA DecList  {$$=mknode(2,DEC_LIST,yylineno,$1,$3);}
	;
Dec:     VarDec  {$$=$1;}
       | VarDec ASSIGNOP Exp  {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}
       ;
Exp:    Exp ASSIGNOP Exp {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}//$$结点type_id空置未用，正好存放运算符
      | Exp AND Exp   {$$=mknode(2,AND,yylineno,$1,$3);strcpy($$->type_id,"AND");}
      | Exp OR Exp    {$$=mknode(2,OR,yylineno,$1,$3);strcpy($$->type_id,"OR");}
      | Exp RELOP Exp {$$=mknode(2,RELOP,yylineno,$1,$3);strcpy($$->type_id,$2);}  //词法分析关系运算符号自身值保存在$2中
      | Exp PLUS Exp  {$$=mknode(2,PLUS,yylineno,$1,$3);strcpy($$->type_id,"PLUS");}
      | Exp MINUS Exp {$$=mknode(2,MINUS,yylineno,$1,$3);strcpy($$->type_id,"MINUS");}
      | Exp STAR Exp  {$$=mknode(2,STAR,yylineno,$1,$3);strcpy($$->type_id,"STAR");}
      | Exp DIV Exp   {$$=mknode(2,DIV,yylineno,$1,$3);strcpy($$->type_id,"DIV");}
      | LP Exp RP     {$$=$2;}
      | MINUS Exp %prec UMINUS   {$$=mknode(1,UMINUS,yylineno,$2);strcpy($$->type_id,"UMINUS");}
      | NOT Exp       {$$=mknode(1,NOT,yylineno,$2);strcpy($$->type_id,"NOT");}
      | ID LP Args RP {$$=mknode(1,FUNC_CALL,yylineno,$3);strcpy($$->type_id,$1);}
      | ID LP RP      {$$=mknode(0,FUNC_CALL,yylineno);strcpy($$->type_id,$1);}
      | ID ARRAY_D ArrayIndex {$$=mknode(2,ARRAY_ID,yylineno,$2,$3);strcpy($$->type_id,$1);}
      | ID            {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}
      | INT           {$$=mknode(0,INT,yylineno);$$->type_int=$1;$$->type=INT;}
      | FLOAT         {$$=mknode(0,FLOAT,yylineno);$$->type_float=$1;$$->type=FLOAT;}
      | CHAR          {$$ = mknode(0,CHAR,yylineno);$$->type_char = $1; $$->type = CHAR;}
      | Exp DOT Exp {$$=mknode(2,STRUCT_USE,yylineno,$1,$3);}
      | Exp PLUSONE {$$ = mknode(1,PLUSONE_L,yylineno,$1);strcpy($$->type_id,"PLUSONE_L");}
      | PLUSONE Exp {$$ = mknode(1,PLUSONE_R,yylineno,$2);strcpy($$->type_id,"PLUSONE_R");}
      | Exp MINUSONE {$$ = mknode(1,MINUSONE_L,yylineno,$1);strcpy($$->type_id,"MINUSONE_L");}
      | MINUSONE Exp {$$ = mknode(1,MINUSONE_R,yylineno,$2);strcpy($$->type_id,"MINUSONE_R");}
      | Exp PLUS ASSIGNOP Exp{$$=mknode(2,ASSIGNOP_PLUS,yylineno,$1,$4);strcpy($$->type_id,"ASSIGNOP_PLUS");}
      | Exp MINUS ASSIGNOP Exp{$$=mknode(2,ASSIGNOP_MINUS,yylineno,$1,$4);strcpy($$->type_id,"ASSIGNOP_MINUS");}
      | Exp STAR ASSIGNOP Exp{$$=mknode(2,ASSIGNOP_STAR,yylineno,$1,$4);strcpy($$->type_id,"ASSIGNOP_STAR");}
      | Exp DIV ASSIGNOP Exp{$$=mknode(2,ASSIGNOP_DIV,yylineno,$1,$4);strcpy($$->type_id,"ASSIGNOP_MINUS");}
      ;
Args:    Exp COMMA Args    {$$=mknode(2,ARGS,yylineno,$1,$3);}
       | Exp               {$$=mknode(1,ARGS,yylineno,$1);}
       ;
%%

int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return -1;
	yylineno=1;
	yyparse();
	return 0;
	}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}	