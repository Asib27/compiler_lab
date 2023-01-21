#include"../symbolTable.h"

SymbolTable::SymbolTable(int bucket_size, Printer *printer)
    : _bucket_size(bucket_size), _curScope(nullptr), nextScopeId(1)
        , printer(printer)
    {
        enterScope();
    }

void SymbolTable::enterScope(){
    auto s =  new ScopeTable(_bucket_size, nextScopeId++, _curScope, printer);
    _curScope = s;
}


void SymbolTable::decreaseScopeCount(int a){
    nextScopeId -= a;
}

void SymbolTable::exitScope(){
    auto t = _curScope->getNext();
    if(t == nullptr){
        if(printer != nullptr && printer->isPrint()){
            auto &os = printer->getOutputStream();
            os << "\t";
            os << "ScopeTable# " << _curScope->getScopeId() <<" cannot be removed" << std::endl;
        }
        return ;
    }
                                        
    delete _curScope;
    _curScope = t;
}

bool SymbolTable::insert(SymbolInfo *s){
    return _curScope->insert(s);
}

bool SymbolTable::remove(std::string s){
    return _curScope->remove(s);
}

SymbolInfo* SymbolTable::lookup(std::string s){
    for(auto head = _curScope; head != nullptr; head = head->getNext()){
        auto t = head->lookup(s);
        if(t != nullptr) return t;
    }

    if(printer->isPrint()){
        auto &os = printer->getOutputStream();
        os << "\t";
        os << "'" << s << "'" << " not found in any of the ScopeTables" << std::endl;
    }
    return nullptr;
}

std::ostream& SymbolTable::printCurrentScope(std::ostream &os){
    os << *_curScope;
    return os;
}

std::ostream& operator<<(std::ostream &os, const SymbolTable &s){
    for(auto head = s._curScope; head != nullptr; head = head->getNext()){
        os << *head ;
    }
    return os;
}

SymbolTable::~SymbolTable(){
    for(auto head = _curScope; head != nullptr; ){
        auto t = head->getNext();
        delete head;
        head = t;
    }
}