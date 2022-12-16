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

	char escapeToChar(char c){
		const int map_size = 11;
		const char keys[] = {'\'', '\"', 'n', 't', '\\', 'a', 'f', 'r', 'b', 'v', '0'};
		const char values[] = {'\'', '\"', '\n', '\t', '\\', '\a', '\f', '\r', '\b', '\v', '\0'};

		for(int i = 0; i < map_size; i++){
			if(keys[i] == c){
				return values[i];
			} 
		}

		return '\0';
	}

	/**
	* removes first and last char also
	*/
	string removerSlashNewline(string text){
		string ans = "";
		for(int i = 1; i < text.length()-1; i++){
			if(text[i] == '\\' && text[i+1] == '\n'){
				i++;
			}
			else{
				ans.push_back(text[i]);
			}
		}

		return ans;
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
		if(text.length() == 3){
			printHelper("CONST_CHAR", string(1, text[1]));
		}
		else{			
			printHelper("CONST_CHAR", string(1, escapeToChar(text[2])));
		}
	}

	int printString(string text){
		string ans = removerSlashNewline(text);
		printHelper("STRING", ans);

		return 0;
	}

	void printComment(string text){
		string ans = removerSlashNewline(text);
		ans = ans.substr(1, ans.length()-1);
		printLog("COMMENT", ans);
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

\"(([^"\\\n]|(\\{ESCAPES}))|("\\\n"))*\"	{
							printUtil.printString(yytext);
}

"//"(.|"\\\n")*\n	{
	printUtil.printComment(yytext);
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
