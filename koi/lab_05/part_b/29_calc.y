%{
	#include <stdio.h>
	#include "global.h"
	extern int tokenval;
	extern void yyerror(const char*);
	extern int yylex();
%}

%union {	
	int val;
	struct node* root;
}

%type <root> expr;
%type <val> NUM ID

%token NUM ID DIV MOD DONE
%right '='
%left '+' '-'
%left '*' '/' '%' DIV MOD
%nonassoc '?' ':'
%nonassoc '<' '>'
%left '|' '&' 

%%

list : expr ';' { treeprint($1); delete_tree($1); } list 
	 | /*empty*/
//assignment : ID { printf("%s\n", symtable[$1].lexptr); } '=' expr { printf("=\n"); symtable[$1].value = $4; $$ = $4; printf("%s = %d\n", symtable[$1].lexptr, symtable[$1].value); };

expr : NUM 						{ $$ = mkleaf(NUM, $1);	}
	 | ID  						{ $$ = mkleaf(ID, $1); }
	 | ID '=' expr				{ $$ = mknode('=', mkleaf(ID, $1), $3, 0, 0); }
	 | '(' expr ')'  			{ $$ = $2; }
	 | expr '+' expr 			{ $$ = mknode('+', $1, $3, 0, 0); }
	 | expr '-' expr 			{ $$ = mknode('-', $1, $3, 0, 0); }
	 | expr '*' expr 			{ $$ = mknode('*', $1, $3, 0, 0); }
	 | expr '/' expr 			{ $$ = mknode('/', $1, $3, 0, 0); }
	 | expr DIV expr 			{ $$ = mknode(DIV, $1, $3, 0, 0); }
	 | expr MOD expr 			{ $$ = mknode(MOD, $1, $3, 0, 0); }
	 | expr '%' expr 			{ $$ = mknode('%', $1, $3, 0, 0); }
	 | expr '&' expr 			{ $$ = mknode('&', $1, $3, 0, 0); }
	 | expr '|' expr 			{ $$ = mknode('|', $1, $3, 0, 0); }
	 | expr '<' expr 			{ $$ = mknode('<', $1, $3, 0, 0); }
	 | expr '>' expr  			{ $$ = mknode('>', $1, $3, 0, 0); }
	 | expr '?' expr ':' expr 	{ $$ = mknode('?', $1, $3, $5, 0); }
	 ;

%%

void yyerror(const char *msg)
{
	printf("Syntax Error: %s\n", msg);
}

/*
int yylex(void)
{
	int lex = lexan();
	if (lex == NUM || lex == ID)
		yylval.val = tokenval;
	//debug
	//if (lex < 256)
	//	printf("debug yylex char: %c\n", lex);
	//else
	//	printf("debug yylex int: %d\n", lex);
	//return lex;
}*/

void parse()
{
	yyparse();
}

