OBJ = code_generator.o lex.yy.o parser.o emitter.o symbol.o syntax_tree.o init.o error.o main.o
SRC = code_generator.c 29_calc.tab.c emitter.c symbol.c syntax_tree.c init.c error.c main.c 29_lexerl.l
EXE = infix2postfix

infix2postfix:	$(OBJ)
	gcc -Wall -o infix2postfix $(OBJ)

main.o: 	main.c global.h
	gcc -Wall -c main.c

lex.yy.o: lex.yy.c
	gcc -Wall -c lex.yy.c

lex.yy.c: lexer.l global.h
	flex lexer.l

code_generator.o: code_generator.c global.h
	gcc -Wall -c code_generator.c

parser.tab.h parser.tab.c: parser.y
	bison -d parser.y

parser.o: 	parser.tab.c global.h
	gcc -Wall -o parser.o -c parser.tab.c

emitter.o: 	emitter.c global.h
	gcc -Wall -c emitter.c

symbol.o: 	symbol.c global.h
	gcc -Wall -c symbol.c

syntax_tree.o: syntax_tree.c global.h
	gcc -Wall -c syntax_tree.c

init.o: 	init.c global.h
	gcc -Wall -c init.c

error.o: 	error.c global.h
	gcc -Wall -c error.c

global.h: parser.tab.h

clean: 
	rm -f $(EXE) $(OBJ) 29.tar.gz 29.zip parser.tab.c parser.tab.h lex.yy.c *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
