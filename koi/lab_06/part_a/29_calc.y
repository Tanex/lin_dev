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

%type <root> expr statement statementlist
%type <val> NUM ID

%token NUM ID DIV MOD DONE WHILE IF ELSE PRINT READ ASGMNTID

%right '='
%nonassoc IFNOELSE
%nonassoc '?' ':' ELSE
%nonassoc '<' '>'
%left '+' '-'
%left '*' '/' '%' DIV MOD
%left '|' '&' 

%%

list : statementlist '@' { printf("%d", interpreter($1)); delete_tree($1); } list 
	 | /*empty*/


statementlist : statement statementlist					{ $$ = mknode(';', $1, $2, 0, 0); }
			  | /*empty*/								{ $$ = 0; }

statement : expr ';' 									{ $$ = $1; }
		  | WHILE '(' expr ')' statement				{ $$ = mknode(WHILE, $3, $5, 0, 0); }
		  | IF '(' expr ')' statement					{ $$ = mknode(IF, $3, $5, 0, 0); } %prec IFNOELSE
		  | IF '(' expr ')' statement ELSE statement 	{ $$ = mknode(IF, $3, $5, $7, 0); }
		  | PRINT '(' ID ')' ';'						{ $$ = mknode(PRINT, mkleaf(ASGMNTID, $3), 0, 0, 0); } 
		  | READ '(' ID ')' ';'							{ $$ = mknode(READ, mkleaf(ASGMNTID, $3), 0, 0, 0); }
		  | '{' statementlist '}'						{ $$ = $2; }
		  ;


expr : NUM 						{ $$ = mkleaf(NUM, $1);	}
	 | ID  						{ $$ = mkleaf(ID, $1); }
	 | ID '=' expr				{ $$ = mknode('=', mkleaf(ASGMNTID, $1), $3, 0, 0); }
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

void parse()
{
	yyparse();
}

