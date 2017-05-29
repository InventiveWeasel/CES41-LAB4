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

/* Definicao dos tipos de identificadores */
#define 	IDPROG	1
#define 	IDVAR	2

/* Definicao dos tipos de variaveis */
#define	NAOVAR		0
#define	INTEIRO		1
#define	LOGICO		2
#define	REAL		3
#define	CARACTERE	4

/* Definicao de outras constantes */
#define	NCLASSHASH	23
#define	VERDADE		1
#define	FALSO		0
#define MAXDIMS		10

/* Strings para nomes dos tipos de identificadores*/
char *nometipid[3] = {" ", "IDPROG", "IDVAR"};

/* Strings para nomes dos tipos de variaveis */
char *nometipvar[5]={"NAOVAR", "INTEIRO", "LOGICO","REAL", "CARACTERE"};

/* Declaracoes para a tabela de simbolos */
typedef struct celsimb celsimb;
typedef celsimb *simbolo;
struct celsimb{
	char *cadeia;
	int tid, tvar, ndims,dims[MAXDIMS+1];
	char inic, ref, array;
	simbolo prox;
};

/* Variaveis globais para a tabela de simbolos e analise semantica */
simbolo tabsimb[NCLASSHASH];
simbolo simb;
int tipocorrente;

/* Prototipos das funcoes para a tabela de simbolos e analise semantica */
void InicTabSimb(void);
void ImprimeTabSimb(void);
simbolo InsereSimb(char *,int,int);
int hash(char *);
simbolo ProcuraSimb(char *);
void DeclaracaoRepetida(char *);
void TipoInadequado(char *);
void NaoDeclarado(char *);
void VerificaInicRef(void);
void Incompatibilidade(char *);

int tab = 0;
void tabular (void);
%}
%union {
	char string[50];
	int atr, valint;
	float valreal;
	char carac;
	simbolo simb;
	int tipoexpr;
}
%type	<simb>		Variable
%type	<tipoexpr>	Expression  AuxExpr1  AuxExpr2  AuxExpr3  AuxExpr4  Term  Factor
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
%token	<valint>	INTCT
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
Prog			:  {InicTabSimb();} PROGRAM ID SCOLON {printf("program %s;\n\n", $3); InsereSimb($3, IDPROG, NAOVAR);} Decls  SubProgs  CompStat  {VerificaInicRef(); ImprimeTabSimb();}
				;
Decls 			:	
				|  VAR {printf("var\n"); tab++;} DeclList {tab--;}
				;
DeclList		:  Declaration
				|  DeclList  Declaration
				;
Declaration 	:  Type ElemList SCOLON {printf(";\n");} 
				;
Type			:  INT {tabular(); printf("int "); tipocorrente = INTEIRO;}
				|  FLOAT {tabular(); printf("float "); tipocorrente = REAL;}
				|  CHAR {tabular(); printf("char "); tipocorrente = CARACTERE;}
				|  LOGIC {tabular(); printf("logic ");  tipocorrente = LOGICO;}
				;
ElemList    	:  Elem
				|  ElemList COMMA {printf(", ");} Elem
				;
Elem        	:  ID 	{
							printf("%s", $1);
							if(ProcuraSimb($1) != NULL)
								DeclaracaoRepetida($1);
							else
								InsereSimb($1, IDVAR, tipocorrente);
						} DimList
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
IfStat			:  IF OPPAR {tabular(); printf("if("); tab++;} Expression  CLPAR {printf(")\n");}
				{
					if($4!=LOGICO)
						Incompatibilidade("Expressao do comando 'if' deve ser logica");
				}
					Statement {tab--;} ElseStat
				;
ElseStat		:  
				|  ELSE {tabular(); printf("else\n"); tab++;} Statement {tab--;}
				;
WhileStat   	:  WHILE OPPAR {tabular(); printf("while(");} Expression CLPAR {printf(")");} 
				{
					if($4!=LOGICO)
						Incompatibilidade("Expressao do comando 'while' deve ser logica");
				}
					Statement
				;
