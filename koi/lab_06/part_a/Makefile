OBJ = interpreter.o lex.yy.o parser.o emitter.o symbol.o syntax_tree.o init.o error.o main.o
SRC = interpreter.c 29_calc.tab.c emitter.c symbol.c syntax_tree.c init.c error.c main.c 29_lexerl.l
EXE = infix2postfix

infix2postfix:	$(OBJ)
	gcc -Wall -o infix2postfix $(OBJ)

main.o: 	main.c global.h
	gcc -Wall -c main.c

lex.yy.o: lex.yy.c
	gcc -Wall -c lex.yy.c

lex.yy.c: 29_lexer.l global.h
	flex 29_lexer.l

29_calc.tab.h 29_calc.tab.c: 29_calc.y
	bison -d 29_calc.y

interpreter.o: interpreter.c global.h
	gcc -Wall -c interpreter.c

parser.o: 	29_calc.tab.c global.h
	gcc -Wall -o parser.o -c 29_calc.tab.c

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

global.h: 29_calc.tab.h

clean: 
	rm -f $(EXE) $(OBJ) 29.tar.gz 29.zip *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
