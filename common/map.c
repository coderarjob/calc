/*
 * Project: INFIX TO POSTFIX CONVERTER
 * 
 * Author: Arjob Mukherjee (arjob@aiicsl.com)
 * Version: 1a
 * 
 * This file contains the helper methods for the converter.
 */

int is_mathsymbol(char c)
{
  if (c == '.' || c == '-' || c == '+')
    return 1; //TRUE
  else
    return 0; //FALSE
}

int is_digit(char c)
{
  if (c >= '0' && c <= '9')
    return 1; //TRUE
  else
    return 0; //FALSE
}

int is_operator(char c)
{
  if (c == '-' || c == '+' || c == '/' || c == '*' || c == '^')
    return 1; //TRUE
  else 
    return 0; //FALSE
} 