RepeatStat  	:  REPEAT {tabular(); printf("repeat ");} Statement  WHILE OPPAR {printf("while(");} Expression CLPAR SCOLON {printf(");\n");}
				{
					if($7!=LOGICO)
						Incompatibilidade("Expressao do comando 'do repeat' deve ser logica");
				}
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
AssignStat  	: {tabular();} Variable {if($2 != NULL) $2->inic = $2->ref = VERDADE;} ASSIGN {printf(" = ");} Expression SCOLON {printf(";\n");}
				{
					if($2->tvar==INTEIRO && ($6!=INTEIRO && $6!= CARACTERE))
						Incompatibilidade("Lado improprio para comando de atribuicao");
					if($2->tvar==REAL && ($6!=INTEIRO && $6!=REAL && $6!= CARACTERE))
						Incompatibilidade("Lado improprio para comando de atribuicao");
					if($2->tvar==CARACTERE && ($6!=INTEIRO && $6!= CARACTERE))
						Incompatibilidade("Lado improprio para comando de atribuicao");
					if($2->tvar==LOGICO && $6!=LOGICO)
						Incompatibilidade("Lado improprio para comando de atribuicao");
				}
				;
ExprList		:  Expression
				|  ExprList COMMA {printf(", ");} Expression
				;
Expression  	:  AuxExpr1
				|  Expression OR {printf(" || ");} AuxExpr1
				{
					if($1!=LOGICO || $4!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					$$=LOGICO;
				}
				;
AuxExpr1    	:  AuxExpr2
				|  AuxExpr1 AND {printf(" && ");} AuxExpr2
				{
					if($1!=LOGICO || $4!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					$$=LOGICO;
				}
				;
AuxExpr2    	:  AuxExpr3
				|  NOT {printf("!");} AuxExpr3
				{
					if($3!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					$$=LOGICO;
				}
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
				{
					switch($2){
						case LT: case LE: case GT: case GE:
							if($1!=INTEIRO && $1!=REAL && $1!=CARACTERE
								|| $4!=INTEIRO && $4!=REAL && $4!=CARACTERE)
								Incompatibilidade("Operando improprio para operador relacional");
								break;
						case EQ: case NE:
							//Se for logico, o outro operando também deve ser
							if($1 == LOGICO && $4 != LOGICO || $1 != LOGICO && $4 == LOGICO)
								Incompatibilidade("Operador improprio para operador relacional");
							break;
					}
					$$=LOGICO;
				}
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
				{
					if($1!=INTEIRO && $1!=REAL && $1!=CARACTERE
						|| $4!=INTEIRO && $4!=REAL && $4!=CARACTERE)
						Incompatibilidade("Operando improprio para operador aritmetico");
					if($1==REAL || $4==REAL)
						$$=REAL;
					else
						$$=INTEIRO;
				}
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
				{
					switch($2){
						case MU: case DI:
							if($1!=INTEIRO && $1!=REAL && $1!=CARACTERE
								|| $4!=INTEIRO && $4!=REAL && $4!=CARACTERE)
								Incompatibilidade("Operando improprio para operador aritmetico");
							if($1==REAL || $4==REAL)
								$$=REAL;
							else
								$$=INTEIRO;
							break;
							case RE: 
							printf(" %% ");
							if($1!=INTEIRO && $1!=CARACTERE || $4!=INTEIRO && $4!=CARACTERE)
								Incompatibilidade("Operando improprio para operador resto");
							$$=INTEIRO;
							break;
					}
				}
				;
Factor			:  Variable {
								if($1 != NULL){
									$1->ref = VERDADE;
									$$ = $1->tvar;
								}
							}
				|  INTCT {printf("%d", $1); $$ = INTEIRO;}
				|  FLOATCT {printf("%g", $1); $$ = REAL;}
				|  CHARCT {printf("'%s'", $1); $$ = CARACTERE;}
            	|  TRUE {printf("true"); $$ = LOGICO;}
				|  FALSE {printf("false"); $$ = LOGICO;}
				|  NEG {printf("!");} Factor 
					{
						if($3 != INTEIRO && $3!= REAL && $3!=CARACTERE)
							Incompatibilidade("Operando improprio para menos unario");
						if($3 == REAL)
							$$ = REAL;
						else
							$$ = INTEIRO;
					}
            	|  OPPAR {printf("(");} Expression  CLPAR {printf(")"); $$=$3;}
				|  FuncCall
				;
Variable		:  ID	{
							printf("%s", $1);
							simb=ProcuraSimb($1);
							if(simb == NULL) 
								NaoDeclarado($1); 
							else 
								if(simb->tid != IDVAR)
									TipoInadequado($1);
						} 
					SubscrList {$$=simb;}  
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

/* Inicializa a tabela de simbolos */
void InicTabSimb(){
	int i;
	for(i=0;i<NCLASSHASH;i++)
		tabsimb[i] = NULL;
}

/*
	ProcuraSimb(cadeia): Procura cadeia na tabela de simbolos;
	Caso ela ali esteja, retorna um ponteiro para a sua celula;
	Caso contrário, retorna NULL.

*/
simbolo ProcuraSimb (char *cadeia) {
	simbolo s; int i;
	i = hash (cadeia);
	for (s = tabsimb[i]; (s!=NULL) && strcmp(cadeia, s->cadeia); s = s->prox);
	return s;
}

/*
	InsereSimb (cadeia, tid, tvar): Insere cadeia na tabela de
	simbolos, com tid como tipo de identificador e com tvar como
	tipo de variavel; Retorna um ponteiro para a celula inserida
 */

simbolo InsereSimb (char *cadeia, int tid, int tvar) {
	int i; simbolo aux, s;
	i = hash (cadeia); aux = tabsimb[i];
	s = tabsimb[i] = (simbolo) malloc (sizeof (celsimb));
	s->cadeia = (char*) malloc ((strlen(cadeia)+1) * sizeof(char));
	strcpy (s->cadeia, cadeia);
	s->tid = tid;		s->tvar = tvar;
	s->inic = FALSO;	s->ref = FALSO;
	s->prox = aux;	return s;
}

/*
	hash (cadeia): funcao que determina e retorna a classe
	de cadeia na tabela de simbolos implementada por hashing
 */

int hash (char *cadeia) {
	int i, h;
	for (h = i = 0; cadeia[i]; i++) {h += cadeia[i];}
	h = h % NCLASSHASH;
	return h;
}

/* ImprimeTabSimb: Imprime todo o conteudo da tabela de simbolos  */

void ImprimeTabSimb () {
	int i; simbolo s;
	printf ("\n\n   TABELA  DE  SIMBOLOS:\n\n");
	for (i = 0; i < NCLASSHASH; i++)
		if (tabsimb[i]) {
			printf ("Classe %d:\n", i);
			for (s = tabsimb[i]; s!=NULL; s = s->prox){
				printf ("  (%s, %s", s->cadeia,  nometipid[s->tid]);
				if (s->tid == IDVAR)
					printf (", %s, %d, %d", 
						nometipvar[s->tvar], s->inic, s->ref);
				printf(")\n");
			}
		}
}

/*  Mensagens de erros semanticos  */

void DeclaracaoRepetida (char *s) {
	printf ("\n\n***** Declaracao Repetida: %s *****\n\n", s);
}

void NaoDeclarado (char *s) {
printf ("\n\n***** Identificador Nao Declarado: %s *****\n\n", s);
}

void TipoInadequado (char *s) {
printf 
("\n\n***** Identificador de Tipo Inadequado: %s *****\n\n", s);
}

void VerificaInicRef(){
	int i;
	simbolo s;
	for (i = 0; i < NCLASSHASH; i++)
		if (tabsimb[i]) {
			for (s = tabsimb[i]; s!=NULL; s = s->prox){
				if(s->tid == IDVAR){
					if(s->ref == FALSO)
						printf("%s nao referenciado\n", s->cadeia);
					if(s->inic == FALSO)
						printf("%s nao inicializado\n", s->cadeia);
				}
			}
		}
}

void Incompatibilidade(char *s){
	printf ("\n\n***** Incompatibilidade: %s *****\n\n", s);
}


