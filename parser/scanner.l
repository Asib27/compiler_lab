%option noyywrap  yylineno

%x COMMENT

%{
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include"lib/symbolTable.h"
#include"lib/symbolInfo.h"
#include"lib/printer.h"
#include"lib/printUtil.h"
#include"lib/ast.h"
#include"y.tab.h"

using namespace std;

extern ofstream logout, tokenout;
PrintUtil printUtil(tokenout, logout);
extern SymbolTable symbolTable;
extern YYSTYPE yylval;
extern SymbolInfo *curSymbol;

int error_count = 0;
string multilineComment = "";
int multilineCommentStart = 0;

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
DIGITS ({DIGIT}+)
EXP (E[+-]?{DIGITS})
NEWLINE \n
ESCAPES ['"nt\\afrbv0a-zA-z0-9]

%%
\n		{}

"if"		|		
"for"		|
"do"		|
"int"		|
"float"		|
"void"		|
"switch"	|
"default"	|
"else"		|
"while"		|
"break"		|
"char"		|
"double"	|
"return"	|
"case"		|
"continue"	{
				return printUtil.printKeyword(yytext, yylineno);
			}

		
{DIGIT}+ 	{
				printUtil.print("CONST_INT", yytext, yylineno);
				curSymbol =  new SymbolInfo(yytext, "CONST_INT");
				return CONST_INT;
			}

({DIGITS}?\.{DIGITS}{EXP}?)	|
{DIGITS}{EXP}	{
					printUtil.print("CONST_FLOAT", yytext, yylineno);
					curSymbol =  new SymbolInfo(yytext, "CONST_FLOAT");
					return CONST_FLOAT;
				}

{DIGITS}?((\.)+{DIGITS}){2,}{EXP}?	|
{DIGITS}?(\.)+{DIGITS}?	{
	printUtil.printError("TOO_MANY_DECIMAL_POINTS", yytext, yylineno);
}

{DIGITS}(\.{DIGITS})?(E+[+-]?{DIGITS}?(\.)[0-9(\.)]*)	{
	printUtil.printError("ILLFORMED_NUMBER", yytext, yylineno);
}

'([^'\\\n]|(\\{ESCAPES}))*'	{
					printUtil.printChar(yytext, yylineno);
					return CONST_CHAR;
				}

"'\\'"	|
'([^'\\\n;]|(\\{ESCAPES}))*(\n|";")	{
					string text = yytext;
					bool isNewLine = (text.back() == '\n');

					text = text.substr(0, text.length()-1);
					printUtil.printError("UNFINISHED_CONST_CHAR", text, yylineno - isNewLine);
					if(!isNewLine){ 
						printUtil.printPunctuation(";", yylineno);
					}
				}

[=!(){}\[\],;]	{
					// if(yytext[0] == '{'){
					// 	symbolTable.enterScope();
					// }
					// if(yytext[0] == '}'){
					// 	symbolTable.exitScope();
					// }
					return printUtil.printPunctuation(yytext, yylineno);
				}

"+"		|
"-"		{
			printUtil.print("ADDOP", yytext, yylineno); 
			curSymbol = new SymbolInfo(yytext, "ADDOP");
			return ADDOP;
		}

"*"		|
"/"		|
"%"		{
			printUtil.print("MULOP", yytext, yylineno); 
			curSymbol = new SymbolInfo(yytext, "MULOP");
			return MULOP;
		}

"++"	{printUtil.print("INCOP", yytext, yylineno); return INCOP;}
"--"	{printUtil.print("DECOP", yytext, yylineno); return DECOP;}

"<"		|
">"		|
"<="	|
">="	|
"=="	|
"!="	{
			printUtil.print("RELOP", yytext, yylineno); 
			curSymbol = new SymbolInfo(yytext, "RELOP");
			return RELOP;
		}

"&&"	| 
"||"	{
			printUtil.print("LOGIOP", yytext, yylineno); 
			curSymbol = new SymbolInfo(yytext, "LOGICOP");
			return LOGICOP;
		}

"&"		| 
"|"		|
"^"		|
"<<"	|
">>"	{
			printUtil.print("BITOP", yytext, yylineno);
			curSymbol = new SymbolInfo(yytext, "BITOP");
 			return BITOP;
 		}


[_a-zA-Z][_a-zA-Z0-9]*	{
							printUtil.print("ID", yytext, yylineno);

							SymbolInfo *s = symbolTable.lookup(yytext);
							if(s==nullptr){
								SymbolInfo symbolInfo(yytext, "ID");
								s = symbolTable.insert(symbolInfo);
							}

							//yylval = (YYSTYPE)s;
							
							curSymbol = s;
							return ID;
						}	

[0-9][_a-zA-Z0-9]+		{
							printUtil.printError("INVALID_ID_SUFFIX_NUM_PREFIX", yytext, yylineno);
						}

\"(([^"\\\n]|(\\{ESCAPES}))|("\\\n"))*\"	{
							printUtil.printString(yytext, yylineno);
}
\"(([^"\\\n]|(\\{ESCAPES}))|("\\\n"))*\n	{
	string text = yytext;
	int newLineCount = 0;
	for(auto i: text) if(i == '\n') newLineCount++;

	printUtil.printError("UNFINISHED_STRING", text.substr(0, text.length()-1), yylineno-newLineCount);
}

"//"(.|"\\\n")*\n	{
	printUtil.printComment(yytext, yylineno);
}

"/*"					{
							BEGIN(COMMENT);
							multilineCommentStart = yylineno;
						}
<COMMENT>"*/"			{
							BEGIN(INITIAL);
							printUtil.printMultilineComment(multilineComment, yylineno);
							multilineComment = "";
						}
<COMMENT>([^*]|\n)+|.	{
							multilineComment.append(yytext);
						}
<COMMENT><<EOF>>		{
							if(multilineComment.back() == '\n') multilineComment.pop_back();
							printUtil.printError("UNFINISHED_COMMENT", "/*" + multilineComment, multilineCommentStart);
							multilineComment = "";
							yylineno--;
							BEGIN(INITIAL);
						}

[ \t\n]+		{ /* IGNORE */}
.				{printUtil.printError("UNRECOGNIZED_CHAR", yytext, yylineno);}
%%

// int main(int argc, char** argv) {
// 	if(argc!=2){
// 		printf("Please provide input file name and try again\n");
// 		return 0;
// 	}
	
// 	FILE *fin=fopen(argv[1],"r");
// 	if(fin==NULL){
// 		printf("Cannot open specified file\n");
// 		return 0;
// 	}
	

// 	yyin= fin;
// 	yylex();
	
// 	logout << symbolTable;
// 	logout << "Total lines: " << yylineno << endl;
// 	logout << "Total errors: " << printUtil.getErrorCount() << endl;

// 	fclose(yyin);

// 	return 0;
// }
