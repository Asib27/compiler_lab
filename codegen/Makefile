lib_path := gen/lib/bin
lib_src := gen/lib/src
header_path := gen/lib
gen := gen
lib := ${lib_path}/printer.o ${lib_path}/scopeTable.o ${lib_path}/symbolInfo.o ${lib_path}/symbolTable.o ${lib_path}/printUtil.o ${lib_path}/tokenHelper.o ${lib_path}/ast.o ${lib_path}/functionSymbolInfo.o ${lib_path}/treeWalker.o ${lib_path}/variableSymbolInfo.o

cc := g++
cflags := -fpermissive -ggdb3

codegen.out:	${gen}/parser.o ${gen}/lexer.o ${lib}
	${cc} ${cflags} ${gen}/parser.o ${gen}/lexer.o ${lib} -o parser.out

${gen}/parser.o: parser.y ${header_path}/ast.h ${header_path}/functionSymbolInfo.h ${header_path}/variableSymbolInfo.h ${header_path}/printUtil.h
	bison -d parser.y
	mv parser.tab.c parser.tab.h ${gen}
	${cc} ${cflags} -c ${gen}/parser.tab.c -o ${gen}/parser.o

${gen}/lexer.o: scanner.l ${gen}/parser.tab.h ${header_path}/ast.h
	flex scanner.l
	mv lex.yy.c ${gen} 
	${cc} ${cflags} -c ${gen}/lex.yy.c -o ${gen}/lexer.o

${lib_path}/printUtil.o: ${lib_src}/printUtil.cpp
	${cc} ${cflags} -c ${lib_src}/printUtil.cpp
	mv printUtil.o ${lib_path}

${lib_path}/printer.o:	${lib_src}/printer.cpp
	${cc} ${cflags} -c ${lib_src}/printer.cpp
	mv printer.o ${lib_path}

${lib_path}/scopeTable.o:	${lib_src}/scopeTable.cpp ${header_path}/symbolInfo.h ${header_path}/scopeTable.h
	${cc} ${cflags} -c ${lib_src}/scopeTable.cpp
	mv scopeTable.o ${lib_path}
	
${lib_path}/symbolInfo.o:	${lib_src}/symbolInfo.cpp ${header_path}/symbolInfo.h
	${cc} ${cflags} -c ${lib_src}/symbolInfo.cpp
	mv symbolInfo.o ${lib_path}

${lib_path}/symbolTable.o:	${lib_src}/symbolTable.cpp ${header_path}/scopeTable.h ${header_path}/symbolInfo.h ${header_path}/symbolTable.h
	${cc} ${cflags} -c ${lib_src}/symbolTable.cpp
	mv symbolTable.o ${lib_path}


${lib_path}/tokenHelper.o:	${lib_src}/tokenHelper.cpp
	${cc} ${cflags} -c ${lib_src}/tokenHelper.cpp
	mv tokenHelper.o ${lib_path}

${lib_path}/ast.o:	${lib_src}/ast.cpp ${header_path}/ast.h
	${cc} ${cflags} -c ${lib_src}/ast.cpp
	mv ast.o ${lib_path}

${lib_path}/functionSymbolInfo.o:	${lib_src}/functionSymbolInfo.cpp ${header_path}/symbolInfo.h ${header_path}/functionSymbolInfo.h
	${cc} ${cflags} -c ${lib_src}/functionSymbolInfo.cpp
	mv functionSymbolInfo.o ${lib_path}

${lib_path}/variableSymbolInfo.o:	${lib_src}/variableSymbolInfo.cpp ${header_path}/symbolInfo.h ${header_path}/variableSymbolInfo.h
	${cc} ${cflags} -c ${lib_src}/variableSymbolInfo.cpp
	mv variableSymbolInfo.o ${lib_path}

${lib_path}/treeWalker.o:	${lib_src}/treeWalker.cpp ${header_path}/treeWalker.h ${header_path}/variableSymbolInfo.h ${header_path}/functionSymbolInfo.h 
	${cc} ${cflags} -ggdb3 -c ${lib_src}/treeWalker.cpp
	mv treeWalker.o ${lib_path}

clean:
	rm ${gen}/lex.yy.c ${gen}/parser.tab.c 
	rm ${gen}/lexer.o ${gen}/parser.o
	rm parseTree.txt log.txt error.txt token.txt
	rm parser.out
	rm gen/lib/bin/*.o