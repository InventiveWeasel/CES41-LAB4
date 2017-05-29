%{
#include 	<string.h>
#include	<stdio.h>
#include	<stdlib.h>
void comentario (void);
#define LT 			1
#define LE 			2
#define	GT			3
#define	GE			4
#define	EQ			5
#define	NE			6
#define PL			1
#define MI			2
#define MU			1
#define DI			2
#define RE			3
int tab = 0;
void tabular (void);
%}
%union {
	char string[50];
	int atr, valor;
	float valreal;
	char carac;
}
%token 				CALL
%token 				CHAR
%Token 				ELSE
%token				FALSE
%token 				FLOAT
%token 				FOR
%token 				FUNCTION
%token 				IF
%token 				INT
%token 				LOGIC
%token 				PROCEDURE
%token 				PROGRAM
%token 				READ
%token 				REPEAT
%token 				RETURN
%token 				TRUE
%token 				VAR
%token 				WHILE
%token 				WRITE
%token	<string>	ID
%token	<valor>		INTCT
%token	<string>	CHARCT
%token	<valreal>	FLOATCT
%token	<string>	STRING
%token				OR
%token				AND
%token				NOT
%token	<atr>		RELOP
%token	<atr>		ADOP
%token	<atr>		MULTOP
%token				NEG
%token				OPPAR
%token				CLPAR
%token				OPBRAK
%token				CLBRAK
%token				OPBRACE
%token				CLBRACE
%token				SCOLON 
%token				COMMA
%token				ASSIGN
%token	<carac>		INVAL
%nonassoc 			LOWER_THAN_ELSE
%nonassoc 			ELSE
%%
Prog			:  PROGRAM ID SCOLON {printf("program %s;\n\n", $2);} Decls  SubProgs  CompStat  
				;
Decls 			:	
				|  VAR {printf("var\n"); tab++;} DeclList {tab--;}
				;
DeclList		:  Declaration
				|  DeclList  Declaration
				;
Declaration 	:  Type ElemList SCOLON {printf(";\n");} 
				;
Type			:  INT {tabular(); printf("int ");}
				|  FLOAT {tabular(); printf("float ");}
				|  CHAR {tabular(); printf("char ");}
				|  LOGIC {tabular(); printf("logic ");}
				;
ElemList    	:  Elem
				|  ElemList COMMA {printf(", ");} Elem
				;
Elem        	:  ID {printf("%s", $1);} DimList
				;
DimList	    	: 
				|  DimList  Dim
				;
Dim				:  OPBRAK INTCT CLBRAK {printf("[%d]", $2);}
				;
SubProgs	    :
				|  SubProgs  SubProgDecl
				;
SubProgDecl   	:  Header  Decls  CompStat
				;
Header   		:  FuncHeader
				|  ProcHeader
				;
FuncHeader		:  FUNCTION {tabular(); printf("function ");} Type ID OPPAR {printf("%s(", $4);} FuncHeaderAux
				;
FuncHeaderAux	:  CLPAR  SCOLON {printf(");\n");}
				|  ParamList  CLPAR  SCOLON {printf(");\n");}
				;
ProcHeader  	:  PROCEDURE ID OPPAR {tabular(); printf("procedure %s(", $2);} CLPAR SCOLON {printf(");\n");}
				|  PROCEDURE ID OPPAR {tabular(); printf("procedure %s(", $2);} ParamList CLPAR SCOLON {printf(");\n");}
				;
ParamList   	:  Parameter
				|  ParamList  COMMA {printf(", ");} Parameter
				;
Parameter   	:  Type ID {printf("%s", $2);}
				;
CompStat		:  OPBRACE {tabular(); printf("\{\n"); tab++;}
				   StatList  CLBRACE  {tab--; tabular(); printf("}\n");}
				;
StatList		:
				|  StatList  Statement
				;
Statement   	:  CompStat  |  IfStat  |  WhileStat  |  RepeatStat
            	|  ForStat  |  ReadStat  |  WriteStat  |  AssignStat
            	|  CallStat  |  ReturnStat  |  SCOLON {printf(";\n");}
				;
IfStat			:  IF OPPAR {tabular(); printf("if("); tab++;} Expression  CLPAR {printf(")\n");} Statement {tab--;} ElseStat
				;
