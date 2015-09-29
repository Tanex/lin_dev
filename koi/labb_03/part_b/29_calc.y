%{
	#include <stdio.h>
	#include "global.h"
	extern int tokenval;
	extern void yyerror(char*);
    extern int yylex();
%}

%token NUM ID DIV MOD DONE

%%

list : expr ';' list
	 | assignment ';' list
	 | /*empty*/
 	 ;
assignment : ID { $$ = 3; emit(ID, $1); } '=' expr { $$ = $3; emit('=', yylval); } ;
expr : expr '+' term { $$ = $1 + $3; emit('+', yylval); } 
     | expr '-' term { $$ = $1 - $3; emit('-', yylval); } 
     //| expr '?' expr ':' expr { $$ = $1 ? $3 : $5; emit('-', yylval); } 
	 | term
	 ;
term : term '*' factor { $$ = $1 * $3; emit('*', yylval); }
	 | term '/' factor { $$ = $1 / $3; emit('/', yylval); }
	 | term DIV factor { $$ = $1 / $3; emit(DIV, yylval); }
	 | term MOD factor { $$ = $1 % $3; emit(MOD, yylval); } 
	 | term '%' factor { $$ = $1 % $3; emit('%', yylval); } 
	 | term '&' factor { $$ = $1 & $3; emit('&', yylval); } 
	 | term '|' factor { $$ = $1 | $3; emit('|', yylval); } 
	 | term '<' factor { $$ = $1 < $3; emit('<', yylval); } 
	 | term '>' factor { $$ = $1 > $3; emit('>', yylval); } 
	 | factor
factor : '(' expr ')'
	   | ID { $$ = 3; emit(ID, $1); }
	   | NUM { emit(NUM, yylval); }
	   ;

%%

void yyerror(char *msg)
{
	printf("Syntax Error: %s\n", msg);
}

int yylex(void)
{
	int lex = lexan();
	yylval = tokenval;
	return lex;
}

void parse()
{
	yyparse();
}
