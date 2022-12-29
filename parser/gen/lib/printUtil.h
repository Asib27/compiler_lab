#ifndef _PRINT_UTIL_H_
#define _PRINT_UTIL_H_

#include<iostream>
#include<string>
#include"../y.tab.h"

class PrintUtil{
	std::ostream& logos;
	std::ostream& tokenos;
	int errorCount;

	void printLog(std::string token, std::string symbol, int lineNo);
	void printToken(std::string token, std::string symbol);
	void printHelper(std::string token, std::string symbol, int lineNo);

	char escapeToChar(char c);
	bool isEscapeChar(char c);
	/**
	* removes first and last char also
	*/
	std::string removerSlashNewline(std::string text);
	std::string insertEscapeInString(std::string text);

	int newLineCount(std::string text);
public:
	PrintUtil(std::ostream &token, std::ostream &log);
	int printKeyword(std::string text, int lineNo);
	void print(std::string token, std::string text, int lineNo);
	int printPunctuation(std::string text, int lineNo);
	void printChar(std::string text, int lineNo);
	int printString(std::string text, int lineNo);
	void printComment(std::string text, int lineNo);
	void printMultilineComment(std::string text, int lineNo);
	void printError(std::string error, std::string text, int lineNo);

	int getErrorCount();
};

#endif