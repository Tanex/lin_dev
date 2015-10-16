/* global.h */

#include <stdio.h>  /* include declarations for i/o routines */
#include <ctype.h>  /* ... and for character test routines */
#include <stdlib.h> /* ... and for some standard routines, such as exit */
#include <string.h> /* ... and for string routines */
#include "parser.tab.hpp"
#include "StackMachine.h"

#define BSIZE  128  /* buffer size */
#define NONE   -1
#define EOS    '\0'
#define NODE_MAX_ARGS 4

//#define NUM    256
//#define DIV    257
//#define MOD    258
//#define ID     259
//#define DONE   260

extern int tokenval;   /*  value of token attribute */  

extern StackMachine sm;

struct entry {  /*  form of symbol table entry  */
  char *lexptr; 
  int  token;    
  int value;    
};

typedef struct node {
	int node_type;
	int leaf_value;
	struct node* args[NODE_MAX_ARGS];
} node;

extern struct entry symtable[];  /* symbol table  */

extern void init();  /*  loads keywords into symtable  */
extern void error(char* m);  /*  generates all error messages  */
extern int lexan();  /*  lexical analyzer  */
extern void parse();  /*  parses and translates expression list  */
extern int insert(char *s, int tok);  /*  returns position of entry for s */
extern int lookup(char *s);  /*  returns position of entry for s */
extern void emit (int t, int tval);  /*  generates output  */


extern node* mknode(int node_type, node* arg0, node* arg1, node* arg2, node* arg3); /* creates a new node in the syntax tree */
extern node* mkleaf(int, int); /* creates a new leaf node in the syntax tree */
extern void delete_tree(node* root); /* deletes all nodes connected to the root node */
extern void treeprint(node* root); /* prints the entire tree to stdout */
extern void code_gen(node* root); /*generates stack machine code for the syntaxtree */

extern node* optimizer(node* root); /*optimizes the syntaxtree*/