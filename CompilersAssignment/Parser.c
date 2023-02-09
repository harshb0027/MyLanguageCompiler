/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa / Daniel Cormier
*************************************************************/

/*************************************************************
* File name: Parser.c
* Compiler: MS Visual Studio 2019
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: Sep 01 2021
* Professor: Paulo Sousa
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif


#ifndef PARSER_H_
#include "Parser.h"
#endif

/* TO_DO: For all functions adjust the datatypes used in your language */

/*************************************************************
 * Process Parser
 ************************************************************/
 /* TO_DO: This is the function to start the parser - check your program definition */
#define STR_LANGNAME "Chandigarh"
chandigarh_nul startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*************************************************************
 * Match Token
 ************************************************************/
 /* TO_DO: This is the main code for match - check your definitions */

chandigarh_nul matchToken(chandigarh_int tokenCode, chandigarh_int tokenAttribute) {
	chandigarh_int matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	
	default:		
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}

	}
	else
		syncErrorHandler(tokenCode);
}

/*************************************************************
 * Syncronize Error Handler
 ************************************************************/
 /* TO_DO: This is the function to handler error - adjust basically datatypes */

chandigarh_nul syncErrorHandler(chandigarh_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*************************************************************
 * Print Error
 ************************************************************/
 /* TO_DO: This is the function to error printing - adjust basically datatypes */

chandigarh_nul printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("%s\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("%s\n", getContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("%s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
	case RPR_T:
	case LBR_T:
	case RBR_T:
	case COM_T:
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*************************************************************
 * Program statement
 * BNF: <program> -> MAIN { <opt_statements> }
 * FIRST(<program>)= { MNID_T }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

chandigarh_nul program() {
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, "_main", 5) == 0) {
			matchToken(MNID_T, NO_ATTR);
			matchToken(LPR_T, NO_ATTR);
			matchToken(RPR_T, NO_ATTR);
			matchToken(LBR_T, NO_ATTR);
			dataSession();
			codeSession();
			matchToken(RBR_T, NO_ATTR);
			break;
		}
		else {
			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}


/*************************************************************
 * dataSession
 * BNF: <dataSession> -> DATA { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (DATA)}.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

chandigarh_nul dataSession() {
	//matchToken(KW_T, DATA);
	//matchToken(LBR_T, NO_ATTR);
	optVarListDeclarations();
	//matchToken(EOS_T, NO_ATTR);
	//matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
}

/*************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (FLOAT) }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

chandigarh_nul optVarListDeclarations() {
	
	//printf("lookahead.attribute.codeType = %d\n", lookahead.attribute.codeType);
	switch (lookahead.code) {
	case KW_T:
		varListDeclarations();
		break;
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/******************************************************************
 * varListDeclarations
 *
 *
 
 */
chandigarh_nul varListDeclarations() {
	varListDeclaration();
	varListDeclarationsPrime();

}

chandigarh_nul varListDeclaration() {
	switch (lookahead.code) {
	case EOS_T:
		printf("List of variables parsed *****\n");
		//matchToken(EOS_T, NO_ATTR);
	case KW_T:
		if (strcmp(lookahead.attribute.idLexeme, "Float") == 0) {
			//matchToken(KW_T, Float);
			lookahead.attribute.codeType = Float;
		}
		if (strcmp(lookahead.attribute.idLexeme, "Int") == 0) {
			lookahead.attribute.codeType = Int;
		}
		//matchToken(lookahead.code, NO_ATTR);
		switch (lookahead.attribute.codeType) {
		case Float:
			matchToken(KW_T, Float);
			//varListDeclarations();
			fltVarListDeclaration();
			break;
		case Int:
			matchToken(KW_T, Int);
			intVarListDeclaration();
			break;
		}

	//case EOS_T:
		//printf("List of variables parsed *****\n");
	}
	

	
	

}
chandigarh_nul varListDeclarationsPrime() {
	switch (lookahead.code) {
	case EOS_T:
		//matchToken(EOS_T, NO_ATTR);
		printf("List of variables parsed\n");

		matchToken(EOS_T, NO_ATTR);
		
		//break;
	case KW_T:
		if (!(strcmp(lookahead.attribute.idLexeme, "Int") == 0 ||
			strcmp(lookahead.attribute.idLexeme, "Float") == 0 ||
			strcmp(lookahead.attribute.idLexeme, "Char") == 0 ||
			strcmp(lookahead.attribute.idLexeme, "String") == 0)) {
			break;
		}
		if (strcmp(lookahead.attribute.idLexeme, "Float") == 0) {
			//matchToken(KW_T, Float);
			lookahead.attribute.codeType = Float;
		}
		if (strcmp(lookahead.attribute.idLexeme, "Int") == 0) {
			lookahead.attribute.codeType = Int;
		}
		switch (lookahead.attribute.codeType) {
		case Float:
			//matchToken(KW_T, Float);
			varListDeclaration();
			varListDeclarationsPrime();
		case Int:
			varListDeclaration();
			varListDeclarationsPrime();
		}
		break;
	
	default:
		;
	}
	
}

chandigarh_nul fltVarListDeclaration() {
	fltVarList();
}

chandigarh_nul intVarListDeclaration() {
	intVarList();
}

chandigarh_nul intVarList() {
	intVariableIdentifier();
	intVarListPrime();

}

chandigarh_nul fltVarList() {
	fltVariableIdentifier();
	fltVarListPrime();

}

chandigarh_nul intVariableIdentifier() {
	printf("lookahead.code = %d\n", lookahead.code);

	//lookahead.code = VID_T;
//	matchToken(VID_T, NO_ATTR);
	printf("Variable identifier %s identified\n", lookahead.attribute.idLexeme);
	matchToken(VID_T, NO_ATTR);
}


chandigarh_nul intVarListPrime() {
	switch (lookahead.code) {
	case COM_T:
		matchToken(COM_T, NO_ATTR);
		intVariableIdentifier();
		intVarListPrime();
		break;
		//case EOS_T:
			//printf("List of variables parsed\n");
			//matchToken(EOS_T, NO_ATTR);
			//break;
	default:
		;
	}

}

chandigarh_nul fltVariableIdentifier() {
	//printf("lookahead.code = %d\n", lookahead.code);
	
	//lookahead.code = VID_T;
//	matchToken(VID_T, NO_ATTR);
	printf("Variable identifier %s identified\n", lookahead.attribute.idLexeme);
	matchToken(VID_T, NO_ATTR);
}
chandigarh_nul fltVarListPrime() {
	switch (lookahead.code) {
	case COM_T:
		matchToken(COM_T, NO_ATTR);
		fltVariableIdentifier();
		fltVarListPrime();
		break;
	//case EOS_T:
		//printf("List of variables parsed\n");
		//matchToken(EOS_T, NO_ATTR);
		//break;
	default:
		;
	}

}
/***************************************************************************************/
/***************************************************************************************/
/*************************************************************
 * codeSession statement
 * BNF: <codeSession> -> CODE { <opt_statements> }
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

chandigarh_nul codeSession() {
	/*switch (lookahead.code) {
	case KW_T:
		if (strcmp(lookahead.attribute.idLexeme, "CODE") == 0) {
			lookahead.attribute.codeType = CODE;
			matchToken(KW_T, CODE);
		}
	}*/	
	/*matchToken(LBR_T, NO_ATTR);*/
	optionalStatements();
	/*matchToken(RBR_T, NO_ATTR);*/
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

/*************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

chandigarh_nul optionalStatements() {
	//printf("lookahead.attribute.idLexeme = %s\n", lookahead.attribute.idLexeme);
	switch (lookahead.code) {		
	case KW_T:
		if (strcmp(lookahead.attribute.idLexeme,"Display") == 0) {
			lookahead.attribute.codeType = Display;
			statements();
			break;
		}
		if (strcmp(lookahead.attribute.idLexeme, "Enter") == 0) {
			lookahead.attribute.codeType = Enter;
			statements();
			break;
		}
	case VID_T:
		statements();
		break;
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

chandigarh_nul statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*************************************************************
 * Statements Prime
 * BNF: <statementsPrime>  <statement><statementsPrime> | ϵ
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

chandigarh_nul statementsPrime() {
	switch (lookahead.code) {
	//case EOS_T:
		//matchToken(EOS_T, NO_ATTR);
	case KW_T:
		if (strcmp(lookahead.attribute.idLexeme, "Display") ==0) {
			lookahead.attribute.codeType = Display;
			statement();
			statementsPrime();
			break;
		}
		if (strcmp(lookahead.attribute.idLexeme, "Enter") == 0) {
			lookahead.attribute.codeType = Enter;
			statement();
			statementsPrime();
			break;
		}
		break;
	case VID_T:
		statement();
		statementsPrime();
		break;
	default:
		; //empty string
	}
}

/*************************************************************
 * Single statement
 * BNF: <statement> ->  <assignment statement> | <input statement> | <output statement>
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

chandigarh_nul statement() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case Display:
			outputStatement();
			break;
		case Enter:
			inputStatement();
			break;
		default:
			printError();
		}
		break;
	case VID_T:
		assignmentExpression();
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

chandigarh_nul assignmentExpression() {
	matchToken(VID_T, NO_ATTR);
	switch (lookahead.code) {
	case KW_T:
		if (strcmp(lookahead.attribute.idLexeme, "equ") == 0) {
			lookahead.attribute.codeType = equ;
			matchToken(KW_T, equ);
		}
		arithmeticExpression();
	}
	
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Assignment expression parsed");
}

chandigarh_nul arithmeticExpression() {
	additiveArithmeticExpression();
	printf("%s%s\n", STR_LANGNAME, ": Arithmetic Expression parsed");
}

chandigarh_nul additiveArithmeticExpression() {
	multiplicativeArithmeticExpression();
	additiveArithmeticExpressionPrime();
	printf("%s%s\n", STR_LANGNAME, ": Additive arithmetic expression parsed");
}

chandigarh_nul multiplicativeArithmeticExpression() {
	primaryArithmeticExpression();
	multiplicativeArithmeticExpressionPrime();
	printf("%s%s\n", STR_LANGNAME, ": Multiplicative arithmetic expression parsed");

}


chandigarh_nul primaryArithmeticExpression() {
	switch (lookahead.code) {
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		break;
	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		break;
	case RPR_T:
		matchToken(RPR_T, NO_ATTR);
		break;
	case LBR_T:
		matchToken(LBR_T, NO_ATTR);
		break;
	case RBR_T:
		matchToken(RBR_T, NO_ATTR);
		break;
	//case EOS_T:
		//matchToken(EOS_T, NO_ATTR);
		//break;	
	}
	printf("%s%s\n", STR_LANGNAME, ": Primary Arithmetic expression parsed");
}

chandigarh_nul multiplicativeArithmeticExpressionPrime() {
	switch (lookahead.code) {
	case EOS_T:
		//printf("Reached at the end of the statement:)\n");
		break;
	case VID_T:
		//matchToken(VID_T, NO_ATTR);
		primaryArithmeticExpression();
		multiplicativeArithmeticExpressionPrime();
	case LPR_T:
		primaryArithmeticExpression();
		multiplicativeArithmeticExpressionPrime();
	case RPR_T:
		primaryArithmeticExpression();
		multiplicativeArithmeticExpressionPrime();
	case FPL_T:
		primaryArithmeticExpression();
		multiplicativeArithmeticExpressionPrime();
	case INL_T:
		primaryArithmeticExpression();
		multiplicativeArithmeticExpressionPrime();
	case ART_OP_T:
		switch (lookahead.attribute.arithmeticOperator) {
		case OP_MUL:
			matchToken(ART_OP_T, OP_MUL);
			primaryArithmeticExpression();
			multiplicativeArithmeticExpressionPrime();
			break;
		case OP_DIV:
			matchToken(ART_OP_T, OP_DIV);
			primaryArithmeticExpression();
			multiplicativeArithmeticExpressionPrime();
			break;
		default:
			;
		}
	

		break;
		
	}
	printf("%s%s\n", STR_LANGNAME, ": Multiplicative arithmetic expression prime parsed");
}
chandigarh_nul additiveArithmeticExpressionPrime() {
	switch (lookahead.code) {
	case ART_OP_T:
		switch (lookahead.attribute.arithmeticOperator) {
		case OP_ADD:
			matchToken(ART_OP_T, OP_ADD);
			multiplicativeArithmeticExpression();
			additiveArithmeticExpressionPrime();
			break;
		case OP_SUB:
			matchToken(ART_OP_T, OP_SUB);
			multiplicativeArithmeticExpression();
			additiveArithmeticExpressionPrime();
			break;
		default:
			;
		}
	
		
	}
	printf("%s%s\n", STR_LANGNAME, ": Additive arithmetic expression prime parsed");
}

chandigarh_nul inputStatement() {
//	printf("Came to input statement:-\n");
	matchToken(KW_T, Enter);
	matchToken(LPR_T, NO_ATTR);
	matchToken(VID_T, NO_ATTR);
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}
/*************************************************************
 * Output Statement
 * BNF: <output statement> -> WRITE (<output statementPrime>);
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

chandigarh_nul outputStatement() {
	matchToken(KW_T, Display);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<???>) = { ??? }.
 ************************************************************/
 /* TO_DO: Adjust this function to respect your grammar */

chandigarh_nul outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/* TO_DO: Continue the development (all non-terminal functions) */
