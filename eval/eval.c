#include "../stack/stack.h"
#include <stdio.h>

#define ERRLEN 100
#define EXPRLEN 100
#define NDEBUG

//Note: extern keyword is not needed. If absent, extern is implied. All function declarations have hidden extern keyword.
extern int getch(char*);
extern int ungetch(char);
extern int is_digit(char);
extern int is_operator(char);
extern void strcopy(char *destination, char *source, int dlen);
float eval();
static void add_error(char *error);
static int powre(int number, int exponential);
float getinteger(char c, char *lastchar); //my version of atoi

int match(char *pattern, char *place);
int get_line(char line[], int max, int omitSpaces);

char errorstr[ERRLEN]; //Holds error messages
char expr[EXPRLEN];
int iserror = 0;
int e_index;

static void add_error(char *error) 
{
  extern char expr[];
  extern int iserror;
  
  errorstr[0] = '\0'; 
  strcopy(errorstr, error, ERRLEN);
  iserror = 1;
  
}

float getinteger(char c, char *lastchar)
{
  float out = 0;
  int decimal = 0; //Boolean
  float fraction = 1.0;

  do
  {
    if (c != '.') 
      out = out * 10.0 + (c - '0');
	    
    getch(&c);
    
    if (decimal)
      fraction *= 10.0;
	    
    if (c == '.')
      decimal = 1; //True
      
    #ifdef DEBUG
      printf("\nReading: %c (out = %f)", c, out );
    #endif
  }while (c != ' ' && !is_operator(c) && c != '\0');

  if (decimal)
    fraction = fraction / 10;
	  
  out = out/fraction;
  
  #ifdef DEBUG
    printf("\nNumber: %3f, char: %d", out, c);
  #endif
    
  *lastchar = c; //c is the last char.
  return out;
}   

static int powre(int number, int exponential)
{

	int result=1;
	while(exponential)
	{
		result *=number;
		exponential--;
	}

	return result;
}	

float eval()
{	
  char c;
  int ret;
	
  while ((ret = getch(&c)) > 0 && c !='\0')
  {	
  	#ifdef DEBUG
      printf("\nInput: %d", c);
    #endif
      
    if (is_digit(c) || c == '.')
    {
      //Get number from expression.
      
      #ifdef DEBUG
				printf("\nProcessing digit: %c", c);
      #endif
      
      float out = getinteger(c, &c);
      push(out);
      ungetch(c);
	    
    }
    else if (is_operator(c))
    {
      float num1 = 0.0;
      float num2 = 0.0;
      
      pop(&num1);
      pop(&num2);
	    
      switch (c)
      {
		  case '+' :
			 push(num1 + num2);
			 break;
		  case '-':
			 push(num2 - num1);
			 break;
		  case '*' :
			 push(num1 * num2);
			 break;
		  case '/':
			 if (num1 == 0)
			 {
				add_error("EVAL: Error: Division by zero.");
				return -1; //ERROR
			 }
			 
			 push(num2/num1);
			 break;
		  case '^':
			 push(powre(num2,num1));
			 break;
		  default:
			 add_error("EVAL: Error: Undefined operator.");
			 return -1; //ERROR
      }
    }
    else if (c == ' ')
    {
      #ifdef DEBUG
		  printf("\nInput: Space.");
      #endif
    }
    else if (c == '\n')
    {
      //enter key
    }
    else
    {	
      #ifdef DEBUG
				printf("Invalid operator: %d\n", c);
      #endif
      add_error("EVAL: Error: Cannot find operator. Invalid operator.");
      return -1; //ERROR
    }	
  }
	
  if(ret < 0)
  {
    add_error("EVAL: Error: Severe stack operation.");
    return -1; //ERROR
  }
  
  float outnumber;
  
  if (pop(&outnumber) < 0)
  {
     add_error("EVAL: Error: Invalid expression.");
    return -1; //ERROR
  }
  
  #ifdef DEBUG
    printf("\nSTACK END: %f", outnumber);
  #endif
    
  return outnumber;
}


int main(int argc, char *argv[])
{
  extern char expr[];
  extern char errorstr[];
  extern int iserror;
  
  int issillent = 0;
  
  if(argc > 1) {
    if (match("-s", argv[1]) == 0)
      issillent = 1;
    else {
      printf("EVA: Invalid option. %s\n", argv[1]);
      printf("usage: %s -s (optional, sillent mode), postfix expression from stdin\n", argv[0]);
      return 0;
    }
  }
  
  if (!issillent)
    printf("Enter postfix expression: ");
  
  int len = get_line(expr, EXPRLEN,0);
  
  if (len == 1){
    printf("help: %s expects an expression in post fix notation from standard input.\n", argv[0]);
    return 0;
  }
  
	float result = eval();
  
  if (iserror)
    printf("\nFAILURE:%s\n", errorstr);
  else
    printf("%f\n", result);
  
  return 0;
}
