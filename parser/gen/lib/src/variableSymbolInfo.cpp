#include"../variableSymbolInfo.h"

VariableSymbolInfo::VariableSymbolInfo(std::string name, std::string type, std::string variableType, SymbolInfo* next)
    : SymbolInfo(name, type, next), variableType(variableType)
{}


void VariableSymbolInfo::printHelper(std::ostream &os){
    os << "<" << getName() << ", " << variableType << ", " << getType() << ">";
}

VariableSymbolInfo::~VariableSymbolInfo()
{
}