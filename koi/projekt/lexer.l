%{
#include "global.h"
#include <string.h>
%}

%option noyywrap

%%

[ \t]		{ /* ignore whitespace */ }
'\n'		{ }
[0-9]+ 		{ yylval.val = atoi(yytext); return NUM; }
mod			{ return MOD; }
div			{ return DIV; }
while 		{ return WHILE; } 
if 			{ return IF; } 
else 		{ return ELSE; } 
int         { return VARINT; }
str         { return VARSTR; }         
print		{ return PRINT; } 
read 		{ return READ; }
[a-zA-Z]+ 	{       
				int p = lookup (yytext);
		        if (p == 0)
		        	p = insert (yytext, ID);
		      	yylval.val = p;
		      	return symtable[p].token;
		  	}
\"[A-Za-z]*\" { strcpy(yylval.str, yytext); return STR; }
.			{ return *yytext; }
<<EOF>>		{ return DONE; }

%%
