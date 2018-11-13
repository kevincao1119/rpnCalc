#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int op_subtract(struct tokenStack *stack);
static int op_multiply(struct tokenStack *stack);
static int op_divide(struct tokenStack *stack);
static int op_GThan(struct tokenStack *stack);/*-push 1 if n1 > n2 and 0 otherwise*/ 
static int op_GEThan(struct tokenStack *stack);/*-push 1 if n1 >= n2 and 0 otherwise*/ 
static int op_LThan(struct tokenStack *stack);/* -push 1 if n1 < n2 and 0 otherwise */
static int op_LEThan(struct tokenStack *stack);/* -push 1 if n1 <= n2 and 0 otherwise */
static int op_MODQuot(struct tokenStack *stack);/*- push remainder then quotient */
static int op_equal(struct tokenStack *stack);
static int op_MOD(struct tokenStack *stack);/* - push two copies of n1 onto the stack */
static int op_SWAP(struct tokenStack *stack);
static int op_HELP(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
<<<<<<< HEAD
}
 ops[] = {
=======
} 
ops[] = {
>>>>>>> 3db415cf4994913f2ad060d210352fed3d480877
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_subtract},
  {"*", op_multiply},
  {"/", op_divide},
  {"GT", op_GThan},
  {"GE", op_GEThan},
  {"LT", op_LThan},
  {"LE", op_LEThan},
  {"MODQ", op_MODQuot},
  {"MOD", op_MOD},
  {"EQ", op_equal},
  {"SWAP", op_SWAP},
  {"HELP", op_HELP},

  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{  
  struct lexToken *t = popTokenStack(s);	
  int temp = atoi(t->symbol); /* convert the char symbol to int */	  
  freeToken(t);   
  return temp;
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{  /* 
   		-given a stack and an int, push the int onto the stack,
   		-need to turn int into char to push onto stack
   		-once char is achieved, need to put it in a lexToken (encode) to push onto stack
   		-call pushTokenStack and pass stack and lextoken
  	  */
  struct lexToken *t = allocToken();
  
  char str[MAX_SYMBOL_LENGTH]; 
  sprintf(str,"%d", v);  /*turn int v into char and put in array*/
  
  /*char temp = (char) (v + '0');  convert the int to char symbol  
  printf("this is  pushing  %s \n", str); */
  
  /* place char into the lextoken at symbol[0] */
    t->kind = LEX_TOKEN_NUMBER;  
    
    strncpy(t->symbol, str, MAX_SYMBOL_LENGTH);   /* copy all of new string array into t->symbol */
    
  /*  t->symbol[1]= temp;*/
    
  /*  t->symbol = '\0';
    printf("this is t->symbol  %s \n", t->symbol); */

   /*  then push lextoken onto the stack*/
 pushTokenStack(s,t);
}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_HELP(struct tokenStack *stack)
{
   printf("+  - push n1+n2\n");
   printf("-  - push n1-n2\n");
   printf("*  - push n1*n2\n");
   printf("/  - push n1/n2\n");
   printf("GT - push 1 if n1 > n2 and 0 otherwise\n");
   printf("LT - push 1 if n1 < n2 and 0 otherwise\n");
   printf("GT - push 1 if n1 >= n2 and 0 otherwise\n");
   printf("LE - push 1 if n1 <= n2 and 0 otherwise \n");
   printf("EQ - push 1 if n1 == n2 and 0 otherwise \n");
   printf("MOD - push two copies of n1 onto the stack\n");
   printf("MODQ - push remainder then quotient \n");
   printf("SWAP -  swap the order of the top two elements on the stack \n");
   return (0);
}
static int op_subtract(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2-v1);
  return(0);
}
static int op_multiply(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2*v1);
  return(0);
}

static int op_divide(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2/v1);
  return(0);
}

static int op_GThan(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v2>v1){
  	pushInt(stack, 1);
  }
  else{
	pushInt(stack, 0);
  }
  return(0);
}

static int op_LThan(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v2<v1){
 	 pushInt(stack, 1);
  }
  else{
	 pushInt(stack, 0);
  }
  return(0);
}

static int op_GEThan(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v2>=v1){
 	 pushInt(stack, 1);
  }
  else{
	 pushInt(stack, 0);
  }
  return(0);
}

static int op_LEThan(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v2<=v1){
         pushInt(stack, 1);
  }
  else{
         pushInt(stack, 0);
  }
  return(0);
}

static int op_equal(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v2==v1){
         pushInt(stack, 1);
  }
  else{
         pushInt(stack, 0);
  }
  return(0);
}

static int op_MOD(struct tokenStack *stack)
{
  int v1;
  v1 = popInt(stack);
  pushInt(stack, v1);
  pushInt(stack, v1);
  return(0);
}


static int op_MODQuot(struct tokenStack *stack)
{
  int v1;
  int v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2%v1);
  pushInt(stack, v2/v1);
  return(0);
}

static int op_SWAP(struct tokenStack *stack)
{
  int v1;
  int v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1);
  pushInt(stack, v2);
  return(0);
}
