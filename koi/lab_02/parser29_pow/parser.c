/* parser.c -- without the optimizations */

#include "global.h"

int lookahead;

void match(int);
void start(), list(), expr(), moreterms(), term(), morefactors(), factor(), assignment(), expo(), moreexpo();

void parse()  /*  parses and translates expression list  */
{
  lookahead = lexan();
  start();
}

void start ()
{
  /* Just one production for start, so we don't need to check lookahead */
  list(); match(DONE);
}

void list()
{
  //if (lookahead == '(' || lookahead == ID || lookahead == NUM) {
  //  expr(); match(';'); list();
  if (lookahead == ID)
	{
		assignment();
		match(';');
		list();
	}
  else {
    /* Empty */
  }
}

//////////////////////////
//		NEW CODE		//
//////////////////////////

void assignment()
{
	if (lookahead == ID)
    {
		int id_lexeme = tokenval;
		match(ID);
		match('=');    
		emit(ID, id_lexeme);
		stack_push(id_lexeme);
		expr();
		emit('=', tokenval);
		int calc_value = stack_pop();
		symtable[stack_pop()].value = calc_value;
		printf("%s = %d\n", symtable[id_lexeme].lexptr, symtable[id_lexeme].value);
	}	
  	else 
	    error("syntax error in assignment");
}

void expo()
{
	if (lookahead == '('){
		match('('); expr(); match(')');
	}
	else if (lookahead == ID) {
		int id_lexeme = tokenval;
		match(ID);
		emit(ID, id_lexeme);
		stack_push(symtable[id_lexeme].value);
	}
	else if (lookahead == NUM) {
		int num_value = tokenval;
		match(NUM);
		emit(NUM, num_value);
		stack_push(num_value);
	}
	else
		error("syntax error in expo");
}

void moreexpo()
{
	if (lookahead == '^') {
		match('^');
		expo();
		emit('^', tokenval);
		stack_operator('^');
		moreexpo();
	}
	else{
		/*empty*/
	}
}
//////////////////////////
//		NEW CODE		//
//////////////////////////

void expr ()
{
  /* Just one production for expr, so we don't need to check lookahead */
  term(); moreterms();
}

void moreterms()
{
  if (lookahead == '+') {
	  match('+');  term(); emit('+', tokenval); stack_operator('+'); moreterms();
  }
  else if (lookahead == '-') {
	  match('-'); term(); emit('-', tokenval); stack_operator('-'); moreterms();
  }
  else {
    /* Empty */
  }
}

void term ()
{
  /* Just one production for term, so we don't need to check lookahead */
  factor(); morefactors();
}

void morefactors ()
{
  if (lookahead == '*') {
	  match('*'); factor(); emit('*', tokenval); stack_operator('*'); morefactors();
  }
  else if (lookahead == '/') {
	  match('/'); factor(); emit('/', tokenval); stack_operator('/'); morefactors();
  }
  else if (lookahead == DIV) {
    match(DIV); factor(); emit(DIV, tokenval); stack_operator(DIV); morefactors();
  }
  else if (lookahead == MOD) {
    match(MOD); factor(); emit(MOD, tokenval); stack_operator(MOD); morefactors();
  }
  else {
    /* Empty */
  }
}

void factor ()
{
  expo(); moreexpo();
}

void match(int t)
{
  if (lookahead == t)
    lookahead = lexan();
  else
    error ("syntax error in match");
}
