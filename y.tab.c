#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "build.y"
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
#define IDVOID		0
#define IDPROG		1
#define IDVAR		2
#define	IDFUNC		3
#define	IDPROC		4

/* Definicao dos tipos de passagem de parametros*/
#define PARAMVAL	1
#define PARAMREF	2

/* Definicao dos tipos de variaveis */
#define	NAOVAR		0
#define	INTEIRO		1
#define	LOGICO		2
#define	REAL		3
#define	CARACTERE	4
#define VOID		5

/* Definicao de outras constantes */
#define	NCLASSHASH	23
#define	VERDADE		1
#define	FALSO		0
#define MAXDIMS		10

/* Strings para nomes dos tipos de identificadores*/
char *nometipid[5] = {" ", "IDPROG", "IDVAR", "IDFUNC", "IDPROC"};

/* Strings para nomes dos tipos de variaveis */
char *nometipvar[6]={"NAOVAR", "INTEIRO", "LOGICO", "REAL", "CARACTERE", "VOID"};

/* Declaracoes para a tabela de simbolos */
typedef struct celsimb celsimb;
typedef celsimb *simbolo;
typedef struct elemlistsimb elemlistsimb;
typedef elemlistsimb *listsimb;
struct celsimb {
	char *cadeia;
	int tid, tvar, tparam, ndims, dims[MAXDIMS+1], nparams;
	char inic, ref, array, param;
	simbolo escopo, prox;
	listsimb listvar, listparam, listfunc;
};
struct elemlistsimb {
	simbolo simb;
	listsimb prox;
};

/* Lista de tipos */
typedef struct celtiponoh celtiponoh;
typedef celtiponoh *tiponoh;
struct celtiponoh{
	int tipo;
	tiponoh prox;
};
tiponoh listatipos;

/* Variaveis globais para a tabela de simbolos e analise semantica */
simbolo tabsimb[NCLASSHASH];
simbolo simb;
simbolo escopo, escglobal;
int tipocorrente;
int declparam;

/* Prototipos das funcoes para a tabela de simbolos e analise semantica */
void InicTabSimb(void);
void ImprimeTabSimb(void);
simbolo InsereSimb(char *,int,int,simbolo);
int hash(char *);
simbolo ProcuraSimb(char *,simbolo);
void DeclaracaoRepetida(char *);
void TipoInadequado(char *);
void NaoDeclarado(char *);
void VerificaInicRef(void);
void Incompatibilidade(char *);
void Esperado(char *);
void NaoEsperado(char *);
void ErroLinguagem(char *);
void ErroInterno(char *);
void AdicionarListaTipo(int);
void LimparListaTipos(void);
void VerificarParams(listsimb);
void VerificarCompatibilidade(const char *, int, int);
void VerificarFuncao(char *, int);

