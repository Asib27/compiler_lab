#include"symbolInfo.h"

SymbolInfo::SymbolInfo() : _next(nullptr) {}
SymbolInfo::SymbolInfo(std::string name, std::string type, SymbolInfo* next)
    : _name(name), _type(type), _next(next)
{

}

SymbolInfo::SymbolInfo(SymbolInfo &s, SymbolInfo* next)
    : _name(s._name), _type(s._type), _next(next)
{

}

std::string SymbolInfo::getName(){ return _name;}
std::string SymbolInfo::getType(){ return _type;}
SymbolInfo* SymbolInfo::getNext(){ return _next;}
void SymbolInfo::setName(std::string name){ _name = name;}
void SymbolInfo::setType(std::string type){ _type = type;} 
void SymbolInfo::setNext(SymbolInfo* next){
    _next = next;
}

std::ostream& operator<<(std::ostream &os, SymbolInfo s){
    os << "<" << s._name << "," << s._type << ">";

    return os;
}

bool SymbolInfo::operator==(const SymbolInfo &s){
    return _name == s._name &&
            _type == s._type;
}

bool SymbolInfo::operator!=(const SymbolInfo &s){
    return !( *this == s);
}

bool SymbolInfo::operator==(const std::string &s){
    return _name == s;
}

bool SymbolInfo::operator!=(const std::string s){
    return !( *this == s);
}