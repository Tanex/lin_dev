/* global.h */

#include <stdio.h>  /* include declarations for i/o routines */
#include <ctype.h>  /* ... and for character test routines */
#include <stdlib.h> /* ... and for some standard routines, such as exit */
#include <string.h> /* ... and for string routines */

#define BSIZE  128  /* buffer size */
#define NONE   -1
#define EOS    '\0'

#define NUM    256
#define DIV    257
#define MOD    258
#define ID     259
#define DONE   260

#define STACK_SIZE 50

extern int tokenval;   /*  value of token attribute */  
extern int lineno;

struct entry {  /*  form of symbol table entry  */
  char *lexptr; 
  int  token;
  int value;    
};

struct stack
{
	int stack_array[STACK_SIZE];
	int top_free;
};

extern struct entry symtable[];  /* symbol table  */

extern void init();  /*  loads keywords into symtable  */
extern void error(char* m);  /*  generates all error messages  */
extern int lexan();  /*  lexical analyzer  */
extern void parse();  /*  parses and translates expression list  */
extern int insert(char *s, int tok);  /*  returns position of entry for s */
extern int lookup(char *s);  /*  returns position of entry for s */
extern int setvalue(char *s, int val); /* returns the value of entry for s */
extern int getvalue(char *s); /* returns the value of entry for s */
extern void emit (int t, int tval);  /*  generates output  */

extern void stack_init();//Initializes the stack for use						 
extern int stack_pop();//Pops the top entry on the stack and puts it into value					   
extern void stack_push(int value);//Pushes value onto the top of the stack
extern void stack_operator(int oper);//Performs the given operator on the calculation stack