%option noyywrap  yylineno

%{
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>

using namespace std;


FILE *logout;
FILE *tokenout;

class SymbolInfo{
public:
	string symbol;
	string type;
	SymbolInfo(){
		symbol="";type="";
	}
	SymbolInfo(string symbol,string type){
		this->symbol=symbol;this->type=type;
	}
};
class ScopeTable{
	vector<SymbolInfo *> syminfo;
	public:
	void insert(SymbolInfo *s){
		syminfo.push_back(s);
	}
	void print(){
		for(int i=0;i<syminfo.size();i++){
			fprintf(logout,"\n%s %s\n",syminfo[i]->symbol.c_str(),syminfo[i]->type.c_str());
		}
	}
};

ScopeTable st;

class PrintUtil{
	FILE *logout;
	FILE *tokenout;

	void printLog(string token, string symbol){
		fprintf(logout,"Line# %d: TOKEN <%s> Lexeme %s found\n",yylineno,token.c_str(), symbol.c_str());
	}

	void printToken(string token, string symbol){
		fprintf(tokenout,"<%s, %s>\n",token.c_str(), symbol.c_str());
	}

	void printHelper(string token, string symbol){
		printLog(token, symbol);
		printToken(token, symbol);
	}

public:
	PrintUtil(FILE *logout, FILE* tokenout){
		this->logout = logout;
		this->tokenout = tokenout;
	}

	void printKeyword(string text){
		string upper = "";
		for(auto i: text){
			if(i >= 'a' && i <= 'z')
				upper.push_back(i - 'a' + 'A');
			else upper.push_back(i);
		}

		printHelper(upper, text);
	}

	void print(string token, string text){
		printHelper(token, text);
	}

	void setOutput(FILE *logout, FILE* tokenout){
		this->logout = logout;
		this->tokenout = tokenout;
	}

	void printPunctuation(string text){
		char c = text[0];

		string keys = "=!(){}[],;";
		string values[] = {"ASSIGNOP", "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL",
			"LSQUARE", "RSQUARE", "COMMA", "SEMICOLON"
		};

		for(int i = 0; i < keys.length(); i++){
			if(c == keys[i]){
				printHelper(values[i], string(1, c));
			}
		}
	}

	void printChar(string text){
		const int map_size = 11;
		const char keys[] = {'\'', '\"', 'n', 't', '\\', 'a', 'f', 'r', 'b', 'v', '0'};
		const char values[] = {'\'', '\"', '\n', '\t', '\\', '\a', '\f', '\r', '\b', '\v', '\0'};

		if(text.length() == 3){
			printHelper(string("CONST_CHAR"), string(1, text[1]));
		}
		else{			
			for(int idx = 0; idx < map_size; idx++){
				if(keys[idx] == text[2]){
					printHelper(string("CONST_CHAR"), string(1, values[idx]));
					return ;
				} 
			}
		}
	}

};

PrintUtil printUtil(nullptr, nullptr);

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
DIGITS ({DIGIT}+)
EXP (E[+-]?{DIGITS})
NEWLINE \n
ESCAPES ['"nt\\afrbv0]

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
				printUtil.printKeyword(yytext);
			}

		
{DIGIT}+ 	{
				printUtil.print("CONST_INT", yytext);
			}

({DIGITS}?\.{DIGITS}{EXP}?)	|
{DIGITS}{EXP}	{
					printUtil.print("CONST_FLOAT", yytext);
				}

'([^'\\]|(\\{ESCAPES}))'	{
					printUtil.printChar(yytext);
				}

[=!(){}\[\],;]	{
					printUtil.printPunctuation(yytext);
				}

"+"		|
"-"		{printUtil.print("ADDOP", yytext);}

"*"		|
"/"		|
"%"		{printUtil.print("MULOP", yytext);}

"++"	|
"--" 	{printUtil.print("INCOP", yytext);}

"<"		|
">"		|
"<="	|
">="	|
"=="	|
"!="	{printUtil.print("RELOP", yytext);}

"&&"	| 
"||"	{printUtil.print("LOGIOP", yytext);}

"&"		| 
"|"		|
"^"		|
"<<"	|
">>"	{printUtil.print("BITOP", yytext);}


[_a-zA-Z][_a-zA-Z0-9]*	{
							printUtil.print("ID", yytext);
							//TODO: change into my implementation
							SymbolInfo *si=new SymbolInfo(string(yytext),"ID");
							st.insert(si);
						}	

.			{}
%%

int main(int argc, char** argv) {
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	logout= fopen("log.txt","w");
	tokenout= fopen("token.txt","w");
	printUtil.setOutput(logout, tokenout);

	yyin= fin;
	yylex();
	st.print();
	fclose(yyin);
	fclose(tokenout);
	fclose(logout);
	return 0;
}
