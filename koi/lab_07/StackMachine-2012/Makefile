OFILES = stacktest.o StackMachine.o
CPPFLAGS = -g -Wall

stacktest: $(OFILES)
	g++ -o stacktest $(OFILES)

StackMachine.o: StackMachine.h
stacktest.o: StackMachine.h

clean:
	$(RM) $(OFILES) stacktest

archives: clean
	cd ..; \
	$(RM) StackMachine.tar StackMachine.tar.gz StackMachine.zip StackMachine-2012/StackMachine.tar StackMachine-2012/StackMachine.tar.gz StackMachine-2012/StackMachine.zip; \
	tar -cvf StackMachine.tar StackMachine-2012; \
	gzip -9 StackMachine.tar; \
	zip -r StackMachine.zip StackMachine-2012; \
	mv StackMachine.zip StackMachine-2012/StackMachine.zip; \
	mv StackMachine.tar.gz StackMachine-2012/StackMachine.tar.gz
