OBJ = lexer.o parser.o  emitter.o symbol.o init.o error.o main.o 
SRC = lexer.cpp 29_calc.tab.cpp emitter.cpp symbol.cpp init.cpp error.cpp main.cpp
EXE = infix2postfix

infix2postfix:	$(OBJ)
	gcc -Wall -o infix2postfix $(OBJ)

main.o: 	main.cpp global.h 29_calc.tab.hpp
	gcc -Wall -c main.cpp

lexer.o: 	lexer.cpp global.h 29_calc.tab.hpp
	gcc -Wall -c lexer.cpp

29_calc.tab.hpp 29_calc.tab.cpp: 29_calc.ypp
	bison -d 29_calc.ypp

parser.o: 	29_calc.tab.cpp global.h 29_calc.tab.hpp
	gcc -Wall -o parser.o -c 29_calc.tab.cpp

emitter.o: 	emitter.cpp global.h 29_calc.tab.hpp
	gcc -Wall -c emitter.cpp

symbol.o: 	symbol.cpp global.h 29_calc.tab.hpp
	gcc -Wall -c symbol.cpp

init.o: 	init.cpp global.h 29_calc.tab.hpp
	gcc -Wall -c init.cpp

error.o: 	error.cpp global.h 29_calc.tab.hpp
	gcc -Wall -c error.cpp

clean: 
	rm -f $(EXE) $(OBJ) 29.tar.gz 29.zip *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
