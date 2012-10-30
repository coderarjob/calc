static int pullfromstack = 0;

extern int pop (float*); //or include stack.h
extern int push(float);

/*
Returns charecter from input array or from stack.
Errors: -1, if stack is empty when poped. 	
*/
int getch(char *c)
{
  extern char expr[];
  extern int e_index;
  
  extern int pullfromstack;
  extern int pop(float*);	
  
  //printf("\npullfromstack = %d", pullfromstack);
  
  if (pullfromstack > 0)
  {
    float m;
    if (pop(&m) < 0)
      return -1;

    *c = (char) m;
    
    pullfromstack--;
  }
  else
    *c = expr[e_index++];
	  
  return 1;
}

/*
Puts charecter into stack and the next call to getch() will pop the charecter from stack.
Errors:	-1, if stack is full.
*/

int ungetch(char c)
{	
  extern int pullfromstack;
  extern int push(float);
	  
  int ret = push((float)c); 

  if (ret < 0)
    return -1;

  pullfromstack++;	
  
  return 1;
}

