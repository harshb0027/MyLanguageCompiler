/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
*************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa (based on prof. Svillen Ranev work)
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A3.
* Date: Dec 11 2021
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef BUFFER_H_
#include "Buffer.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */

/* TO_DO: Adjust all datatypes to your language */
static Token lookahead;
chandigarh_int syntaxErrorNumber = 0;
extern Buffer* stringLiteralTable;
extern chandigarh_int line;
extern Token tokenizer();
extern chandigarh_chr* keywordTable[];
extern Token funcVID(chandigarh_chr lexeme[]);

/* TO_DO: Adjust your language name here */
#define STR_LANGNAME "Chandigarh"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	Int,
	Float,
	String,
	Double,
	Char,
	If,
	Main,
	DATA,
	CODE,
	Then,
	Else,
	ElseIf,
	equ,
	While,
	Do,
	For,
	Enter,
	Display,
	Return

};

/* Function definitions */
chandigarh_nul startParser();
chandigarh_nul matchToken(chandigarh_int, chandigarh_int);
chandigarh_nul syncErrorHandler(chandigarh_int);
chandigarh_nul printError();

/* TO_DO: Place ALL non-terminal function declarations */
chandigarh_nul additiveArithmeticExpression();
chandigarh_nul additiveArithmeticExpressionPrime();
chandigarh_nul arithmeticExpression();
chandigarh_nul assignmentExpression();
chandigarh_nul assignmentStatement();
chandigarh_nul codeSession();
chandigarh_nul dataSession();
chandigarh_nul fltVariableIdentifier();
chandigarh_nul fltVarList();
chandigarh_nul fltVarListPrime();
chandigarh_nul intVariableIdentifier();
chandigarh_nul intVarList();
chandigarh_nul intVarListPrime();
chandigarh_nul intVarListDeclaration();
chandigarh_nul inputStatement();
chandigarh_nul multiplicativeArithmeticExpression();
chandigarh_nul multiplicativeArithmeticExpressionPrime();
chandigarh_nul fltVarListDeclaration();
chandigarh_nul optVarListDeclarations();
chandigarh_nul optionalStatements();
chandigarh_nul outputStatement();
chandigarh_nul outputVariableList();
chandigarh_nul primaryArithmeticExpression();
chandigarh_nul program();
chandigarh_nul statement();
chandigarh_nul statements();
chandigarh_nul statementsPrime();
chandigarh_nul variableIdentifier();
chandigarh_nul variableList();
chandigarh_nul variableListPrime();
chandigarh_nul varListDeclarations();
chandigarh_nul varListDeclaration();
chandigarh_nul varListDeclarationsPrime();

#endif
