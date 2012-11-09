/*
INFIX TO POSTFIX CONVERTER

LIMITATIONS:
  * Functions are not supported. Ex: Sine(), NOT() etc
  * Signed integer is not supported. All numbers are assumed positive.

FEATURES:		
  * Input from argument
  * Mathematical operator precidence is supported.
  * Brackets are supported.
  * Decimal points are supported.
  * Operator length qreater than one is supported, but not implemented, for the sake of simplicity. In future this feature will be implemented by functions not operators. But Functions are not supported now.
  * Unary operator is supported.
	* ^ (power) operator is supported.
*/

#include <stdio.h>
#define printerror(str) do { printf("%s\n", str); return 0; }while(0)

int convert(char[], char[]);
int match(char *pattern, char *place);
void strcopy(char *destination, char *source, int dlen);

int main(int argc, char *argv[])
{
  extern char *errorstr;
  int issilent = 0;
  
  if (argc == 1)
    printerror("Usage: itop (-s : optional) expression");
  
  if (match("-s", argv[1]) == 0) {
    issilent = 1;
    argc--;
    argv++;
  }
  
  char expr[100];
  expr[0] = '\0';
 
  while(--argc && *++argv)
   strcopy(expr, *argv, 100);
  
  char output[100]; 
  int stat = convert(expr,output);
  
  if (issilent) {
    printf("%s\n", output); //last \n is importaint
    return 0;
  }
    
  if (stat != 1)
    printf("\nFAILURE:\n%s\nOUTPUT: %s\n", errorstr, output);
  else
    printf("\nRESULT: %s\n:", output);
  
  return 0;
	
}

