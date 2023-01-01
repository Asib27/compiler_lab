#ifndef __VARIABLE_SYMBOL_INFO_H__
#define __VARIABLE_SYMBOL_INFO_H__

#include"symbolInfo.h"

class VariableSymbolInfo : public SymbolInfo
{
private:
    std::string variableType;

	virtual void printHelper(std::ostream &os);
public:
    VariableSymbolInfo(std::string name, std::string type, std::string variableType, SymbolInfo* next=nullptr);

    std::string getVariableType(){ return variableType;}

    ~VariableSymbolInfo();
};

#endif