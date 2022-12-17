lexer.out: main.l lib/bin/printer.o lib/bin/scopeTable.o lib/bin/symbolInfo.o lib/bin/symbolTable.o lib/bin/printUtil.o
	flex main.l
	g++ -c lex.yy.c
	g++ -o lexer.out lex.yy.o lib/bin/printer.o lib/bin/scopeTable.o lib/bin/symbolInfo.o lib/bin/symbolTable.o lib/bin/printUtil.o

lib/bin/printUtil.o: lib/src/printUtil.cpp
	g++ -c lib/src/printUtil.cpp
	mv printUtil.o lib/bin/

lib/bin/printer.o:	lib/src/printer.cpp
	g++ -c lib/src/printer.cpp
	mv printer.o lib/bin/

lib/bin/scopeTable.o:	lib/src/scopeTable.cpp
	g++ -c lib/src/scopeTable.cpp
	mv scopeTable.o lib/bin/
	
lib/bin/symbolInfo.o:	lib/src/symbolInfo.cpp
	g++ -c lib/src/symbolInfo.cpp
	mv symbolInfo.o lib/bin/

lib/bin/symbolTable.o:	lib/src/symbolTable.cpp
	g++ -c lib/src/symbolTable.cpp
	mv symbolTable.o lib/bin/

clean:
	rm lexer.out