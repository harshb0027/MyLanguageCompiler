/*//************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa / Daniel Cormier
*************************************************************/

/************************************************************
* File name: buffer.c
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: Sep 01 2021
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer (A12)
*************************************************************/


/***************************************************************************************
* This file is modified by the group of two students-----
* Student Name:- Harsh Bansal
* Student Number:- 041005659
* Section:- CST8152
* ***************************************************************************************
* Student Name:- Arshdeep Kaur
* Student Number:- 040991688
* Section:- CST8152
* ***************************************************************************************
* This file is modified and according to the TO_DO comments assigned in the method
* Submission date:- October 02, 2021 (before 11:59pm)
* **********************************************************************************************
* The script for the buffer created in C language is given. The language proposed for creating
* the buffer is -- CHANDIGARH and the extension for these types of files is .chg
* 
* There are four types of formats of the files/ programs included for testing
*		--Thanks to the authors and professors (Prof. Paulo Sousa & Prof. Daniel Cormier) for giving some ideas in creating the script files
* Reference of the scripts is taken from the Prof.Svillen Ranev's sofia files programs provided 
* by the professor. 
* Syntax of the .chg is proposed from the A11 Language Specifications(Chandigarh) -- (document file submitted).
* 
* Batch file:- The .bat file (BatchFIle.bat) includes all the commands written for the execution of the files and testing(running
* the different test cases) -- making the error and the output files. 
* the reading of the files in different operational modes and 
***************************************************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Buffer.h"
#endif

/************************************************************
* Function name: create
* Purpose: Creates the buffer according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: Ver 2.1
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to Buffer)
* Algorithm: Allocation of memory according to inicial (default) values.
* TO_DO:
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
**************************************************************/

BufferPointer create(chandigarh_int size, chandigarh_int increment, chandigarh_int mode) {
	BufferPointer b;
	/* TO_DO: Defensive programming */
	if (size<0 || size>CHANDIGARH_MAX_SIZE) {
		return NULL;
	}
	if (!size) {
		size = BUFFER_DEFAULT_SIZE;
		increment = BUFFER_DEFAULT_INCREMENT;
	}

	//CHECK THE VALUE OF INCREMENT SO THAT IS IS != 0
	if (!increment)
		mode = MODE_FIXED;
	b = (BufferPointer)calloc(1, sizeof(Buffer));
	/* TO_DO: Defensive programming */
	if (increment < 0) {
		return NULL;
	}
	if (!b) {
		return NULL;
	}
	if (b == NULL)
		return NULL;
	b->content = (chandigarh_chr*)malloc(size);
	/* TO_DO: Defensive programming */
	if (!b->content) {
		return NULL;
	}
	b->mode = mode;
	b->size = size;
	b->increment = increment;

	/* TO_DO: Initialize flags */
	b->flags = CHANDIGARH_DEFAULT_FLAG;

	/* TO_DO: The created flag must be signalized as EMP */
	b->flags = b->flags | CHANDIGARH_SET_FLAG_EMPTY;

	return b;
}


/************************************************************
* Function name: addChar
* Purpose: Adds a char to buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   ch = char to be added
* Return value:
*	bPointer (pointer to Buffer)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/

BufferPointer addChar(BufferPointer const pBuffer, chandigarh_chr ch) {
	chandigarh_chr* tempbuf;
	chandigarh_int newSize;
	/* TO_DO: Defensive programming done */
	if (!pBuffer) {
		return NULL;
	}
	/* TO_DO: Reset Relocation done */
	pBuffer->flags = pBuffer->flags & CHANDIGARH_RESET_FLAG_REL;
	/* TO_DO: Check FUL done */
	/* if the full bit is not equal to 1 or the decimal value is not 2, use the and operation */
	if ((pBuffer->flags & CHANDIGARH_CHECK_FLAG_FULL) != 2) {
		pBuffer->flags = pBuffer->flags & CHANDIGARH_CHECK_FLAG_FULL;
	}		
	if (pBuffer->size == pBuffer->position.writePos * (chandigarh_int)sizeof(chandigarh_chr)) {
		switch (pBuffer->mode) {
		case MODE_FIXED:
			/* TO_DO: Set FUL done */
			pBuffer->flags = pBuffer->flags | CHANDIGARH_SET_FLAG_FULL;
			return NULL;
		case MODE_ADDIT:
			newSize = pBuffer->size + pBuffer->increment;
			/* TO_DO: Defensive programming done*/
			if (newSize < 0 || newSize <= pBuffer->size) {
				return NULL;
			}
			break;
		case MODE_MULTI:
			newSize = pBuffer->size * pBuffer->increment;
			/* TO_DO: Defensive programming done*/
			if (newSize < 0 || newSize <= pBuffer->size) {
				return NULL;
			}
			break;
		default:
			return NULL;
		}
		/*making a temporary buffer and allocating all the ocntent to this buffer*/
		tempbuf = (chandigarh_chr*)realloc(pBuffer->content, newSize);
		/* TO_DO: Defensive programming */
		if (!tempbuf) {
			return NULL;
		}
		if (tempbuf && tempbuf != pBuffer->content) {
			/* TO_DO: Set Relocation done */
			pBuffer->flags = pBuffer->flags | CHANDIGARH_SET_FLAG_REL;
			pBuffer->content = tempbuf;
		}
		pBuffer->size = newSize;
	}
	/* TO_DO: Adjust flags: Reset EMP done*/
	pBuffer->flags = pBuffer->flags & CHANDIGARH_RESET_FLAG_EMPTY;
	/* TO_DO: Adjust flags: Set FUL if necessary done */
	if (pBuffer->size == pBuffer->position.writePos * (chandigarh_int)sizeof(chandigarh_chr))
		pBuffer->flags = pBuffer->flags | CHANDIGARH_SET_FLAG_FULL;
	pBuffer->content[pBuffer->position.writePos++] = ch;
	return pBuffer;
}

