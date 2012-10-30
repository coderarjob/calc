/*
PROJECT: Expression evaluator
AUTHOR: Arjob Mukherjee <arjob@aiicsl.com>
MULTIFILE C PROJECT
NOTE: This file contains the source of stack implementation.
NOTE: The stack.h contains the expernal function declarations and enternal fields.
NOTE: The source contains some static fields which are private to this file.
*/

#include "stack.h"
#define STACKMAX 500

static float stak[STACKMAX]; //becasue chars as well as ints can be saved in it.
static int position = 0;

/*
RETURNS: 0 is no error, sub-zero number in case of a error
*/
int push(float c)
{
	extern int position;
	extern float stak[];
	
	if (position == STACKMAX)
		return -1;
		
	stak[position++] = c;
	return 0;	
}

/*
RETURNS: 0 is no error, sub-zero number in case of a error
*/
int pop(float *output)
{
	extern int position;
	extern float stak[];
	
	if (position == 0)
		return -1;
	
	*output = stak[--position];
	return 1;
}

/*
Returns -1 if pos is a invalid number, otherwise returns 1.
*/
int setposition(int pos)
{
	extern int position;
	
	if (pos > -1 && pos < STACKMAX)
		position = pos;
	else
		return -1;
		
	return 1;
}

/*
Returns the topmost element from stack.
However it does not pop. It just gives us a copy of the top most element.
ERRORS: 	*	-1	- Stack is empty
			*	-2	- Cannot allocate space for output	
*/

int topmost(float *output)
{
	extern int position; //local extern variable declaration
	extern float stak[]; //local extern variable declaration
	
	int pos = position;
	
	if (pos == 0)
		return -1;
	
	*output = stak[--pos];
	return 1;
	
}

/*int topmost_multiple(int max, char separator, char output[])
{	 	
	extern int position; //local extern variable declaration
	extern char stak[]; //local extern variable declaration
	
 	if (position = 0)
 		return -1; //Error: Stack is empty

	//output = malloc(sizeof(char) * max+1);
	
	if (output == 0)
		return -2;	//Error: Cannot allocate memory
	
	char c;
	int index = 0;
	int pos = position;
	
	while ((c = stak[--pos]) != separator && pos != 0 && index < max)
		output[index++] = c;
	
	output[index] = '\0';
	
	return 1;
}*/

