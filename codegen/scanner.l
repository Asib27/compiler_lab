%option noyywrap  yylineno

%x COMMENT

%{
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<utility>

#include"lib/symbolInfo.h"
#include"lib/printUtil.h"
#include"parser.tab.h"

using namespace std;

extern PrintUtil printUtil;

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
"println"	|
"case"		|
"continue"	{
				auto t = printUtil.printKeyword(yytext, yylineno);
				yylval = new SymbolAST(new SymbolInfo(yytext, t.second), yylineno);
				return t.first;
			}

		
{DIGIT}+ 	{
				printUtil.print("CONST_INT", yytext, yylineno);
				auto curSymbol =  new SymbolInfo(yytext, "CONST_INT");
				yylval = new SymbolAST(curSymbol, yylineno);
				return CONST_INT;
			}

({DIGITS}?\.{DIGITS}{EXP}?)	|
{DIGITS}{EXP}	{
					printUtil.print("CONST_FLOAT", yytext, yylineno);
					auto curSymbol =  new SymbolInfo(yytext, "CONST_FLOAT");
					yylval = new SymbolAST(curSymbol, yylineno);
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
						auto t = printUtil.printPunctuation(";", yylineno);
						yylval = new SymbolAST(new SymbolInfo(yytext, t.second), yylineno);
						return t.first;
					}
				}

[=!(){}\[\],;]	{
					// if(yytext[0] == '{'){
					// 	symbolTable.enterScope();
					// }
					// if(yytext[0] == '}'){
					// 	symbolTable.exitScope();
					// }
					auto t = printUtil.printPunctuation(yytext, yylineno);

					yylval = new SymbolAST(new SymbolInfo(yytext, t.second), yylineno);
					return t.first;
				}

"+"		|
"-"		{
			printUtil.print("ADDOP", yytext, yylineno); 
			auto curSymbol = new SymbolInfo(yytext, "ADDOP");
			yylval = new SymbolAST(curSymbol, yylineno);
			return ADDOP;
		}

"*"		|
"/"		|
"%"		{
			printUtil.print("MULOP", yytext, yylineno); 
			auto curSymbol = new SymbolInfo(yytext, "MULOP");
			yylval = new SymbolAST(curSymbol, yylineno);
			return MULOP;
		}

"++"	{
			printUtil.print("INCOP", yytext, yylineno); 
			yylval = new SymbolAST(new SymbolInfo(yytext, "INCOP"), yylineno); 
			return INCOP;
		}
"--"	{
			printUtil.print("DECOP", yytext, yylineno); 
			yylval = new SymbolAST(new SymbolInfo(yytext, "DECOP"), yylineno); 
			return DECOP;
		}

"<"		|
">"		|
"<="	|
">="	|
"=="	|
"!="	{
			printUtil.print("RELOP", yytext, yylineno); 
			auto curSymbol = new SymbolInfo(yytext, "RELOP");
			yylval = new SymbolAST(curSymbol, yylineno);
			return RELOP;
		}

"&&"	| 
"||"	{
			printUtil.print("LOGICOP", yytext, yylineno); 
			auto curSymbol = new SymbolInfo(yytext, "LOGICOP");
			yylval = new SymbolAST(curSymbol, yylineno);
			return LOGICOP;
		}

"&"		| 
"|"		|
"^"		|
"<<"	|
">>"	{
			printUtil.print("BITOP", yytext, yylineno);
			auto curSymbol = new SymbolInfo(yytext, "BITOP");
			yylval = new SymbolAST(curSymbol, yylineno);
 			return BITOP;
 		}


[_a-zA-Z][_a-zA-Z0-9]*	{
							/* IDENTIFIER */
							printUtil.print("ID", yytext, yylineno);

							SymbolInfo *s = new SymbolInfo(yytext, "ID");
							yylval = new SymbolAST(s, yylineno);
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