/************************************************************
* Function name: clear
* Purpose: Clears the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_bol clear(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	if (pBuffer == NULL) {
		return CHANDIGARH_FALSE;
	}
	/*reinitializing the offsets and pointers*/
	pBuffer->position.writePos = pBuffer->position.markPos = pBuffer->position.readPos = 0;
	/* TO_DO: Adjust flags original done */
	pBuffer->flags = pBuffer->flags | CHANDIGARH_DEFAULT_FLAG;
	return CHANDIGARH_TRUE;
}

/************************************************************
* Function name: destroy
* Purpose: Releases the buffer address
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_bol destroy(BufferPointer const pBuffer) {
	free(pBuffer->content);
	free(pBuffer);
	return CHANDIGARH_TRUE;
}

/************************************************************
* Function name: isFull
* Purpose: Checks if buffer is full
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_bol isFull(BufferPointer const pBuffer) {

	/* TO_DO: Use bitwise check to test if buffer is FUL done*/
	if ((pBuffer->flags & CHANDIGARH_CHECK_FLAG_FULL) == 2) {
		return CHANDIGARH_TRUE;
	}
	/* TO_DO: Defensive programming */
	if (pBuffer == NULL) {
		return CHANDIGARH_FALSE;
	}
	if (pBuffer->size == pBuffer->position.writePos * (chandigarh_int)sizeof(chandigarh_chr))
		return CHANDIGARH_TRUE;
	return CHANDIGARH_FALSE;
}

/************************************************************
* Function name: getWritePos
* Purpose: Returns the position of char to be added
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	addcPosition value
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions*************
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_int getWritePos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	if (!pBuffer)
		return CHANDIGARH_FALSE;

	if (pBuffer->size < pBuffer->position.writePos * (chandigarh_int)sizeof(chandigarh_chr)) {
		return CHANDIGARH_FALSE;
	}
	return pBuffer->position.writePos;
}

/************************************************************
* Function name: getSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_int getSize(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	
	if (!pBuffer)
		return CHANDIGARH_FALSE;
	return pBuffer->size;
}

/************************************************************
* Function name: getMode
* Purpose: Returns the operational mode
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_int getMode(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	if (pBuffer == NULL) {
		return CHANDIGARH_FALSE;
	}
	return pBuffer->mode;
}


/************************************************************
* Function name: getMarkPos
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	mark offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_int getMarkPos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	if (pBuffer == NULL) {
		return CHANDIGARH_FALSE;
	}
	/*if the buffer's mark comes indicates the value which is greater than the distance from the
	beginning to the end of the mark, the function should return null value in that case.*/
	if (pBuffer->position.markPos > pBuffer->size)
		return CHANDIGARH_FALSE;
	return pBuffer->position.markPos;
}


/************************************************************
* Function name: setMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_bol setMark(BufferPointer const pBuffer, chandigarh_int mark) {
	/* TO_DO: Defensive programming */
	if (!pBuffer) {
		return CHANDIGARH_FALSE;
	}
	/*if mark position is greater than the size itself*/
	if (pBuffer->size < mark)
		return CHANDIGARH_FALSE;
	pBuffer->position.markPos = mark;
	return CHANDIGARH_TRUE;
}

