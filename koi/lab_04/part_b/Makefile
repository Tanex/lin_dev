OBJ = lexer.o parser.o  symbol.o init.o error.o main.o 
SRC = 29_lexer.l 29_calc.tab.c symbol.c init.c error.c main.c
EXE = infix2postfix

infix2postfix:	$(OBJ)
	gcc -Wall -o infix2postfix $(OBJ)

main.o: 	main.c global.h 
	gcc -Wall -c main.c

lexer.o: lex.yy.c
	gcc -Wall -o lexer.o -c lex.yy.c

lex.yy.c: 29_lexer.l global.h
	flex 29_lexer.l

29_calc.tab.h 29_calc.tab.c: 29_calc.y
	bison -d 29_calc.y

parser.o: 	29_calc.tab.c global.h
	gcc -Wall -o parser.o -c 29_calc.tab.c

symbol.o: 	symbol.c global.h
	gcc -Wall -c symbol.c

init.o: 	init.c global.h 
	gcc -Wall -c init.c

error.o: 	error.c global.h 
	gcc -Wall -c error.c

global.h: 29_calc.tab.h

clean: 
	rm -f $(EXE) $(OBJ) 29.tar.gz 29.zip *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
