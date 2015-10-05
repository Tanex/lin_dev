%{
	#include <stdio.h>
	#include "global.h"
	extern int tokenval;
	extern void yyerror(char*);
    extern int yylex();
	int power(int base, int exp);
%}

%token NUM ID DIV MOD DONE

%nonassoc '?' ':'
%nonassoc '<' '>'
%left '+' '-'
%left '*' '/' '%' DIV MOD
%left '^'
%left '|' '&' 

%%

list : expr ';' list
	 | assignment ';' list
	 | /*empty*/
 	 ;

assignment : ID { printf("%s\n", symtable[$1].lexptr); } '=' expr { printf("=\n"); symtable[$1].value = $4; $$ = $4; printf("%s = %d\n", symtable[$1].lexptr, symtable[$1].value); };

expr : NUM 						{ $$ = $1; printf("%d\n", $1); }
	 | ID  						{ $$ = symtable[$1].value; printf("%s\n", symtable[$1].lexptr); }
	 | '(' expr ')'  			{ $$ = $2; }
	 | expr '+' expr 			{ $$ = $1 + $3; printf("+\n"); }
	 | expr '-' expr 			{ $$ = $1 - $3; printf("-\n"); }
	 | expr '*' expr 			{ $$ = $1 * $3; printf("*\n"); }
	 | expr '/' expr 			{ $$ = $1 / $3; printf("/\n"); }
	 | expr DIV expr 			{ $$ = div($1, $3).quot; printf("DIV\n"); }
	 | expr MOD expr 			{ $$ = $1 % $3; printf("MOD\n"); }
	 | expr '%' expr 			{ $$ = $1 % $3; printf("%%\n"); }
	 | expr '&' expr 			{ $$ = $1 & $3; printf("&\n"); }
	 | expr '|' expr 			{ $$ = $1 | $3; printf("|\n"); }
	 | expr '<' expr 			{ $$ = $1 < $3; printf("<\n"); }
	 | expr '>' expr  			{ $$ = $1 > $3; printf(">\n"); }
	 | expr '?' expr ':' expr 	{ $$ = $1 ? $3 : $5; printf("?:\n"); }
	 | expr '^' expr			{ $$ = power($1, $3); printf("^\n"); }
	 ;

%%

void yyerror(char *msg)
{
	printf("Syntax Error: %s\n", msg);
}

void parse()
{
	yyparse();
}

int power(int base, int exp)
{
	int i;
	if (exp < 0)
		return 0;
	int sum = 1;
	for(i = 0; i < exp; i++)
	{
		sum *= base;
	}
	return sum;
}