int tab = 0;
void tabular (void);
#line 106 "build.y"
typedef union {
	char string[50];
	int atr, valint;
	float valreal;
	char carac;
	simbolo simb;
	int tipoexpr;
	int nsubscr;
	int nparams;
} YYSTYPE;
#line 127 "y.tab.c"
#define CALL 257
#define CHAR 258
#define ELSE 259
#define FALSE 260
#define FLOAT 261
#define FOR 262
#define FUNCTION 263
#define IF 264
#define INT 265
#define LOGIC 266
#define PROCEDURE 267
#define PROGRAM 268
#define READ 269
#define REPEAT 270
#define RETURN 271
#define TRUE 272
#define VAR 273
#define WHILE 274
#define WRITE 275
#define ID 276
#define INTCT 277
#define CHARCT 278
#define FLOATCT 279
#define STRING 280
#define OR 281
#define AND 282
#define NOT 283
#define RELOP 284
#define ADOP 285
#define MULTOP 286
#define NEG 287
#define OPPAR 288
#define CLPAR 289
#define OPBRAK 290
#define CLBRAK 291
#define OPBRACE 292
#define CLBRACE 293
#define SCOLON 294
#define COMMA 295
#define ASSIGN 296
#define INVAL 297
#define LOWER_THAN_ELSE 298
#define YYERRCODE 256
short yylhs[] = {                                        -1,
   13,    0,   12,   17,   12,   16,   16,   18,   19,   19,
   19,   19,   20,   22,   20,   24,   21,   23,   23,   25,
   14,   14,   26,   27,   27,   30,   32,   28,   31,   31,
   34,   29,   35,   29,   33,   37,   33,   36,   39,   15,
   38,   38,   40,   40,   40,   40,   40,   40,   40,   40,
   40,   40,   40,   50,   51,   52,   54,   41,   53,   55,
   53,   56,   57,   58,   42,   59,   60,   61,   43,   62,
   63,   64,   65,   66,   67,   44,   69,   45,   68,   70,
   68,   72,   46,   71,   74,   71,   73,   73,   75,   48,
   76,   48,   77,   49,   78,   49,   79,   80,   81,   47,
   10,   82,   10,    2,   83,    2,    3,   84,    3,    4,
   85,    4,    5,   86,    5,    6,   87,    6,    7,   88,
    7,    8,    8,    8,    8,    8,    8,   89,    8,   90,
    8,    8,   91,    1,    9,    9,   93,   94,   92,   95,
   11,   96,   11,
};
short yylen[] = {                                         2,
    0,    7,    0,    0,    3,    1,    2,    3,    1,    1,
    1,    1,    1,    0,    4,    0,    3,    0,    2,    3,
    0,    2,    3,    1,    1,    0,    0,    7,    2,    3,
    0,    6,    0,    7,    1,    0,    4,    2,    0,    4,
    0,    2,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    0,    0,    0,    0,   10,    0,    0,
    3,    0,    0,    0,    8,    0,    0,    0,   10,    0,
    0,    0,    0,    0,    0,   19,    0,    6,    1,    0,
    4,    0,    6,    1,    0,    4,    1,    1,    0,    6,
    0,    7,    0,    3,    0,    4,    0,    0,    0,    7,
    1,    0,    4,    1,    0,    4,    1,    0,    4,    1,
    0,    3,    1,    0,    4,    1,    0,    4,    1,    0,
    4,    1,    1,    1,    1,    1,    1,    0,    3,    0,
    4,    1,    0,    3,    0,    2,    0,    0,    5,    0,
    4,    0,    5,
};
short yydefred[] = {                                      0,
    0,    0,    0,    1,    0,    4,   21,    0,    0,   11,
   10,    9,   12,    0,    6,    0,   26,    0,   39,    2,
   22,    0,   24,   25,    7,   16,    0,   13,    0,    0,
   41,    0,   18,    8,   14,    0,    0,    0,   23,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   66,    0,
    0,    0,   40,   53,   43,   42,   44,   45,   46,   47,
   48,   49,   50,   51,   52,    0,    0,   19,   15,   27,
    0,    0,    0,   35,    0,   70,   54,   77,    0,    0,
    0,   62,   82,  133,    0,    0,    0,   32,   38,    0,
   36,    0,    0,    0,    0,    0,   94,  127,  126,    0,
  123,  125,  124,  111,  128,  130,  122,    0,    0,  107,
  110,    0,    0,  119,  132,    0,    0,  135,   98,   20,
    0,   28,    0,   34,    0,    0,    0,    0,    0,   79,
    0,    0,    0,    0,    0,    0,  105,   96,  108,  114,
  117,  120,    0,   87,    0,    0,   84,    0,    0,   29,
    0,   37,    0,    0,    0,   71,   55,    0,   80,   67,
    0,    0,  112,  129,    0,    0,    0,    0,    0,    0,
   63,    0,   85,  137,  136,    0,   30,   90,    0,  102,
    0,   56,   78,    0,    0,  141,    0,  131,    0,  109,
    0,    0,  121,   64,   83,    0,    0,   99,   92,    0,
    0,    0,   81,    0,  143,    0,   86,    0,  100,    0,
   72,   57,    0,   65,  138,    0,    0,   68,  139,    0,
   60,   58,   69,   73,    0,    0,   61,    0,   74,    0,
    0,   75,    0,   76,
};
short yydgoto[] = {                                       2,
  107,  145,  109,  110,  111,  112,  113,  114,  148,  155,
  115,    7,    5,    9,   55,   14,    8,   15,   72,   27,
   28,   41,   40,   33,   68,   21,   22,   23,   24,   29,
  122,   87,   73,   43,   44,   74,  125,   38,   31,   56,
   57,   58,   59,   60,   61,   62,   63,   64,   65,   94,
  182,  202,  222,  217,  225,  116,  194,  206,   79,  185,
  223,   93,  181,  216,  226,  230,  233,  131,   95,  184,
  146,  117,  147,  196,  126,  127,   80,   81,   66,  149,
  209,  200,  166,  167,  134,  168,  169,  170,  135,  136,
  118,  175,  197,  219,  161,  162,
};
short yysindex[] = {                                   -242,
 -223,    0, -229,    0, -194,    0,    0,   23, -257,    0,
    0,    0,    0,   23,    0, -181,    0, -178,    0,    0,
    0, -194,    0,    0,    0,    0, -232,    0,   23, -172,
    0, -215,    0,    0,    0, -149,    0, -219,    0, -147,
 -181, -130, -150,   23, -135, -126, -117,  -82,    0,    0,
  -71,  -70,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -124,  -90,    0,    0,    0,
 -102,  -68, -281,    0,  -69,    0,    0,    0, -203,  -84,
  -76,    0,    0,    0,  -75,  -59, -157,    0,    0,  -74,
    0,    0, -124,  -76, -124,  -52,    0,    0,    0,  -65,
    0,    0,    0,    0,    0,    0,    0, -269,  -54,    0,
    0,  -80,  -53,    0,    0,  -76,  -97,    0,    0,    0,
  -57,    0, -259,    0,   23,  -51,  -76,  -61, -199,    0,
 -231,  -44,    0,  -63,  -63,  -76,    0,    0,    0,    0,
    0,    0, -170,    0,  -33, -211,    0,  -41,  -76,    0,
  -40,    0,  -35,  -33, -196,    0,    0,  -32,    0,    0,
  -36,  -76,    0,    0, -159,  -76,  -76,  -63,  -63,  -63,
    0,  -31,    0,    0,    0, -250,    0,    0,  -30,    0,
  -76,    0,    0, -124,  -76,    0, -195,    0,  -54,    0,
  -19,  -53,    0,    0,    0,  -97,  -63,    0,    0,  -76,
 -248, -203,    0, -158,    0, -203,    0, -137,    0,  -33,
    0,    0,  -26,    0,    0,  -76,   10,    0,    0, -234,
    0,    0,    0,    0, -203, -124,    0,  -22,    0,  -76,
 -139,    0, -203,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0, -243,    0,    0,    0,    0,    0,
    0,    0,    0, -187,    0,    0,    0,    0,    0,    0,
    0,  -15,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -151,    2,    0, -121,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -191,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    2,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -143,    0,    0,    0,    0,    0,    0,    0,  -39,
    0,    0,    0,    0,    0,    0,    0,    0,  -96,    0,
    0, -169,  -24,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -111,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -136,    0,    0,  -55,    0,    0,
    0,    0,    0, -101,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   -2,    0,
 -125,   -9,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    2,    0,    0,    0,    2,    0,    0,    0, -100,
    0,    0,    0,    0,    0,    0, -253,    0,    0,    0,
    0,    0,    0,    0,    2,    0,    0,    0,    0,    0,
    0,    0,    2,    0,
};
short yygindex[] = {                                      0,
  -66,  -79,  117,  123,  157, -165,  125, -128,    0,  133,
    0,  274,    0,    0,   -4,    0,    0,  283,    5,    0,
  257,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  212,    0,    0,  175,    0,    0,    0,  -78,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  105,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 301
short yytable[] = {                                      85,
   96,  108,  191,   59,   20,   17,  164,   90,   59,   18,
   59,  137,   16,   91,  129,   59,   59,   59,   16,    3,
   59,   59,   59,    3,  138,    1,  128,   39,  130,  151,
  137,  208,  137,   36,   19,   91,  143,   45,   59,   59,
   59,  193,   46,  198,   47,  211,  137,  154,    3,   48,
   49,   50,    3,   45,   51,   52,  165,  158,   46,  224,
   47,   34,   35,  159,    4,   48,   49,   50,   95,  176,
   51,   52,   19,   53,   54,    5,   19,  172,    6,    5,
   95,  137,  154,  173,   95,   95,   95,   95,   19,  157,
   54,   95,  179,  205,   26,   95,   95,   30,  180,  180,
   10,  201,   93,   11,    5,  204,   33,   12,   13,   33,
  137,  113,  113,   33,   33,   37,   91,  203,  171,  113,
  210,  137,  137,  212,  113,  113,   42,  214,   91,  188,
  213,  121,   91,   91,   91,   91,  220,   31,   71,   91,
   75,  137,   67,   91,   91,   89,  227,  141,  142,  232,
  231,   84,   88,  215,  234,  115,  115,   70,   88,  228,
  142,   76,   98,  115,  142,  142,  142,  142,  115,  115,
   77,  142,   17,   17,   99,  142,  142,  140,  100,  101,
  102,  103,  144,   98,  104,  104,   86,  101,  103,  105,
  106,   88,  104,  101,  103,   99,   98,  104,  104,  100,
  101,  102,  103,  140,  141,   78,  104,   89,   99,   97,
  105,  106,  100,  101,  102,  103,   82,   83,   92,  124,
  119,  132,  133,  105,  106,  134,  134,  139,  134,  134,
  134,  120,  142,  134,  156,  134,  150,  153,  134,  134,
  134,  133,  133,  160,  133,  133,  133,  137,  174,  133,
  133,  133,  186,  177,  133,  133,  116,  116,  178,  116,
  116,  183,  195,  199,  116,  141,  116,  218,  221,  116,
  116,  118,  118,  229,  118,  118,    3,   97,  106,  118,
   10,  118,  189,   11,  118,  118,  106,   12,   13,  190,
  163,  106,  106,  192,  187,   32,   25,   69,  123,  152,
  207,
};
short yycheck[] = {                                      66,
   79,   81,  168,  257,    9,  263,  135,  289,  262,  267,
  264,  281,    8,  295,   94,  269,  270,  271,   14,  263,
  274,  275,  276,  267,  294,  268,   93,   32,   95,  289,
  281,  197,  281,   29,  292,  295,  116,  257,  292,  293,
  294,  170,  262,  294,  264,  294,  281,  127,  292,  269,
  270,  271,  276,  257,  274,  275,  136,  289,  262,  294,
  264,  294,  295,  295,  294,  269,  270,  271,  260,  149,
  274,  275,  292,  293,  294,  263,  292,  289,  273,  267,
  272,  281,  162,  295,  276,  277,  278,  279,  292,  289,
  294,  283,  289,  289,  276,  287,  288,  276,  295,  295,
  258,  181,  294,  261,  292,  185,  258,  265,  266,  261,
  281,  281,  282,  265,  266,  288,  260,  184,  289,  289,
  200,  281,  281,  202,  294,  295,  276,  206,  272,  289,
  289,  289,  276,  277,  278,  279,  216,  289,  289,  283,
  276,  281,  290,  287,  288,  289,  225,  285,  260,  289,
  230,  276,  289,  291,  233,  281,  282,  288,  295,  226,
  272,  288,  260,  289,  276,  277,  278,  279,  294,  295,
  288,  283,  294,  295,  272,  287,  288,  289,  276,  277,
  278,  279,  280,  260,  281,  283,  277,  289,  289,  287,
  288,  294,  289,  295,  295,  272,  260,  294,  295,  276,
  277,  278,  279,  284,  285,  288,  283,  276,  272,  294,
  287,  288,  276,  277,  278,  279,  288,  288,  288,  294,
  296,  274,  288,  287,  288,  281,  282,  282,  284,  285,
  286,  291,  286,  289,  296,  291,  294,  289,  294,  295,
  296,  281,  282,  288,  284,  285,  286,  281,  290,  289,
  290,  291,  289,  294,  294,  295,  281,  282,  294,  284,
  285,  294,  294,  294,  289,  285,  291,  294,  259,  294,
  295,  281,  282,  296,  284,  285,  292,  276,  281,  289,
  258,  291,  166,  261,  294,  295,  289,  265,  266,  167,
  134,  294,  295,  169,  162,   22,   14,   41,   87,  125,
  196,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 298
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"CALL","CHAR","ELSE","FALSE",
"FLOAT","FOR","FUNCTION","IF","INT","LOGIC","PROCEDURE","PROGRAM","READ",
"REPEAT","RETURN","TRUE","VAR","WHILE","WRITE","ID","INTCT","CHARCT","FLOATCT",
"STRING","OR","AND","NOT","RELOP","ADOP","MULTOP","NEG","OPPAR","CLPAR",
"OPBRAK","CLBRAK","OPBRACE","CLBRACE","SCOLON","COMMA","ASSIGN","INVAL",
"LOWER_THAN_ELSE",
};
char *yyrule[] = {
"$accept : Prog",
"$$1 :",
"Prog : PROGRAM ID SCOLON $$1 Decls SubProgs CompStat",
"Decls :",
"$$2 :",
"Decls : VAR $$2 DeclList",
"DeclList : Declaration",
"DeclList : DeclList Declaration",
"Declaration : Type ElemList SCOLON",
"Type : INT",
"Type : FLOAT",
"Type : CHAR",
"Type : LOGIC",
"ElemList : Elem",
"$$3 :",
"ElemList : ElemList COMMA $$3 Elem",
"$$4 :",
"Elem : ID $$4 DimList",
"DimList :",
"DimList : DimList Dim",
"Dim : OPBRAK INTCT CLBRAK",
"SubProgs :",
"SubProgs : SubProgs SubProgDecl",
"SubProgDecl : Header Decls CompStat",
"Header : FuncHeader",
"Header : ProcHeader",
"$$5 :",
"$$6 :",
"FuncHeader : FUNCTION $$5 Type ID OPPAR $$6 FuncHeaderAux",
"FuncHeaderAux : CLPAR SCOLON",
"FuncHeaderAux : ParamList CLPAR SCOLON",
"$$7 :",
"ProcHeader : PROCEDURE ID OPPAR $$7 CLPAR SCOLON",
"$$8 :",
"ProcHeader : PROCEDURE ID OPPAR $$8 ParamList CLPAR SCOLON",
"ParamList : Parameter",
"$$9 :",
"ParamList : ParamList COMMA $$9 Parameter",
"Parameter : Type ID",
"$$10 :",
"CompStat : OPBRACE $$10 StatList CLBRACE",
"StatList :",
"StatList : StatList Statement",
"Statement : CompStat",
"Statement : IfStat",
"Statement : WhileStat",
"Statement : RepeatStat",
"Statement : ForStat",
"Statement : ReadStat",
"Statement : WriteStat",
"Statement : AssignStat",
"Statement : CallStat",
"Statement : ReturnStat",
"Statement : SCOLON",
"$$11 :",
"$$12 :",
"$$13 :",
"$$14 :",
"IfStat : IF OPPAR $$11 Expression CLPAR $$12 $$13 Statement $$14 ElseStat",
"ElseStat :",
"$$15 :",
"ElseStat : ELSE $$15 Statement",
"$$16 :",
"$$17 :",
"$$18 :",
"WhileStat : WHILE OPPAR $$16 Expression CLPAR $$17 $$18 Statement",
"$$19 :",
"$$20 :",
"$$21 :",
"RepeatStat : REPEAT $$19 Statement WHILE OPPAR $$20 Expression CLPAR SCOLON $$21",
"$$22 :",
"$$23 :",
"$$24 :",
"$$25 :",
"$$26 :",
"$$27 :",
"ForStat : FOR OPPAR $$22 Variable ASSIGN $$23 Expression SCOLON $$24 Expression SCOLON $$25 Variable ASSIGN $$26 Expression CLPAR $$27 Statement",
"$$28 :",
"ReadStat : READ OPPAR $$28 ReadList CLPAR SCOLON",
"ReadList : Variable",
"$$29 :",
"ReadList : ReadList COMMA $$29 Variable",
"$$30 :",
"WriteStat : WRITE OPPAR $$30 WriteList CLPAR SCOLON",
"WriteList : WriteElem",
"$$31 :",
"WriteList : WriteList COMMA $$31 WriteElem",
"WriteElem : STRING",
"WriteElem : Expression",
"$$32 :",
"CallStat : CALL ID OPPAR $$32 CLPAR SCOLON",
"$$33 :",
"CallStat : CALL ID OPPAR $$33 ExprList CLPAR SCOLON",
"$$34 :",
"ReturnStat : RETURN $$34 SCOLON",
"$$35 :",
"ReturnStat : RETURN $$35 Expression SCOLON",
"$$36 :",
"$$37 :",
"$$38 :",
"AssignStat : $$36 Variable ASSIGN $$37 Expression SCOLON $$38",
"ExprList : Expression",
"$$39 :",
"ExprList : ExprList COMMA $$39 Expression",
"Expression : AuxExpr1",
"$$40 :",
"Expression : Expression OR $$40 AuxExpr1",
"AuxExpr1 : AuxExpr2",
"$$41 :",
"AuxExpr1 : AuxExpr1 AND $$41 AuxExpr2",
"AuxExpr2 : AuxExpr3",
"$$42 :",
"AuxExpr2 : NOT $$42 AuxExpr3",
"AuxExpr3 : AuxExpr4",
"$$43 :",
"AuxExpr3 : AuxExpr4 RELOP $$43 AuxExpr4",
"AuxExpr4 : Term",
"$$44 :",
"AuxExpr4 : AuxExpr4 ADOP $$44 Term",
"Term : Factor",
"$$45 :",
"Term : Term MULTOP $$45 Factor",
"Factor : Variable",
"Factor : INTCT",
"Factor : FLOATCT",
"Factor : CHARCT",
"Factor : TRUE",
"Factor : FALSE",
"$$46 :",
"Factor : NEG $$46 Factor",
"$$47 :",
"Factor : OPPAR $$47 Expression CLPAR",
"Factor : FuncCall",
"$$48 :",
"Variable : ID $$48 SubscrList",
"SubscrList :",
"SubscrList : SubscrList Subscript",
"$$49 :",
"$$50 :",
"Subscript : OPBRAK $$49 AuxExpr4 CLBRAK $$50",
"$$51 :",
"FuncCall : ID OPPAR $$51 CLPAR",
"$$52 :",
"FuncCall : ID OPPAR $$52 ExprList CLPAR",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 589 "build.y"
#include "lex.yy.c"

/* Inicializa a tabela de simbolos */
void InicTabSimb(){
	int i;
	for(i=0;i<NCLASSHASH;i++)
		tabsimb[i] = NULL;
}

/*
	ProcuraSimb(cadeia, escopo): Procura cadeia e escopo na tabela de simbolos;
	Caso ela ali esteja, retorna um ponteiro para a sua celula;
	Caso contrário, retorna NULL.

*/
simbolo ProcuraSimb (char *cadeia, simbolo escopo) {
	simbolo s; int i;
	i = hash (cadeia);
	for (s = tabsimb[i]; (s != NULL) && (strcmp(cadeia, s->cadeia) != 0 || (escopo != s->escopo)); s = s->prox);
	return s;
}

/*
	InsereListSimb(simbolo, listsimb*): Insere
	simbolo numa lista de simbolos
 */
 
void InsereListSimb(simbolo simb, listsimb *lista) {
	listsimb l = (listsimb) malloc (sizeof (elemlistsimb));
	l->simb = simb;
	l->prox = *lista;
	*lista = l;
}

/*
	InsereSimb (cadeia, tid, tvar, escopo): Insere cadeia na tabela de
	simbolos, com tid como tipo de identificador, com tvar como
	tipo de variavel e com escopo como escopo; Retorna um ponteiro para a celula inserida
 */

simbolo InsereSimb (char *cadeia, int tid, int tvar, simbolo escopo) {
	int i; simbolo aux, s;
	i = hash (cadeia); aux = tabsimb[i];
	s = tabsimb[i] = (simbolo) malloc (sizeof (celsimb));
	s->cadeia = (char*) malloc ((strlen(cadeia)+1) * sizeof(char));
	strcpy (s->cadeia, cadeia);
	s->tid = tid;		s->tvar = tvar;
	s->nparams = s->ndims = 0;
	s->listfunc = s->listparam = s->listvar = NULL;
	s->escopo = escopo;
	s->prox = aux;
	if (declparam) {
		s->inic = s->ref = s->param = VERDADE;
		if (s->tid == IDVAR)
			InsereListSimb(s, &escopo->listparam);
		s->escopo->nparams++;
	}
	else {
		s->inic = s->ref = s->param = FALSO;
		if (s->tid == IDVAR)
			InsereListSimb(s, &escopo->listvar);
	}
	if (tid == IDFUNC || tid == IDPROC) {
		InsereListSimb(s, &escopo->listfunc);
	}
	return s;
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
	int i, j; simbolo s;
	printf ("\n\n   TABELA  DE  SIMBOLOS:\n\n");
	for (i = 0; i < NCLASSHASH; i++)
		if (tabsimb[i]) {
			printf ("Classe %d:\n", i);
			for (s = tabsimb[i]; s!=NULL; s = s->prox){
				printf ("  %s(%s %s), escopo: ", s->cadeia,  nometipid[s->tid],  nometipvar[s->tvar]);
				if (s->escopo == NULL) printf("null\n");
				else printf("%s\n", s->escopo->cadeia);
				if (s->listparam != NULL) {
					printf("\tParametros (%d): ", s->nparams);
					listsimb l = s->listparam;
					while(l != NULL) {
						printf(" %s(%s)", l->simb->cadeia, nometipvar[l->simb->tvar]);
						l = l->prox;
					}
					printf("\n");
				}
				if (s->listfunc != NULL) {
					printf("\tFuncoes: ");
					listsimb l = s->listfunc;
					while(l != NULL) {
						printf(" %s(%s)", l->simb->cadeia, nometipvar[l->simb->tvar]);
						l = l->prox;
					}
					printf("\n");
				}
				if (s->listvar != NULL) {
					printf("\tVariaveis: ");
					listsimb l = s->listvar;
					while(l != NULL) {
						printf(" %s(%s)", l->simb->cadeia, nometipvar[l->simb->tvar]);
						l = l->prox;
					}
					printf("\n");
				}
				if (s->tid == IDVAR){
					printf ("\tInicializado: %d, Referenciado: %d\n", s->inic, s->ref);
					if(s->array == VERDADE){
						printf("\tArray: (%d dimensoes):", s->ndims);
						for(j=1; j <= s->ndims; j++)
							printf(" %d", s->dims[j]);
						printf("\n");
					}
				}
				printf("\n");
			}
		}
}

void VerificaInicRef(){
	int i;
	simbolo s;
	for (i = 0; i < NCLASSHASH; i++) {
		if (tabsimb[i]) {
			for (s = tabsimb[i]; s!=NULL; s = s->prox){
				if(s->tid == IDVAR){
					if(s->ref == FALSO)
						printf("%s do escopo %s nao referenciado\n", s->cadeia, s->escopo->cadeia);
					if(s->inic == FALSO)
						printf("%s do escopo %s nao inicializado\n", s->cadeia, s->escopo->cadeia);
				}
			}
		}
	}
	
}

void AdicionarListaTipo(int tipo) {
	tiponoh n = (tiponoh) malloc (sizeof (celtiponoh));
	n->tipo = tipo;
	n->prox = listatipos;
	listatipos = n;
}

void LimparListaTipos(){
	tiponoh n;
	while(listatipos != NULL) {
		n = listatipos;
		listatipos = listatipos->prox;
		free(n);
	}
}

void VerificarCompatibilidade(const char *mensagem, int tipo1, int tipo2) {
	char buffer[200];
	buffer[0] = 0;
	if(tipo1==INTEIRO && (tipo2!=INTEIRO && tipo2!= CARACTERE))
		sprintf(buffer, "[%s] Compatibilidade de inteiro: esperado inteiro ou caractere.", mensagem);
	else if(tipo1==REAL && (tipo2!=INTEIRO && tipo2!=REAL && tipo2!= CARACTERE))
		sprintf(buffer, "[%s] Compatibilidade de real: esperado real, inteiro ou caractere.", mensagem);
	else if(tipo1==CARACTERE && (tipo2!=INTEIRO && tipo2!= CARACTERE))
		sprintf(buffer, "[%s] Compatibilidade de caractere: esperado inteiro ou caractere.", mensagem);
	else if(tipo1==LOGICO && tipo2!=LOGICO)
		sprintf(buffer, "[%s] Compatibilidade de logico: esperado logico.", mensagem);
	if (buffer[0] != 0)
		Incompatibilidade(buffer);
}

void VerificarParams(listsimb p) {
	tiponoh q = listatipos;
	while(q != NULL && p != NULL){
		VerificarCompatibilidade("param", p->simb->tvar, q->tipo);
		q = q->prox;
		p = p->prox;
	}
	if (p != NULL || q != NULL)
		ErroInterno("Erro interno de logica do compilador.");
}

void VerificarFuncao(char * id, int nparams) {
	simbolo s = ProcuraSimb(id, escglobal);
	if (s == NULL) {
		NaoDeclarado("Funcao ou procedimento nao declarado.");
		return;
	}
	simbolo escaux = escopo;
	while(escaux != NULL) {
		if (strcmp(escaux->cadeia, id) == 0)
			ErroLinguagem("Proibida recursividade.");
		escaux = escaux->escopo;
	}
	if(s->tid != IDFUNC && s->tid != IDPROC){
		NaoEsperado("Esperava identificador de funcao.");
	}
	else if(s->nparams != nparams) {
		Incompatibilidade("Quantidade de parametros nao compativel.");
	}
	else {
		VerificarParams(s->listparam);
	}
	LimparListaTipos();
}

/*  Mensagens de erros semanticos  */

void DeclaracaoRepetida (char *s) {
	printf ("\n\n***** Declaracao Repetida: %s *****\n\n", s);
}

void NaoDeclarado (char *s) {
	printf ("\n\n***** Identificador Nao Declarado: %s *****\n\n", s);
}

void TipoInadequado (char *s) {
	printf ("\n\n***** Identificador de Tipo Inadequado: %s *****\n\n", s);
}

void Incompatibilidade(char *s){
	printf ("\n\n***** Incompatibilidade: %s *****\n\n", s);
}

void Esperado (char *s) {
	printf ("\n\n***** Esperado: %s *****\n\n", s);
}

void NaoEsperado (char *s) {
	printf ("\n\n***** Nao Esperado: %s *****\n\n", s);
}

void ErroLinguagem(char *s) {
	printf ("\n\n***** Erro de linguagem: %s *****\n\n", s);
}

void ErroInterno(char *s) {
	printf ("\n\n***** Erro interno: %s *****\n\n", s);
}
#line 814 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 166 "build.y"
{
					InicTabSimb();
					listatipos = NULL;
					declparam = FALSO;
					printf("program %s;\n\n", yyvsp[-1].string);
					escglobal = escopo = InsereSimb(yyvsp[-1].string, IDPROG, NAOVAR, NULL);
				}
break;
case 2:
#line 174 "build.y"
{
					VerificaInicRef();
					ImprimeTabSimb();
				}
break;
case 4:
#line 180 "build.y"
{printf("var\n"); tab++; }
break;
case 5:
#line 180 "build.y"
{tab--;}
break;
case 8:
#line 185 "build.y"
{printf(";\n");}
break;
case 9:
#line 187 "build.y"
{tabular(); printf("int "); tipocorrente = INTEIRO;}
break;
case 10:
#line 188 "build.y"
{tabular(); printf("float "); tipocorrente = REAL;}
break;
case 11:
#line 189 "build.y"
{tabular(); printf("char "); tipocorrente = CARACTERE;}
break;
case 12:
#line 190 "build.y"
{tabular(); printf("logic ");  tipocorrente = LOGICO;}
break;
case 14:
#line 193 "build.y"
{printf(", ");}
break;
case 16:
#line 196 "build.y"
{
					printf("%s", yyvsp[0].string);
					if(ProcuraSimb(yyvsp[0].string, escopo) != NULL)
						DeclaracaoRepetida(yyvsp[0].string);
					else{
						simb = InsereSimb(yyvsp[0].string, IDVAR, tipocorrente, escopo);
						simb->array=FALSO;
						simb->ndims=0;
					}
				}
break;
case 19:
#line 208 "build.y"
{simb->array=VERDADE;}
break;
case 20:
#line 211 "build.y"
{
					printf("[%d]", yyvsp[-1].valint);
					if(yyvsp[-1].valint<=0)
						Esperado("Valor inteiro positivo");
					simb->ndims++;
					simb->dims[simb->ndims]=yyvsp[-1].valint;
				}
break;
case 23:
#line 223 "build.y"
{
					escopo = escopo->escopo;
					if (escopo == NULL) printf("Erro, escopo voltou demais\n");
				}
break;
case 26:
#line 231 "build.y"
{tabular(); printf("function ");}
break;
case 27:
#line 232 "build.y"
{
					printf("%s(", yyvsp[-1].string);
					if (ProcuraSimb(yyvsp[-1].string, escopo) != NULL)
						DeclaracaoRepetida("Funcao com o mesmo nome que uma variavel global");
					escopo = simb = InsereSimb(yyvsp[-1].string, IDFUNC, tipocorrente, escopo);
				}
break;
case 29:
#line 240 "build.y"
{printf(");\n");}
break;
case 30:
#line 241 "build.y"
{printf(");\n");}
break;
case 31:
#line 244 "build.y"
{
					tabular();
					printf("procedure %s(", yyvsp[-1].string);
					if (ProcuraSimb(yyvsp[-1].string, escopo) != NULL)
						DeclaracaoRepetida("Funcao com o mesmo nome que uma variavel global");
					escopo = simb = InsereSimb(yyvsp[-1].string, IDPROC, NAOVAR, escopo);
				}
break;
case 32:
#line 251 "build.y"
{printf(");\n");}
break;
case 33:
#line 253 "build.y"
{
					tabular();
					printf("procedure %s(", yyvsp[-1].string);
					escopo = simb = InsereSimb(yyvsp[-1].string, IDPROC, NAOVAR, escopo);
				}
break;
case 34:
#line 258 "build.y"
{printf(");\n");}
break;
case 36:
#line 261 "build.y"
{printf(", ");}
break;
case 38:
#line 264 "build.y"
{
					printf("%s", yyvsp[0].string);
					declparam = VERDADE;
					simbolo s = ProcuraSimb(yyvsp[0].string, escglobal);
					if (s != NULL && (s->tid == IDFUNC || s->tid == IDFUNC)){
						ErroLinguagem("Subprograma nao pode ser usado como parametro.");
					}
					InsereSimb(yyvsp[0].string, IDVAR, tipocorrente, escopo);
					declparam = FALSO;
				}
break;
case 39:
#line 276 "build.y"
{
					tabular();
					printf("\{\n");
					tab++;
				}
break;
case 40:
#line 282 "build.y"
{
					tab--;
					tabular();
					printf("}\n");
				}
break;
case 53:
#line 293 "build.y"
{printf(";\n");}
break;
case 54:
#line 295 "build.y"
{tabular(); printf("if("); tab++;}
break;
case 55:
#line 295 "build.y"
{printf(")\n");}
break;
case 56:
#line 296 "build.y"
{
					if(yyvsp[-2].tipoexpr!=LOGICO)
						Incompatibilidade("Expressao do comando 'if' deve ser logica");
				}
break;
case 57:
#line 300 "build.y"
{tab--;}
break;
case 60:
#line 303 "build.y"
{tabular(); printf("else\n"); tab++;}
break;
case 61:
#line 303 "build.y"
{tab--;}
break;
case 62:
#line 305 "build.y"
{tabular(); printf("while(");}
break;
case 63:
#line 305 "build.y"
{printf(")\n");}
break;
case 64:
#line 306 "build.y"
{
					if(yyvsp[-2].tipoexpr!=LOGICO)
						Incompatibilidade("Expressao do comando 'while' deve ser logica");
				}
break;
case 66:
#line 312 "build.y"
{tabular(); printf("repeat\n");}
break;
case 67:
#line 312 "build.y"
{tabular(); printf("while(");}
break;
case 68:
#line 312 "build.y"
{printf(");\n");}
break;
case 69:
#line 313 "build.y"
{
					if(yyvsp[-3].tipoexpr!=LOGICO)
						Incompatibilidade("Expressao do comando 'do repeat' deve ser logica");
				}
break;
case 70:
#line 318 "build.y"
{tabular(); printf("for(");}
break;
case 71:
#line 318 "build.y"
{printf(" = ");}
break;
case 72:
#line 319 "build.y"
{
					printf("; ");
					if (yyvsp[-4].simb == NULL) {
						ErroInterno("Variable null.");
					}
					else {
						yyvsp[-4].simb->inic = VERDADE;
						if(yyvsp[-4].simb->tid!=IDVAR || (yyvsp[-4].simb->tvar!=INTEIRO && yyvsp[-4].simb->tvar!=CARACTERE) || yyvsp[-4].simb->array!=FALSO)
							Incompatibilidade("Variavel de inicializacao incompativel para o operador 'for'");
					}
				}
break;
case 73:
#line 330 "build.y"
{printf("; ");}
break;
case 74:
#line 330 "build.y"
{printf(" = ");}
break;
case 75:
#line 331 "build.y"
{
					printf(")\n");
					if (yyvsp[-13].simb == NULL || yyvsp[-4].simb == NULL) {
						ErroInterno("Variable null.");
					}
					else {
						yyvsp[-4].simb->inic = VERDADE;
						if(strcmp(yyvsp[-13].simb->cadeia, yyvsp[-4].simb->cadeia))
							Incompatibilidade("Variavel de atualizacao deve ser a mesma de inicializacao");
						if((yyvsp[-10].tipoexpr != INTEIRO && yyvsp[-10].tipoexpr != CARACTERE) || (yyvsp[-1].tipoexpr != INTEIRO && yyvsp[-1].tipoexpr != CARACTERE) || yyvsp[-7].tipoexpr!=LOGICO)
							Incompatibilidade("Expressoes de tipo inadequado");
					}
				}
break;
case 77:
#line 345 "build.y"
{tabular(); printf("read(");}
break;
case 78:
#line 345 "build.y"
{printf(");\n");}
break;
case 80:
#line 348 "build.y"
{printf(", ");}
break;
case 82:
#line 350 "build.y"
{tabular(); printf("write(");}
break;
case 83:
#line 350 "build.y"
{printf(");\n");}
break;
case 85:
#line 353 "build.y"
{printf(", ");}
break;
case 87:
#line 355 "build.y"
{printf("\"%s\"", yyvsp[0].string);}
break;
case 89:
#line 358 "build.y"
{tabular(); printf("call %s();\n", yyvsp[-1].string); VerificarFuncao(yyvsp[-1].string, 0);}
break;
case 91:
#line 360 "build.y"
{
					tabular();
					printf("call %s(", yyvsp[-1].string);
				}
break;
case 92:
#line 364 "build.y"
{printf(");\n"); VerificarFuncao(yyvsp[-5].string, yyvsp[-2].nparams);}
break;
case 93:
#line 366 "build.y"
{tabular(); printf("return");}
break;
case 94:
#line 367 "build.y"
{
					printf(";\n");
					if (escopo->tid != IDPROG && escopo->tid != IDPROC)
						Incompatibilidade("Tipo de retorno nao deveria ser void");
				}
break;
case 95:
#line 372 "build.y"
{tabular(); printf("return ");}
break;
case 96:
#line 373 "build.y"
{
					printf(";\n");
					if (escopo->tid != IDFUNC)
						Incompatibilidade("Retorno de nao funcao nao deve ter tipo");
					VerificarCompatibilidade("return", escopo->tvar, yyvsp[-1].tipoexpr);
				}
break;
case 97:
#line 380 "build.y"
{tabular();}
break;
case 98:
#line 380 "build.y"
{printf(" = ");}
break;
case 99:
#line 380 "build.y"
{printf(";\n");}
break;
case 100:
#line 381 "build.y"
{
					if (yyvsp[-5].simb == NULL) {
						ErroInterno("Variable null.");
					}
					else {
						yyvsp[-5].simb->inic = VERDADE;
						if(yyvsp[-5].simb->tvar == NAOVAR || yyvsp[-5].simb->tid != IDVAR)
							Esperado("Esperada uma variavel inteira, caractere, real ou logica para atribuicao.");
						VerificarCompatibilidade("assign", yyvsp[-5].simb->tvar, yyvsp[-2].tipoexpr);
					}
				}
break;
case 101:
#line 393 "build.y"
{yyval.nparams=1; AdicionarListaTipo(yyvsp[0].tipoexpr);}
break;
case 102:
#line 394 "build.y"
{printf(", ");}
break;
case 103:
#line 394 "build.y"
{yyval.nparams=yyvsp[-3].nparams+1;  AdicionarListaTipo(yyvsp[0].tipoexpr);}
break;
case 105:
#line 397 "build.y"
{printf(" || ");}
break;
case 106:
#line 398 "build.y"
{
					if(yyvsp[-3].tipoexpr!=LOGICO || yyvsp[0].tipoexpr!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					yyval.tipoexpr=LOGICO;
				}
break;
case 108:
#line 405 "build.y"
{printf(" && ");}
break;
case 109:
#line 406 "build.y"
{
					if(yyvsp[-3].tipoexpr!=LOGICO || yyvsp[0].tipoexpr!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					yyval.tipoexpr=LOGICO;
				}
break;
case 111:
#line 413 "build.y"
{printf("!");}
break;
case 112:
#line 414 "build.y"
{
					if(yyvsp[0].tipoexpr!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					yyval.tipoexpr=LOGICO;
				}
break;
case 114:
#line 422 "build.y"
{
					switch(yyvsp[0].atr){
						case LT: printf(" < "); break;
						case LE: printf(" <= "); break;
						case GT: printf(" > "); break;
						case GE: printf(" >= "); break;
						case EQ: printf(" == "); break;
						case NE: printf(" != "); break;
					}
				}
break;
case 115:
#line 433 "build.y"
{
					switch(yyvsp[-2].atr){
						case LT:
						case LE:
						case GT:
						case GE:
							if((yyvsp[-3].tipoexpr!=INTEIRO && yyvsp[-3].tipoexpr!=REAL && yyvsp[-3].tipoexpr!=CARACTERE)
								|| (yyvsp[0].tipoexpr!=INTEIRO && yyvsp[0].tipoexpr!=REAL && yyvsp[0].tipoexpr!=CARACTERE))
								Incompatibilidade("Operando improprio para operador relacional");
							break;
						case EQ:
						case NE:
							/*Se for logico, o outro operando também deve ser*/
							if(yyvsp[-3].tipoexpr == LOGICO && yyvsp[0].tipoexpr != LOGICO || yyvsp[-3].tipoexpr != LOGICO && yyvsp[0].tipoexpr == LOGICO)
								Incompatibilidade("Operador improprio para operador relacional");
							break;
						default:
							break;
					}
					yyval.tipoexpr=LOGICO;
				}
break;
case 117:
#line 457 "build.y"
{
					switch(yyvsp[0].atr){
						case PL: printf(" + "); break;
						case MI: printf(" - "); break;
					}
				}
break;
case 118:
#line 464 "build.y"
{
					if((yyvsp[-3].tipoexpr!=INTEIRO && yyvsp[-3].tipoexpr!=REAL && yyvsp[-3].tipoexpr!=CARACTERE)
						|| (yyvsp[0].tipoexpr!=INTEIRO && yyvsp[0].tipoexpr!=REAL && yyvsp[0].tipoexpr!=CARACTERE))
						Incompatibilidade("Operando improprio para operador aritmetico");
					if(yyvsp[-3].tipoexpr==REAL || yyvsp[0].tipoexpr==REAL)
						yyval.tipoexpr=REAL;
					else
						yyval.tipoexpr=INTEIRO;
				}
break;
case 120:
#line 476 "build.y"
{
					switch(yyvsp[0].atr){
						case MU: printf(" * "); break;
						case DI: printf(" / "); break;
						case RE: printf(" %% "); break;
					}
				}
break;
case 121:
#line 484 "build.y"
{
					switch(yyvsp[-2].atr){
						case MU:
						case DI:
							if((yyvsp[-3].tipoexpr!=INTEIRO && yyvsp[-3].tipoexpr!=REAL && yyvsp[-3].tipoexpr!=CARACTERE)
								|| (yyvsp[0].tipoexpr!=INTEIRO && yyvsp[0].tipoexpr!=REAL && yyvsp[0].tipoexpr!=CARACTERE))
								Incompatibilidade("Operando improprio para operador aritmetico");
							if(yyvsp[-3].tipoexpr==REAL || yyvsp[0].tipoexpr==REAL) yyval.tipoexpr=REAL;
							else yyval.tipoexpr=INTEIRO;
							break;
						case RE:
							if((yyvsp[-3].tipoexpr!=INTEIRO && yyvsp[-3].tipoexpr!=CARACTERE) || (yyvsp[0].tipoexpr!=INTEIRO && yyvsp[0].tipoexpr!=CARACTERE))
								Incompatibilidade("Operando improprio para operador resto");
							yyval.tipoexpr=INTEIRO;
							break;
						default:
							break;
					}
				}
break;
case 122:
#line 505 "build.y"
{
					if(yyvsp[0].simb != NULL) {
						yyvsp[0].simb->ref = VERDADE;
						yyval.tipoexpr = yyvsp[0].simb->tvar;
					}
				}
break;
case 123:
#line 511 "build.y"
{printf("%d", yyvsp[0].valint); yyval.tipoexpr = INTEIRO;}
break;
case 124:
#line 512 "build.y"
{printf("%g", yyvsp[0].valreal); yyval.tipoexpr = REAL;}
break;
case 125:
#line 513 "build.y"
{printf("\'%s\'", yyvsp[0].string); yyval.tipoexpr = CARACTERE;}
break;
case 126:
#line 514 "build.y"
{printf("true"); yyval.tipoexpr = LOGICO;}
break;
case 127:
#line 515 "build.y"
{printf("false"); yyval.tipoexpr = LOGICO;}
break;
case 128:
#line 516 "build.y"
{printf("~");}
break;
case 129:
#line 517 "build.y"
{
					if(yyvsp[0].tipoexpr != INTEIRO && yyvsp[0].tipoexpr!= REAL && yyvsp[0].tipoexpr!=CARACTERE)
						Incompatibilidade("Operando improprio para menos unario");
					if(yyvsp[0].tipoexpr == REAL)
						yyval.tipoexpr = REAL;
					else
						yyval.tipoexpr = INTEIRO;
				}
break;
case 130:
#line 525 "build.y"
{printf("(");}
break;
case 131:
#line 526 "build.y"
{
					printf(")");
					yyval.tipoexpr=yyvsp[-1].tipoexpr;
				}
break;
case 132:
#line 530 "build.y"
{yyval.tipoexpr = yyvsp[0].tipoexpr;}
break;
case 133:
#line 533 "build.y"
{
					printf("%s", yyvsp[0].string);
					simbolo escaux = escopo;
					simb = ProcuraSimb(yyvsp[0].string, escaux);
					while(escaux != NULL && simb == NULL) {
						escaux = escaux->escopo;
						if (escaux != NULL)
							simb = ProcuraSimb(yyvsp[0].string, escaux);
					}
					if(simb == NULL) 
						NaoDeclarado(yyvsp[0].string); 
					else if(simb->tid != IDVAR)
						TipoInadequado(yyvsp[0].string);
					yyval.simb = simb;
				}
break;
case 134:
#line 549 "build.y"
{
					yyval.simb = yyvsp[-1].simb;
					if(yyval.simb != NULL) {
						if(yyval.simb->array == FALSO && yyvsp[0].nsubscr>0)
							NaoEsperado("Subscrito\(s)");
						else if(yyval.simb->array==VERDADE && yyvsp[0].nsubscr==0)
							Esperado("subscrito\(s)");
						else if(yyvsp[0].nsubscr!=yyval.simb->ndims)
							Incompatibilidade("Numero de subscritos incompativel com o declarado");
					}
				}
break;
case 135:
#line 561 "build.y"
{yyval.nsubscr=0;}
break;
case 136:
#line 562 "build.y"
{yyval.nsubscr=yyvsp[-1].nsubscr+1;}
break;
case 137:
#line 564 "build.y"
{printf("[");}
break;
case 138:
#line 564 "build.y"
{printf("]");}
break;
case 139:
#line 565 "build.y"
{
					if(yyvsp[-2].tipoexpr!=INTEIRO && yyvsp[-2].tipoexpr!=CARACTERE)
						Incompatibilidade("Tipo inadequado para subscrito");
				}
break;
case 140:
#line 570 "build.y"
{printf("%s()", yyvsp[-1].string);}
break;
case 141:
#line 571 "build.y"
{
					simbolo s = ProcuraSimb(yyvsp[-3].string, escglobal);
					VerificarFuncao(yyvsp[-3].string, 0);
					if (s == NULL)
						yyval.tipoexpr = NAOVAR;
					else yyval.tipoexpr = s->tvar;
				}
break;
case 142:
#line 578 "build.y"
{printf("%s(", yyvsp[-1].string);}
break;
case 143:
#line 579 "build.y"
{
					printf(")");
					VerificarFuncao(yyvsp[-4].string, yyvsp[-1].nparams);
					simbolo s = ProcuraSimb(yyvsp[-4].string, escglobal);
					if (s == NULL)
						yyval.tipoexpr = NAOVAR;
					else yyval.tipoexpr = s->tvar;
				}
break;
#line 1604 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
