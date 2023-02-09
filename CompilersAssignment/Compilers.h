/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2020
* Author: Paulo Sousa - Sep, 2021.
*************************************************************
* File name: compilers.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A1, A2, A3.
* Date: Sep 01 2020
* Professor: Paulo Sousa / Haider Miraj
* Purpose: This file defines the functions called by main function.
* Function list: mainBuffer(), mainScanner(), mainParser().
*************************************************************/
/***************************************************************************************
* This file is modified by-----
* Student Name:- Harsh Bansal
* Student Number:- 041005659
* Section:- CST8152
* This file is modified and according to the TO_DO comments assigned in the method
* Submission date:- October 02, 2021 (before 11:59pm)
*****************************************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/* Logical constants - adapt for your language */
#define CHANDIGARH_TRUE	1
#define CHANDIGARH_FALSE 0

/*
------------------------------------------------------------
Programs:
1: Buffer - invokes MainBuffer code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_BUFFER	= '1',
	PGM_SCANNER = '2',
	PGM_PARSER	= '3'
};

/*
------------------------------------------------------------
Main functions signatures
(Codes will be updated during next assignments)
------------------------------------------------------------
*/
int mainBuffer	(int argc, char** argv);
int mainScanner	(int argc, char** argv);
int mainParser	(int argc, char** argv);

/*
------------------------------------------------------------
Data types definitions
------------------------------------------------------------
*/

/* TO_DO: Define your typedefs done*/

typedef short			chandigarh_int;
typedef long			chandigarh_lng;
typedef char			chandigarh_chr;
typedef unsigned char	chandigarh_flg;
typedef char			chandigarh_bol;
typedef float			chandigarh_flt;
typedef double			chandigarh_dbl;
typedef void			chandigarh_nul;

#endif
