#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include"scopeTable.h"

#include<iostream>

class SymbolTable{
    ScopeTable* _curScope; 
    int _bucket_size;

    int nextScopeId;
    Printer *printer;
public:
    SymbolTable(int bucket_size, Printer *printer=nullptr);

    void enterScope();
    void exitScope();

    bool insert(SymbolInfo *s);
    bool remove(std::string s);
    SymbolInfo* lookup(std::string s);

    std::ostream& printCurrentScope(std::ostream &os);
    friend std::ostream& operator<<(std::ostream &os, const SymbolTable &s);

    void decreaseScopeCount(int a);

    ~SymbolTable();
};

#endif