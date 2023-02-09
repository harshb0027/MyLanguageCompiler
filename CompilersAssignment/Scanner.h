/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
*************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa (from original work of Svillen Ranev)
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A2.
* Date: May 01 2021
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 8   /* variable identifier length */
#define ERR_LEN 20  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */
#define CHAR_LEN 1	/*length of char*/
#define WORD_SIZE 10 /*size of ezch keyword*/

#define RTE_CODE 1   /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */



enum TOKENS {
	ERR_T,		/* 0: Error token */
	MNID_T,		/* 4: Method name identifier token (start: _) */
	VID_T,		/*	 :variable identifier token*/
	INL_T,		/* 5: Integer literal token */
	FPL_T,		/* 6: Floating point literal token */
	STR_T,		/* 7: String literal token */
	CHAR_T,		/* 8: Char literal token*/
	SCC_OP_T,	/* 8: String concatenation operator token: (++) */
	ASS_OP_T,	/* 9: Assignment operator token */
	ART_OP_T,	/* 10: Arithmetic operator token */
	REL_OP_T,	/* 11: Relational operator token */
	LOG_OP_T,	/* 12: Logical operator token */
	LPR_T,		/* 13: Left parenthesis token */
	RPR_T,		/* 14: Right parenthesis token */
	LBR_T,		/* 15: Left brace token */
	RBR_T,		/* 16: Right brace token */
	KW_T,		/* 17: Keyword token */
	COM_T,		/* 18: Comma token */
	EOS_T,		/* 19: End of statement (semicolon) */
	RTE_T,		/* 20: Run-time error token */
	SEOF_T		/* 21: Source end-of-file token */
};



