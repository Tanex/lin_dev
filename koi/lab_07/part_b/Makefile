OBJ = code_generator.o lexer.o parser.o symbol.o syntax_tree.o init.o error.o main.o StackMachine.o
SRC = code_generator.cpp parser.ypp symbol.cpp syntax_tree.cpp init.cpp error.cpp main.cpp lexerl.l StackMachine.cpp
EXE = StackMachine


StackMachine:	$(OBJ)
	g++ -Wall -o StackMachine $(OBJ)

main.o: 	main.cpp StackMachine.h global.h
	g++ -Wall -c main.cpp

lexer.o: lexer.c
	g++ -Wall -c lexer.c

lexer.c: lexer.l global.h
	flex -o lexer.c lexer.l

code_generator.o: code_generator.cpp global.h
	g++ -Wall -c code_generator.cpp

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d parser.ypp

parser.o: 	parser.tab.cpp global.h
	g++ -Wall -o parser.o -c parser.tab.cpp

symbol.o: 	symbol.cpp global.h
	g++ -Wall -c symbol.cpp

syntax_tree.o: syntax_tree.cpp global.h
	g++ -Wall -c syntax_tree.cpp

init.o: 	init.cpp global.h
	g++ -Wall -c init.cpp

error.o: 	error.cpp global.h
	g++ -Wall -c error.cpp

StackMachine.o: StackMachine.cpp StackMachine.h
	g++ -Wall -c StackMachine.cpp

global.h: parser.tab.hpp

clean: 
	rm -f $(EXE) $(OBJ) 29.tar.gz 29.zip parser.tab.cpp parser.tab.hpp lexer.c *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
