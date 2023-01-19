#ifndef _SYMBOL_INFO_H_
#define _SYMBOL_INFO_H_

#include<iostream>
#include<string>

class SymbolInfo
{
	std::string _name;
	std::string _type;
	SymbolInfo* _next;

	virtual void printHelper(std::ostream &os){
		os << "<" << _name << ", " << _type << ">";
	}
public:
	SymbolInfo();
	SymbolInfo(std::string name, std::string type, SymbolInfo* next=nullptr);
    SymbolInfo(SymbolInfo &s, SymbolInfo* next=nullptr);

	std::string getName();
	std::string getType();
	SymbolInfo* getNext();
	void setName(std::string name);
	void setType(std::string type);
	void setNext(SymbolInfo* next);

    friend std::ostream& operator<<(std::ostream &os, SymbolInfo& s);
    bool operator==(const SymbolInfo &s);
    bool operator!=(const SymbolInfo &s);
    bool operator==(const std::string &s);
    bool operator!=(const std::string &s);

	virtual ~SymbolInfo() {}
};

#endif