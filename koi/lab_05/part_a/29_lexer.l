%{
#include "global.h"
//#include "29_calc.tab.hpp"
extern int lineno;
%}

%option noyywrap
%option c++

%%

[ \t]		{ /* ignore whitespace */ }
'\n'		{ lineno++; }
[0-9]+ 		{ yylval = atoi(yytext); return NUM; }
mod			{ return MOD; }
div			{ return DIV; }
[a-zA-Z]+ 	{       
				int p = lookup (yytext);
		        if (p == 0)
		        	p = insert (yytext, ID);
		      	yylval = p;
		      	return symtable[p].token;
		  	}
.			{ return *yytext; }
<<EOF>>		{ return DONE; }

%%

int lineno = 1;