/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	chandigarh_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	chandigarh_int intValue;						/* integer literal attribute (value) */
	chandigarh_int keywordIndex;					/* keyword index in the keyword table */
	chandigarh_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	chandigarh_int charTableContent;
	chandigarh_chr contentChar[CHAR_LEN];
	chandigarh_flt floatValue;					/* floating-point literal attribute (value) */
	chandigarh_chr idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	chandigarh_chr errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	chandigarh_flg flags;			/* Flags information */
	union {
		chandigarh_int intValue;				/* Integer value */
		chandigarh_flt floatValue;			/* Float value */
		chandigarh_nul* stringContent;		/* String value */
		chandigarh_chr charValue;
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	chandigarh_int code;					    /* token code */
	TokenAttribute attribute;		/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, @comment@ , ',' , ';' , '-' , '+' , '*' , '/', ## , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Error states and illegal state */
#define ES  17		/* Error state with no retract */
#define ER  16		/* Error state with retract */
#define IS -1		/* Illegal state */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 9

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '-'
#define CHRCOL3 '.'
#define CHRCOL4 '\"'
#define CHRCOL5 '\''
#define CHRCOL6 '_'
/* #define CHRCOL7 '&' */
/* #define CHRCOL8 '\"' */
/* These constants will be used on VID function */
#define MNIDPREFIX '_'



/*
* S--Sign
Input State				Input Symbol						Output State
				L	N	S	P	SD	CD	U	EOF	O
0				7	1	3	ES	9	11	14	18	ES			NoAS
1				2	1	2	4	2	2	2	ER	2			NoAS
2				IS	IS	IS	IS	IS	IS	IS	IS	IS			Integer Literals
3				ES	1	ES	ES	ES	ES	ES	ER	ES			NoAS
4				ES	5	ES	ES	ES	ES	ES	ER	ES			NoAS
5				6	5	6	6	6	6	6	ER	6			NoAS
6				IS	IS	IS	IS	IS	IS	IS	IS	IS			Floating point literals
7				7	8	8	8	8	8	8	ER	8			NoAS
8				IS	IS	IS	IS	IS	IS	IS	IS	IS			VID
9				9	9	9	9	10	9	9	ES	9			NoAS
10				IS	IS	IS	IS	IS	IS	IS	IS	IS			String literals
11				12	12	12	12	12	ES	12	ES	12			NoAS
12				ES	ES	ES	ES	13	ES	ES	ES	ES			NoAS
13				IS	IS	IS	IS	IS	IS	IS	IS	IS			Char Literals
14				14	14	15	15	15	15	15	ER	15			Method Identifier
15				IS	IS	IS	IS	IS	IS	IS	IS	IS			Error states
16				IS	IS	IS	IS	IS	IS	IS	IS	IS			Error states




*/
/* TO_DO: Transition table - type of states defined in separate table */

/*The transition table made from the automata submitted during A21_Lexical Analysis*/
static chandigarh_int transitionTable[][TABLE_COLUMNS] = {
	/*			[A-z],	[0-9], 	(-)		(.)		(")		(')		(_)						
	/*			L(0),	N(1),	S(2)	P(3)	SD(4)	CD(5)	U(6)	EOF(7)	O(8)	
	/* S00 */	{7,		1,		3,		ES,		9,		11,		14,		18,		ES		},	/* NOAS */
	/* S01 */	{2,		1,		2,		4,		2,		2,		2,		ER,		2		},	/* NOAS */
	/* S02 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS		},	/* ASWR(IL) – Integer Literals*/
	/* S03 */	{ES,	1,		ES,		ES,		ES,		ES,		ES,		ER,		ES		},	/* NOAS */
	/* S04 */	{ES,	5,		ES,		ES,		ES,		ES,		ES,		ER,		ES		},	/* NOAS */
	/* S05 */	{6,		5,		6,		6,		6,		6,		6,		ER,		6		},	/* NOAS */
	/* S06 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS		},	/* ASWR(FPL) – Floating point literals */
	/* S07 */	{7,		8,		8,		8,		8,		8,		8,		ER,		8		},	/* NOAS */
	/* S08 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS		},	/* ASWR(VID) – Variable Identifier */
	/* S09 */	{9,		9,		9,		9,		10,		9,		9,		ES,		9		},	/* NOAS */
	/* S10 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS		},	/* ASNR(SL) – String literals  */
	/* S11 */	{12,	12,		12,		12,		12,		ES,		12,		ES,		12		},	/* NOAS */
	/* S12 */	{ES,	ES,		ES,		ES,		ES,		13,		ES,		ES,		ES		},	/* NOAS */
	/* S13 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS		},	/* ASNR(CL) – Char Literals*/
	/* S14 */	{14,	14,		15,		15,		15,		15,		15,		ER,		15		},	/* NoAS */
	/* S15 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS		},	/* ASWR(MID) – Method identifier   */
	/* S16 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS		},	/* ASWR(ERR) – Error States(Retracting) */
	/* S17 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS		}	/* ASNR(ERR) - Error States(Non-Retracting)*/
	};



/* Define accepting states types */
#define NOAS	0		/* not accepting state */
#define ASNR	1		/* accepting state with no retract */
#define ASWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states 
*/
static chandigarh_int stateType[] = {
	NOAS, /* 00 */
	NOAS, /* 01 */
	ASWR, /* 02 (IL -- Integer literals) */			
	NOAS, /* 03 */
	NOAS, /* 04 */
	NOAS, /* 05 */
	ASWR, /* 06 (FPL –- Floating point literals) */
	NOAS, /* 07 */
	ASWR, /* 08 (VID –- Variable Identifier) */
	NOAS, /* 09 */
	ASNR, /* 10 (SL -– String literals) */
	NOAS, /* 11 */
	NOAS, /* 12 */
	ASNR, /* 13 (CL -– Char Literals) */
	NOAS, /* 14 */
	ASWR, /* 15 (MID –- Method Identifier) */
	ASWR, /* 16 (ERR -- Error States(Retracting))*/
	ASNR  /* 17 (ERR -- Error States(Non-Retracting)) */

};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
chandigarh_int startScanner(BufferPointer psc_buf);
static chandigarh_int nextClass(chandigarh_chr c);			/* character class function */
static chandigarh_int nextState(chandigarh_int, chandigarh_chr);		/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(chandigarh_chr* lexeme);

/* Declare accepting states functions */
Token funcMID(chandigarh_chr lexeme[]);
Token funcVID (chandigarh_chr lexeme[]);
Token funcIL(chandigarh_chr lexeme[]);
Token funcFPL(chandigarh_chr lexeme[]);
Token funcSL(chandigarh_chr lexeme[]);
Token funcCL(chandigarh_chr lexeme[]);
Token funcKEY(chandigarh_chr lexeme[]);
Token funcErr(chandigarh_chr lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */
  
/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* 00 */
	NULL,		/* 01 */
	funcIL,		/* 02 */
	NULL,		/* 03 */
	NULL,		/* 04 */
	NULL,		/* 05 */
	funcFPL,	/* 06 */
	NULL,		/* 07 */
	funcVID,	/* 08 */
	NULL,		/* 09 */
	funcSL,		/* 10 */
	NULL,		/* 11 */
	NULL,		/* 12 */
	funcCL,		/* 13 */
	NULL,		/* 14 */
	funcMID,	/* 15 */
	funcErr,	/* 16 */
	funcErr		/* 17 */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 19

/* TO_DO: Define the list of keywords */
static chandigarh_chr* keywordTable[KWT_SIZE] = {
	"Int",
	"Float",
	"String",
	"Double",
	"Char",
	"If",
	"Main",
	"DATA",
	"CODE",
	"Then",
	"Else",
	"ElseIf",
	"equ",
	"While",
	"Do",
	"For",
	"Enter",
	"Display",
	"Return"
};

#endif
