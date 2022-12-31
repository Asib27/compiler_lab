#ifndef _SCOPE_TABLE_H_
#define _SCOPE_TABLE_H_ 

#include"symbolInfo.h"
#include"printer.h"

#include<iostream>
#include<string>

/**
* If any instance of ScopeTable is destroyed it will automatically free,
* all symbolInfo it contaims
*/
class ScopeTable
{
	SymbolInfo** _table;
	int _no_of_bucket;
    int _scopeId;

    Printer *printer;
    ScopeTable* _next;

    unsigned long long SDBMHash(std::string str);
	unsigned long long _getHash(std::string s);

    void printHelper(std::string s, int pos1, int pos2);
    void printDeleteHelper(std::string s, int pos1, int pos2);
    void printInsertHelper(int pos1, int pos2);
    void printInsertHelper(std::string s);
    void printHelper(std::string s);
public:
	ScopeTable(int n, int scopeId, ScopeTable *next=nullptr, Printer *printer=nullptr);

    bool insert(SymbolInfo *s);
    SymbolInfo* lookup(std::string s);
    bool remove(std::string s);

    void setNext(ScopeTable *next);
    ScopeTable* getNext();

    int getScopeId();
	~ScopeTable();

    friend std::ostream& operator<<(std::ostream &os, const ScopeTable &s);
};

#endif