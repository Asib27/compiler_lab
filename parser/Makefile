lib_path := gen/lib/bin
lib_src := gen/lib/src
header_path := gen/lib
gen := gen
lib := ${lib_path}/printer.o ${lib_path}/scopeTable.o ${lib_path}/symbolInfo.o ${lib_path}/symbolTable.o ${lib_path}/printUtil.o ${lib_path}/tokenHelper.o ${lib_path}/ast.o ${lib_path}/functionSymbolInfo.o

parser.out:	${gen}/parser.o ${gen}/lexer.o ${lib}
	g++ -ggdb3 ${gen}/parser.o ${gen}/lexer.o ${lib} -o parser.out

${gen}/parser.o: parser.y ${header_path}/ast.h
	bison -d parser.y
	mv parser.tab.c parser.tab.h ${gen}
	g++ -ggdb3 -c ${gen}/parser.tab.c -o ${gen}/parser.o

${gen}/lexer.o: scanner.l ${gen}/parser.tab.h ${header_path}/ast.h
	flex scanner.l
	mv lex.yy.c ${gen} 
	g++ -ggdb3 -c ${gen}/lex.yy.c -o ${gen}/lexer.o

${lib_path}/printUtil.o: ${lib_src}/printUtil.cpp
	g++ -c ${lib_src}/printUtil.cpp
	mv printUtil.o ${lib_path}

${lib_path}/printer.o:	${lib_src}/printer.cpp
	g++ -c ${lib_src}/printer.cpp
	mv printer.o ${lib_path}

${lib_path}/scopeTable.o:	${lib_src}/scopeTable.cpp ${header_path}/symbolInfo.h ${header_path}/scopeTable.h
	g++ -c ${lib_src}/scopeTable.cpp
	mv scopeTable.o ${lib_path}
	
${lib_path}/symbolInfo.o:	${lib_src}/symbolInfo.cpp ${header_path}/symbolInfo.h
	g++ -c ${lib_src}/symbolInfo.cpp
	mv symbolInfo.o ${lib_path}

${lib_path}/symbolTable.o:	${lib_src}/symbolTable.cpp ${header_path}/scopeTable.h ${header_path}/symbolInfo.h ${header_path}/symbolTable.h
	g++ -c ${lib_src}/symbolTable.cpp
	mv symbolTable.o ${lib_path}


${lib_path}/tokenHelper.o:	${lib_src}/tokenHelper.cpp
	g++ -c ${lib_src}/tokenHelper.cpp
	mv tokenHelper.o ${lib_path}

${lib_path}/ast.o:	${lib_src}/ast.cpp ${header_path}/ast.h
	g++ -c ${lib_src}/ast.cpp
	mv ast.o ${lib_path}

${lib_path}/functionSymbolInfo.o:	${lib_src}/functionSymbolInfo.cpp ${header_path}/symbolInfo.h ${header_path}/functionSymbolInfo.h
	g++ -c ${lib_src}/functionSymbolInfo.cpp
	mv functionSymbolInfo.o ${lib_path}

clean:
	rm ${gen}/lex.yy.c ${gen}/parser.tab.c 
	rm ${gen}/lexer.o ${gen}/parser.o
	rm parser.out
	rm gen/lib/bin/*.o