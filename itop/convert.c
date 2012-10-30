/*
 * Project: INFIX TO POSTFIX CONVERTER
 * 
 * Author: Arjob Mukherjee (arjob@aiicsl.com)
 * Version: 1a
 * 
 * This file contains the methods for the converter.
 */

#include "../stack/stack.h"
#include <stdio.h> /*for printf*/

#define ERRLEN 100
//#define DEBUG

extern int is_mathsymbol(char);
extern int is_digit(char);
extern int is_operator(char);
extern void strcopy(char *destination, char *source, int dlen);

static void add_error(char *error);
static int precedence(char c);
int convert(char expr[], char output[]);

char errorstr[ERRLEN]; //Holds error messages
float prevop = '\0';

/*
Returns 1, if prev has lower precedence than precedence of c
*/
static int precedence(char c)
{
  extern float prevop;
  
  /*
  \0 has the highest lowest, thus if prev == \0, the function will return 1 as expected, while keeping the validity check of operators.
  \n marks the end of array.
  */
  char parray[] = {'^','/', '*', '+' , '-', '\0', '\n'}; //Lower number has higher precedence
  
  int prev_index = -1;
  int c_index = -1;
  
  char o;
  int index = 0;
  while ((o = parray[index++]) != '\n')
  {
    if (o == (char) prevop)
      prev_index = index;
	    
    if (o == c)
      c_index = index;
    
    #ifdef DEBUG
      printf("\nIndex searching..%d - %d",  prev_index, c_index);
    #endif
	  
  }
  
  //Operator validity check
  if (prev_index == -1 || c_index == -1)
    return -1; //Error: Operator was not found
	  
  //for prev_index == c_index , it does not matter if you return 0 or 1. In either cases it works. Ex: 2 + 3 + 4 is (2 + 3) + 4 is same as 2 + (3 + 4).
  //But here we are returning 0, in that case
  if (prev_index > c_index)
    return 1;
  else
    return 0;
  
}

static void add_error(char *error) 
{
  errorstr[0] = '\0'; 
  strcopy(errorstr, error, ERRLEN);
}

int convert(char expr[], char output[])
{

  char c;
  int index = 0;
  int windex = 0;
  
  int brac_flag = 0; //FALSE
  float op_count = 0; //it is of type float, because this variable will be stored in a floating point type stack. Casting will not work as pointer is passed.
  
  extern float prevop;
  prevop = '\0';
  
  while ((c = expr[index]) != '\0')
  {
    #ifdef DEBUG
      printf("\nReading %c" , c);
    #endif
		
    if (is_digit(c))
    {	
      output[windex] = c;	
      #if defined(MODE)
		  printf("\nAdding %c to index: %d", c, windex);
      #endif

      windex++; //Write index increment;
    }
    else if (is_operator(c))
    {
      #ifdef DEBUG
		  printf("\nRead new operator, %c, searching precedence. prevop = %c", c, (char)prevop);
      #endif
      
      int pres = precedence(c); //(char)prevop is needed.
      
      output[windex] = ' ';
      windex++;
	      
      if (pres == -1)
      {
		  //precedence() function returns -1 when either of the operators supplied to it as arguments was not found in its array of known operators.
		  add_error("Error: Cannot find operator. Invalid operator.");
		  output[windex] = '\0';
		  return 0; //ERROR
      }
      else if (pres == 1)
      {			
		  #ifdef DEBUG
			 printf("\n%c operator has higher precedence", c);
		  #endif
	
		  push(c); //(float) c is not needed as this is a widening conversion
		  prevop = c;
		  
		  op_count++; //operator count increment
		  
		  #ifdef DEBUG
			 printf("\nIncrementing: %0f\n", op_count);
		  #endif
		      
      }
      else if (pres == 0)
      {
		  #ifdef DEBUG
			 printf("\n%c operator has lower precedence", c);
		  #endif
	
		  //pop untill precedence == 1
		  //c has higher precedence than op_pop. This maintains the stack rule.
		  int res;
		  int res1;

		  while(op_count > 0 && pop(&prevop) > -1 && (res = precedence(c)) == 0)
		  {
			 output[windex++] = (char) prevop; 
			 op_count--; //operator is decremented as many times stack is poped.
			 
			 #ifdef DEBUG
				printf("\nDecrementing: %0f", op_count);
				printf("\n..and poped: %c\n", (char) prevop);
			 #endif
		  }
				  
		  if (res < 0)
		  {
			 add_error("Error: Error: Cannot find operator. Invalid operator.");
			 output[windex] = '\0';
			 return 0;
		  }
		  
		  push(c);
		  op_count++;
		  
		  res =  topmost(&prevop);
		  if (res < 0)
			 prevop = '\0';
		      
      }
    }
    else if(c == '(')
    {
      int res1, res2;
      res1 = push(prevop); //saves the previous operator variable
      res2 = push(op_count); //saves the operator count variable
      
      if (res1 < 0 || res2 < 0)
      {
		  add_error("Error: Stack overflow.");
		  output[windex] = '\0';
		  return 0;
      }
      
      op_count = 0;
      prevop = '\0';
    }
    else if (c == ')')
    {
	    
      //pop out the rest of the operators (if any)
      while(op_count > 0)
      {
		  float ch;
		  pop(&ch);
		  output[windex++] = (char) ch; //Cast is needed
		  op_count--;
      }
	    
      //Restore the variables
      int res1, res2;
      res1 = pop(&op_count); //restores the operator count variable
      res2 = pop(&prevop); //restores the previous operator variable
      
      if (res1 < 0 || res2 < 0)
      {
		  add_error("Error: Stack underflow. Invalid expression.");
		  output[windex] = '\0';
		  return 0;
      }
	    
    }
    
    //print output so far
    output[windex] = '\0';
    
    #if defined(DEBUB)
      printf("\nSo far: %s", output);
    #endif
    //cont..
    
    index++;	
  }
	
  //Empty the stack
  float ch;
  while(pop(&ch) > 0)
  {	
    output[windex++] = (char) ch; //Cast is needed
    op_count--; //decrement operand count
  }
	
  if (op_count > 0)
  {
    add_error("Error: Invalid expression.");
    printf("\nop_count: %d\n", (int) op_count);
    output[windex] = '\0';
    return 0;
  }
  
  output[windex] = '\0';
  
  return 1;
}
