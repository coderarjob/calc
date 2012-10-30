/*
 * Project: INFIX TO POSTFIX CONVERTER
 * 
 * Author: Arjob Mukherjee (arjob@aiicsl.com)
 * Version: 1a
 * 
 * This file contains the string manipulation methods used in the project.
 */


/*
RETURNS:
  * -1 -> Error, cannot allocate output storage
  * n -> n charecters read. Because \n will me appened (as user hits enter after submission), a empty user input returns 1 not 0
*/
#define EOF -1

int get_line(char line[], int max, int omitSpaces)
{
  char c;
  int count = 0;
  while ((c = getchar()) != '\n' && (c != EOF) && count < max-2)
    if (!omitSpaces || c != ' ')
      line[count++] = c;
  
  if (c == '\n')
    line[count++] = '\n';
	  
  line[count] = '\0';
  
  return count;
}

/*
 * My implementation of strcmp function.
 * Returns 0 if pattern and place matches.
 */
int match(char *pattern, char *place)
{
  while (*pattern == *place && *pattern && *place){
   pattern++ ;
   place++;
  }
  
  if (!*pattern && !*place)
    return 0;
  else
    return *place - *pattern;
}


void strcopy(char *destination, char *source, int dlen)
{
  while (dlen-- && *destination++)
    ;
  
  destination--; 
  
  //dlen: is the number of charecters that can be inserted including the eol charecter.
  
  while((*destination++ = *source++) && dlen-- > 1)
    ;
  
  *destination = '\0';
}
 
