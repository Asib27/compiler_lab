%option noyywrap  yylineno

%x COMMENT

%{
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

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
			// fprintf(logout,"\n%s %s\n",syminfo[i]->symbol.c_str(),syminfo[i]->type.c_str());
		}
	}
};

ScopeTable st;

class PrintUtil{
	ostream& logos;
	ostream& tokenos;

	void printLog(string token, string symbol){
		logos << "Line# " << yylineno << ": Token <" << token 
			<< "> Lexeme " << symbol << "found" << endl;
		// fprintf(logout,"Line# %d: TOKEN <%s> Lexeme %s found\n",yylineno,token.c_str(), symbol.c_str());
	}

	void printToken(string token, string symbol){
		tokenos << "<" << token << ", " << symbol << ">" << endl;
		// fprintf(tokenout,"<%s, %s>\n",token.c_str(), symbol.c_str());
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

		//TODO: EMPTY CHAR HANDLE CODE
		return c;
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

	string insertEscapeInString(string text){
		string ans = "";

		for(int i = 0; i < text.length() -1; i++){
			if(text[i] == '\\'){
				char c = escapeToChar(text[i+1]);
				ans.append(1,c);
				i++;
			}
			else{
				ans.append(1,text[i]);
			}
		}

		// insert last char as it will not be processed
		if(text.length() > 2 && text[text.length()-2] != '\\')
			ans.append(1,text.back());
		return ans;
	}

public:
	PrintUtil(ostream &token, ostream &log)
		: tokenos(token), logos(log)
	{

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
		if(text.length() == 2){
			printError("EMPTY_CONST_CHAR", text);
		}
		else if(text.length() == 3){
			printHelper("CONST_CHAR", string(1, text[1]));
		}
		else if(text.length() == 4 && text[1] == '\\'){			
			//TODO: EMPTY CHAR HANDLE CODE
			printHelper("CONST_CHAR", string(1, escapeToChar(text[2])));
		}
		else{
			printError("MULTICHAR_CONST_CHAR", text);
		}
	}

	int printString(string text){
		string singleLine = removerSlashNewline(text);
		string ans = insertEscapeInString(singleLine);

		if(singleLine.length() < text.length() - 2){
			printHelper("MULTI LINE STRING", ans);
		}
		else
			printHelper("SINGLE LINE STRING", ans);

		return 0;
	}

	void printComment(string text){
		// string ans = removerSlashNewline(text);
		// ans = ans.substr(1, ans.length()-1);
		text = text.substr(0, text.length()-1);
		printLog("COMMENT", text);
	}

	void printMultilineComment(string text){
		printLog("COMMENT", text);
	}

	void printError(string error, string text){
		logos << "Error at line# " << yylineno << ": " << error << " " << text << endl;
	}

};

ofstream logout("log.txt"), tokenout("token.txt");
PrintUtil printUtil(tokenout, logout);
string multilineComment = "";

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

{DIGITS}?((\.)+{DIGITS}){2,}{EXP}?	|
{DIGITS}?(\.)+{DIGITS}?	{
	printUtil.printError("TOO_MANY_DECIMAL_POINTS", yytext);
}

{DIGITS}(\.{DIGITS})?(E+[+-]?{DIGITS}?(\.)[0-9(\.)]*)	{
	printUtil.printError("ILLFORMED_NUMBER", yytext);
}

'([^'\\\n]|(\\{ESCAPES}))*'	{
					printUtil.printChar(yytext);
				}

"'\\'"	|
'([^'\\\n]|(\\{ESCAPES}))*\n	{
					string text = yytext;
					if(text.back() == '\n') text = text.substr(0, text.length()-1);
					printUtil.printError("UNFINISHED_CONST_CHAR", text);
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

[0-9][_a-zA-Z0-9]+		{
							printUtil.printError("INVALID_ID_SUFFIX_NUM_PREFIX", yytext);
						}

\"(([^"\\\n]|(\\{ESCAPES}))|("\\\n"))*\"	{
							printUtil.printString(yytext);
}
\"(([^"\\\n]|(\\{ESCAPES}))|("\\\n"))*\n	{
	string text = yytext;
	printUtil.printError("UNFINISHED_STRING", text.substr(0, text.length()-1));
}

"//"(.|"\\\n")*\n	{
	printUtil.printComment(yytext);
}

"/*"					{BEGIN(COMMENT);}
<COMMENT>"*/"			{
							BEGIN(INITIAL);
							printUtil.printMultilineComment(multilineComment);
							multilineComment = "";
						}
<COMMENT>([^*]|\n)+|.	{multilineComment.append(yytext);}
<COMMENT><<EOF>>		{
							printUtil.printError("UNFINISHED_COMMENT", "/*" + multilineComment);
							multilineComment = "";
							BEGIN(INITIAL);
						}

[ \t\n]+		{ /* IGNORE */}
.				{printUtil.printError("UNRECOGNIZED_CHAR", yytext);}
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
	

	yyin= fin;
	yylex();
	st.print();
	fclose(yyin);

	return 0;
}
