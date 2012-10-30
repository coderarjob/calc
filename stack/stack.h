/*
stack.h

Contains expernal function declarations and external variables and constants
*/

#define STACKMAX 500

/*
METHOD: Stack push function for char variable
RETURNS: 0 is no error, sub-zero number in case of a error
*/
int push(float c); 

/*
METHOD: tack pop function
RETURNS: 0 is no error, sub-zero number in case of a error
*/
int pop(float *output);	

/*
Returns the topmost element from stack.
However it does not pop. It just gives us a copy of the top most element.
ERRORS: 	*	-1	- Stack is empty
			*	-2	- Cannot allocate space for output	
*/

int topmost(float *output);

//int topmost_multiple(int max, char separator, char output[]);

/*
Returns -1 if pos is a invalid number, otherwise returns 1.
*/
int setposition(int pos);
