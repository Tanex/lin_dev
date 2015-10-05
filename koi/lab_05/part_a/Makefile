OBJ = lexer.o parser.o  symbol.o init.o error.o main.o 
SRC = 29_lexer.l 29_calc.tab.cpp symbol.cpp init.cpp error.cpp main.cpp
EXE = infix2postfix

infix2postfix:	$(OBJ)
	gcc -Wall -o infix2postfix $(OBJ)

main.o: 	main.cpp global.h
	gcc -Wall -c main.cpp

lexer.o: lex.yy.cc global.h
	gcc -Wall -o lexer.o -c lex.yy.cc

lex.yy.cc: 29_lexer.l global.h
	flex -+ 29_lexer.l

29_calc.tab.hpp 29_calc.tab.cpp: 29_calc.ypp
	bison -d 29_calc.ypp

parser.o: 	29_calc.tab.cpp global.h
	gcc -Wall -o parser.o -c 29_calc.tab.cpp

symbol.o: 	symbol.cpp global.h
	gcc -Wall -c symbol.cpp

init.o: 	init.cpp global.h 
	gcc -Wall -c init.cpp

error.o: 	error.cpp global.h 
	gcc -Wall -c error.cpp

global.h: 29_calc.tab.hpp

clean: 
	rm -f $(EXE) $(OBJ) 29.tar.gz 29.zip *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
