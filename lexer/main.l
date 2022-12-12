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

		fprintf(tokenout,"<%s, %s>\n",upper.c_str(), text.c_str());
		fprintf(logout,"Line# %d: TOKEN <%s> Lexeme %s found\n",yylineno,upper.c_str(), text.c_str());
	}

	void setOutput(FILE *logout, FILE* tokenout){
		this->logout = logout;
		this->tokenout = tokenout;
	}
};

PrintUtil printUtil(nullptr, nullptr);

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \n

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
				printUtil.printKeyword(string(yytext));
			}

"+"		|

"-"		{
			fprintf(tokenout,"<ADDOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ADDOP> Lexeme %s found\n",yylineno,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}
		
{DIGIT}+ 	{
				fprintf(tokenout,"<CONST_INT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <CONST_INT> Lexeme %s found\n",yylineno,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
				SymbolInfo *si=new SymbolInfo(string(yytext),"CONST_INT");
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
