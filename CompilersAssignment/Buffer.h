/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
*************************************************************
* File name: Buffer.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa (based on prof. Svillen Ranev work)
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: Sep 01 2021
* Purpose: This file is the main header for Parser (.h)
*************************************************************/



#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#define BUFFER_H_

/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer) */
enum BUFFERMODES {
	MODE_FIXED = 'f',
	MODE_ADDIT = 'a',
	MODE_MULTI = 'm'
};

/* TO_DO: Adjust all constants to your Language */

#define BUFFER_ERROR (-1)						/* General error message */
#define BUFFER_EOF '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA).................................. */

#define BUFFER_DEFAULT_SIZE			200			/* default initial buffer capacity */
#define BUFFER_DEFAULT_INCREMENT	100			/* default increment factor */

/* You should add your own constant definitions here */
#define CHANDIGARH_MAX_SIZE				SHRT_MAX-1	/*maximum capacity*/ 

/* Add your bit-masks constant definitions here - Defined for SOFIA */
/* BITS                                7654.3210 */
#define CHANDIGARH_DEFAULT_FLAG 0xF0 	/* 1111.0000 = 240 */

/* TO_DO: BIT 0: EMP: Empty */
/*defining the bit if the buffer is empty*/
#define CHANDIGARH_SET_FLAG_EMPTY 0x01
#define CHANDIGARH_RESET_FLAG_EMPTY 0xFE
#define CHANDIGARH_CHECK_FLAG_EMPTY 0x01
/* TO_DO: BIT 1: FUL = Full */
/*defining the bit if the buffer is full*/
#define CHANDIGARH_SET_FLAG_FULL 0x02	/*0000.0010*/
#define CHANDIGARH_RESET_FLAG_FULL 0xFD	/*1111.1101*/
#define CHANDIGARH_CHECK_FLAG_FULL 0x02	/*0000.0010*/
/* TO_DO: BIT 2: EOB = EndOfBuffer */
/*defining the bit if there is the end of the buffer/achieved at the end by reading the end of the buffer*/
#define CHANDIGARH_SET_FLAG_EOB	0x04	/*0000.0100*/
#define CHANDIGARH_RESET_FLAG_EOB 0xFB	/*1111.1011*/
#define CHANDIGARH_CHECK_FLAG_EOB 0x04	/*0000.0100 -- decimal value = 4*/
/* TO_DO: BIT 3: REL = Relocation */
/*relocating the buffer point where the pointer reaches at the point where it needs to be changed i.e.
after the working of the fixed, additive or multiplicative mode when the pointer needs to be relocated*/
#define CHANDIGARH_SET_FLAG_REL 0x08	/*0000.1000*/;
#define CHANDIGARH_RESET_FLAG_REL 0xF7	/*1111.0111*/
#define CHANDIGARH_CHECK_FLAG_REL 0x08	/*0000.1000*/

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TO_DO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	chandigarh_int writePos;			/* the offset (in chars) to the add-character location */
	chandigarh_int readPos;				/* the offset (in chars) to the get-character location */
	chandigarh_int markPos;				/* the offset (in chars) to the mark location */
} Position;

/* Buffer structure */
typedef struct buffer {
	chandigarh_chr*	content;		/* pointer to the beginning of character array (character buffer) */
	chandigarh_int	size;		    /* current dynamic memory size (in bytes) allocated to character buffer */
	chandigarh_int	increment;		/* character array increment factor */
	chandigarh_int	mode;			/* operational mode indicator */
	chandigarh_flg	flags;			/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;		/* Offset / position field */
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer create(chandigarh_int, chandigarh_int, chandigarh_int);
BufferPointer addChar(BufferPointer const, chandigarh_chr);
chandigarh_bol retract(BufferPointer const);
chandigarh_bol restore(BufferPointer const);
chandigarh_bol recover(BufferPointer const);
chandigarh_bol clear(BufferPointer const);
chandigarh_bol destroy(BufferPointer const);
chandigarh_bol setMark(BufferPointer const, chandigarh_int);
chandigarh_bol isEmpty(BufferPointer const);
chandigarh_bol isFull(BufferPointer const);
chandigarh_bol isRealocated(BufferPointer const);
chandigarh_int print(BufferPointer const);
chandigarh_int load(BufferPointer const, FILE* const);
/* Getters */
chandigarh_int getSize(BufferPointer const);
chandigarh_int getWritePos(BufferPointer const);
chandigarh_int getMarkPos(BufferPointer const);
chandigarh_int getReadPos(BufferPointer const);
chandigarh_int getIncrement(BufferPointer const);
chandigarh_int getMode(BufferPointer const);
chandigarh_chr getChar(BufferPointer const);
chandigarh_chr* getContent(BufferPointer const, chandigarh_int);
chandigarh_flg getFlags(BufferPointer const);

#endif