/************************************************************
* Function name: print
* Purpose: Prints the string in the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_int print(BufferPointer const pBuffer) {
	chandigarh_int cont = 0;
	chandigarh_chr c;
	/* TO_DO: Defensive programming */
	/*if there is nothing in the buffer*/	
	if (pBuffer == NULL) {
		return CHANDIGARH_FALSE;
	}
	c = getChar(pBuffer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	/*
	while ((pBuffer->flags & CHANDIGARH_CHECK_FLAG_EOB) != CHANDIGARH_CHECK_FLAG_EOB) {
		cont++;
		printf("%c", c);
		c = getChar(pBuffer);
	}*/
	if ((pBuffer->flags & CHANDIGARH_CHECK_FLAG_EOB) != CHANDIGARH_CHECK_FLAG_EOB) {
		while (!(pBuffer->position.readPos == pBuffer->position.writePos)) {
			cont++;
			printf("%c", c);
			c = getChar(pBuffer);
		}
	 
	} 
	
	return cont;
}

/************************************************************
* Function name: load
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   fi = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_int load(BufferPointer const pBuffer, FILE* const fi) {
	chandigarh_int size = 0;
	chandigarh_chr c;
	/* TO_DO: Defensive programming */
	c = (chandigarh_chr)fgetc(fi);
	while (!feof(fi)) {
		if (!addChar(pBuffer, c)) {
			ungetc(c, fi);
			return BUFFER_ERROR;
		}
		c = (char)fgetc(fi);
		size++;
	}
	if (ferror(fi))
		return BUFFER_ERROR;
	return size;
}

/************************************************************
* Function name: isEmpty
* Purpose: Checks if buffer is empty.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_bol isEmpty(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Use bitwise operation to test if buffer is EMP */
	
	if (pBuffer == NULL) {
		return CHANDIGARH_TRUE;
	}
	if ((pBuffer->flags & CHANDIGARH_CHECK_FLAG_EMPTY) == 1) {
		return CHANDIGARH_TRUE;
	}

	if (pBuffer->position.writePos == 0)
		return CHANDIGARH_TRUE;
	return CHANDIGARH_FALSE;
}

/************************************************************
* Function name: getChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_chr getChar(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	if (pBuffer == NULL) {
		return CHANDIGARH_FALSE;
	}
	if (pBuffer->position.readPos == pBuffer->position.writePos) {
		/* TO_DO: Set EOB flag */
		pBuffer->flags = pBuffer->flags | CHANDIGARH_SET_FLAG_EOB;
		return BUFFER_EOF;
	}
	/* TO_DO: Reset EOB flag */
	pBuffer->flags = pBuffer->flags & CHANDIGARH_RESET_FLAG_EOB;
	return pBuffer->content[pBuffer->position.readPos++];
}


/************************************************************
* Function name: recover
* Purpose: Rewinds the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_bol recover(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	pBuffer->position.readPos = 0;
	pBuffer->position.markPos = 0;
	return CHANDIGARH_TRUE;
}


/************************************************************
* Function name: retract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_bol retract(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	/* defensive programming in the sense that the pointer of read posiiton should not
	go below or equal to 0*/
	if (pBuffer->position.readPos <= 0) {
		return CHANDIGARH_FALSE;
	}
	pBuffer->position.readPos--;
	return CHANDIGARH_TRUE;
}


/************************************************************
* Function name: restore
* Purpose: Resets the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_bol restore(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	if (pBuffer->position.markPos > pBuffer->size) {
		return CHANDIGARH_FALSE;
	}
	pBuffer->position.readPos = pBuffer->position.markPos;
	return CHANDIGARH_TRUE;
}


/************************************************************
* Function name: getReadPos
* Purpose: Returns the value of getCPosition.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	The readPos offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_int getReadPos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->position.readPos;
}


/************************************************************
* Function name: getIncrement
* Purpose: Returns the buffer increment.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_int getIncrement(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->increment;
}


/************************************************************
* Function name: getContent
* Purpose: Returns the pointer to String.
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_chr* getContent(BufferPointer const pBuffer, chandigarh_int pos) {
	/* TO_DO: Defensive programming */
	if (!pBuffer) {
		return NULL;
	}
	return pBuffer->content + pos;
}


/************************************************************
* Function name: getFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
chandigarh_flg getFlags(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->flags;
}
