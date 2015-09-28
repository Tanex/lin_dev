%{
	#include <stdio.h>
	#include "global.h"
	extern int tokenval;
	extern void yyerror(char*);
%}

%token NUM ID DIV MOD DONE

%%

list : expr ';' list
	 | assignment ';' list
	 | /*empty*/
 	 ;
assignment : ID { $$ = 3; emit(ID, tokenval); } '=' expr { $$ = $3; emit('=', tokenval); } ;
expr : expr '+' term { $$ = $1 + $3; emit('+', tokenval); } 
     | expr '-' term { $$ = $1 - $3; emit('-', tokenval); } 
	 | term
	 ;
term : term '*' factor { $$ = $1 * $3; emit('*', tokenval); }
	 | term '/' factor { $$ = $1 / $3; emit('/', tokenval); }
	 | term DIV factor { $$ = $1 / $3; emit(DIV, tokenval); }
	 | term MOD factor { $$ = $1 % $3; emit(MOD, tokenval); }
	 | factor
factor : '(' expr ')'
	   | ID { $$ = 3; emit(ID, tokenval); }
	   | NUM { $$ = tokenval; emit(NUM, tokenval); }
	   ;

%%

void yyerror(char *msg)
{
	printf("Syntax Error: %s\n", msg);
}

int yylex(void)
{
	return lexan();
}

void parse()
{
	yyparse();
}