ElseStat		:  
				|  ELSE {tabular(); printf("else\n"); tab++;} Statement {tab--;}
				;
WhileStat   	:  WHILE OPPAR {tabular(); printf("while(");} Expression CLPAR {printf(")");} Statement
				;
RepeatStat  	:  REPEAT {tabular(); printf("repeat ");} Statement  WHILE OPPAR {printf("while(");} Expression CLPAR SCOLON {printf(");\n");}
				;
ForStat	    	:  FOR OPPAR {tabular(); printf("for(");} Variable ASSIGN {printf(" = ");} Expression SCOLON {printf("; ");} Expression SCOLON {printf("; ");} Variable ASSIGN {printf(" = ");} Expression  CLPAR {printf(")\n");} Statement
				;
ReadStat   		:  READ OPPAR {tabular(); printf("read(");} ReadList CLPAR SCOLON {printf(");\n");}
				;
ReadList		:  Variable
				|  ReadList COMMA {printf(", ");} Variable
				;
WriteStat   	:  WRITE OPPAR {tabular(); printf("write(");} WriteList CLPAR SCOLON {printf(");\n");}
				;
WriteList		:  WriteElem
				|  WriteList COMMA {printf(", ");} WriteElem
				;
WriteElem		:  STRING {printf("\"%s\"", $1);}
				|  Expression  
				;
CallStat    	:  CALL ID OPPAR {tabular(); printf("call %s(", $2);} CLPAR SCOLON {printf(");\n");}
				|  CALL ID OPPAR {tabular(); printf("call %s(", $2);} ExprList CLPAR SCOLON {printf(");\n");}
				;
ReturnStat  	:  RETURN {tabular(); printf("return ");} SCOLON {printf(";\n");}
				|  RETURN {tabular(); printf("return ");} Expression SCOLON {printf(";\n");}
				;
AssignStat  	: {tabular();} Variable ASSIGN {printf(" = ");} Expression SCOLON {printf(";\n");}
				;
ExprList		:  Expression
				|  ExprList COMMA {printf(", ");} Expression
				;
Expression  	:  AuxExpr1
				|  Expression OR {printf(" || ");} AuxExpr1
				;
AuxExpr1    	:  AuxExpr2
				|  AuxExpr1 AND {printf(" && ");} AuxExpr2
				;
AuxExpr2    	:  AuxExpr3
				|  NOT {printf("!");} AuxExpr3
				;
AuxExpr3    	:  AuxExpr4
				|  AuxExpr4  RELOP
				{
					switch($2){
						case LT: printf(" < "); break;
						case LE: printf(" <= "); break;
						case GT: printf(" > "); break;
						case GE: printf(" >= "); break;
						case EQ: printf(" == "); break;
						case NE: printf(" != "); break;
					}
				}
				AuxExpr4
				;
AuxExpr4    	:  Term
				|  AuxExpr4  ADOP
				{
					switch($2){
						case PL: printf(" + "); break;
						case MI: printf(" - "); break;
					}
				}
				Term
				;
Term  	    	:  Factor
				|  Term  MULTOP 
				{
					switch($2){
						case MU: printf(" * "); break;
						case DI: printf(" / "); break;
						case RE: printf(" %% "); break;
					}
				}
				Factor
				;
Factor			:  Variable
				|  INTCT {printf("%d", $1);}
				|  FLOATCT {printf("%g", $1);}
				|  CHARCT {printf("'%s'", $1);}
            	|  TRUE {printf("true");}
				|  FALSE {printf("false");}
				|  NEG {printf("!");} Factor
            	|  OPPAR {printf("(");} Expression  CLPAR {printf(")");}
				|  FuncCall
				;
Variable		:  ID {printf("%s", $1);} SubscrList  
				;
SubscrList  	:
				|  SubscrList  Subscript
				;
Subscript		:  OPBRAK {printf("[");} AuxExpr4  CLBRAK {printf("]");}
				;
FuncCall    	:  ID OPPAR {printf("%s()", $1);} CLPAR
				|  ID OPPAR {printf("%s(", $1);} ExprList  CLPAR  {printf(")");}
				;
%%
#include "lex.yy.c"
